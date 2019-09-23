//KOK Mesh
using namespace std;

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "KOK_Mesh.h"
#include "KOK_Skeleton.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/gtx/quaternion.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include<glm/gtx/matrix_interpolation.hpp>

#include <stdio.h>
#include <iostream>

#define TICKS_SECOND_GLOBAL 30.0f

namespace KOK_Graphics
{

  KOK_Skeleton::KOK_Skeleton(MeshData * meshData, GLuint computeShader, string path, string name)
  {
    _m_NumBones = 0;
    _meshData = meshData;

    _computeShader = computeShader;
    _currentAnimation = "";

    _nextAnimation = "";

    _blending = false;
    _blendLevel = 0.0f;
    _blendDuration = 0.1f;

    AddAnimation(path, name);

  	glGenBuffers(1, &_boneUniformBuffer);
  	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _boneUniformBuffer);
  	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::mat4) * _m_NumBones, &_boneTransforms[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, _boneUniformBuffer); // Buffer Binding 1
  	glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);

    glGenBuffers(1, &_VBDBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _VBDBuffer);
  	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(VertexBoneData) * _meshData->_vertices.size(), &_VBD[0], GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, _VBDBuffer); // Buffer Binding 2
  	glBindBuffer(GL_SHADER_STORAGE_BUFFER,0);
  }

  KOK_Skeleton::KOK_Skeleton()
  {

  }

  Animation::Animation(const aiScene * m_Scene) : Animation()
  {
    //bake node anims
    for (GLuint i = 0; i < m_Scene->mAnimations[0]->mNumChannels; i++)
    {
      const aiNodeAnim* nodeAnim = m_Scene->mAnimations[0]->mChannels[i];

      vector<AnimationKey> pos;
      vector<AnimationKey> rot;
      vector<AnimationKey> sca;

      for(GLuint q = 0; q < nodeAnim->mNumPositionKeys; q++)
      {
        aiVector3D v = nodeAnim->mPositionKeys[q].mValue;
        pos.push_back(AnimationKey(glm::vec3(v.x, v.y, v.z), nodeAnim->mPositionKeys[q].mTime));
      }

      for(GLuint q = 0; q < nodeAnim->mNumRotationKeys; q++)
      {
        aiQuaternion r = nodeAnim->mRotationKeys[q].mValue;
        rot.push_back(AnimationKey(glm::quat(r.w, r.x, r.y, r.z), nodeAnim->mRotationKeys[q].mTime));
      }

      for(GLuint q = 0; q < nodeAnim->mNumScalingKeys; q++)
      {
        aiVector3D v = nodeAnim->mScalingKeys[q].mValue;
        sca.push_back(AnimationKey(glm::vec3(v.x, v.y, v.z), nodeAnim->mScalingKeys[q].mTime));
      }

      nodeAnims[nodeAnim->mNodeName.data] = new NodeAnim(pos, rot, sca);
    }
  }

  BoneNode::BoneNode(const aiNode * node, const aiScene * m_Scene)
  {
    nodeName = string(node->mName.data);

    transformation = aiMatrixToGlm(node->mTransformation);

    for (int i = 0; i < node->mNumChildren; i++)
    {
      children.push_back(BoneNode(node->mChildren[i], m_Scene));
    }
  }

  void Animation::TransformBone(NodeAnim * nodeAnim, float animationTime)
  {
    KOK_Skeleton::CalcInterpolatedScaling(nodeAnim->scaling, animationTime, nodeAnim);

    KOK_Skeleton::CalcInterpolatedRotation(nodeAnim->rotationQ, animationTime, nodeAnim);

    KOK_Skeleton::CalcInterpolatedPosition(nodeAnim->translation, animationTime, nodeAnim);
  }

  void Animation::TransformBone(const BoneNode& node, glm::mat4 ParentTransform, glm::mat4 globalInverse,
    vector<BoneInfo>& _m_BoneInfo, map<string,uint>& _m_BoneMapping)
  {
    glm::mat4 trans = node.transformation;

    //node ani for current animation
    NodeAnim * nodeAnim = nodeAnims[string(node.nodeName)];

    if(nodeAnim)
    {
      TransformBone(nodeAnim, animationTime);

      glm::mat4 scalingM = glm::scale(nodeAnim->scaling);
      glm::mat4 rotationM = glm::toMat4(nodeAnim->rotationQ);
      glm::mat4 translationM = glm::translate(nodeAnim->translation);

      trans = translationM * rotationM * scalingM;
    }

    glm::mat4 globalTransformation = ParentTransform * trans;

    if(_m_BoneMapping.find(node.nodeName) != _m_BoneMapping.end())
    {
      GLuint boneIndex = _m_BoneMapping[node.nodeName];

      _m_BoneInfo[boneIndex].finalTransformation = globalInverse * globalTransformation * _m_BoneInfo[boneIndex].boneOffset;
    }

    for (GLuint i = 0; i < node.children.size(); i++)
    {
      TransformBone(node.children[i], globalTransformation, globalInverse,
        _m_BoneInfo, _m_BoneMapping);
    }
  }

  //transform for interpolation
  void Animation::TransformBone(const BoneNode& node, glm::mat4 ParentTransform, glm::mat4 globalInverse,
    vector<BoneInfo>& _m_BoneInfo, map<string,uint>& _m_BoneMapping,
    GLfloat factor, Animation * currentAnim)
  {
    glm::mat4 trans = node.transformation;

    //node anim for current anim
    NodeAnim * nodeAnim = currentAnim->nodeAnims[string(node.nodeName)];

    //node anim for next animation
    NodeAnim * nodeAnimNext = nodeAnims[string(node.nodeName)];

    if(nodeAnim && nodeAnimNext)
    {
      //transform current animation with current time
      TransformBone(nodeAnim, animationTime);

      //transform next animation with default 0.0 time
      TransformBone(nodeAnimNext, currentAnim->animationTime);

      //interpolate transform values
      //scale
      glm::vec3 delta = nodeAnimNext->scaling - nodeAnim->scaling;
      glm::vec3 interpolatedScale = nodeAnim->scaling + factor * delta;
      //translation
      delta = nodeAnimNext->translation - nodeAnim->translation;
      glm::vec3 interpolatedTranslation = nodeAnim->translation + factor * delta;
      //rotation
      glm::quat interpolatedRotation = glm::normalize
      (
          glm::mix(nodeAnim->rotationQ, nodeAnimNext->rotationQ, factor)
      );

      //store animation matrices
      glm::mat4 scalingM = glm::scale(interpolatedScale);
      glm::mat4 rotationM = glm::toMat4(interpolatedRotation);
      glm::mat4 translationM = glm::translate(interpolatedTranslation);


      trans = translationM * rotationM * scalingM;
    }

    glm::mat4 globalTransformation = ParentTransform * trans;

    if(_m_BoneMapping.find(node.nodeName) != _m_BoneMapping.end())
    {
      GLuint boneIndex = _m_BoneMapping[node.nodeName];

      _m_BoneInfo[boneIndex].finalTransformation = globalInverse * globalTransformation * _m_BoneInfo[boneIndex].boneOffset;
    }

    for (GLuint i = 0; i < node.children.size(); i++)
    {
      TransformBone(node.children[i], globalTransformation, globalInverse,
        _m_BoneInfo, _m_BoneMapping, factor, currentAnim);
    }
  }


  void KOK_Skeleton::AddAnimation(string path, string name)
  {
    Assimp::Importer import;
    const aiScene * m_Scene;
  	m_Scene = import.ReadFile(path, aiProcess_OptimizeGraph);

    _currentAnimation = name;

    if(_animations.find(name) != _animations.end())
    {
      cout << "animation " << name << " already exists" << endl;
      return;
    }

    for (int i = 0; i < m_Scene->mNumMeshes; i++)
    {
      aiMesh * mesh = m_Scene->mMeshes[i];
      LoadBones(mesh);
    }

    _animations[name] = Animation(m_Scene);
    _rootNode = BoneNode(m_Scene->mRootNode, m_Scene);
    _animations[name].duration = m_Scene->mAnimations[0]->mDuration;
    _animations[name].ticksPerSecond = TICKS_SECOND_GLOBAL;
  }

  void KOK_Skeleton::SwitchAnimation(string name, GLfloat timeInSeconds)
  {
    if(_animations.find(name) == _animations.end())
    {
      cout << "animation " << name << " does not exist!" << endl;
      return;
    }

    //create an animation that includes the last frame of _currentAnimation and
    //first frame of next animation

    _nextAnimation = name;

    _blendLevel = 0.0f;
    _blendTime = timeInSeconds;

    _blending = true;

  }

  void KOK_Skeleton::AddBoneData(GLuint boneID, float weight, GLuint vertexID)
  {
    if(_VBD.size() == 0) _VBD.resize(_meshData->_vertices.size());

    for (GLuint i = 0; i < NUM_BONES_PER_VERTEX; i++)
    {
      if(_VBD[vertexID].weights[i] == 0.0f)
      {
        _VBD[vertexID].boneID[i] = boneID;
        _VBD[vertexID].weights[i] = weight;
        return;
      }
    }
  }

  GLuint KOK_Skeleton::FindRotation(float animationTime, NodeAnim * nodeAnim)
  {
      assert(nodeAnim->RotationKeys.size() > 0);

      for (GLuint i = 0 ; i < nodeAnim->RotationKeys.size() - 1 ; i++) {
          if (animationTime < (float)nodeAnim->RotationKeys[i + 1].time) {
              return i;
          }
      }

      assert(0);

      return 0;
  }

  GLuint KOK_Skeleton::FindScaling(float animationTime, NodeAnim * nodeAnim)
  {

      assert(nodeAnim->ScaleKeys.size() > 0);

      for (GLuint i = 0 ; i < nodeAnim->ScaleKeys.size() - 1 ; i++) {
          if (animationTime < (float)nodeAnim->ScaleKeys[i + 1].time) {
              return i;
          }
      }

      assert(0);

      return 0;
  }

  GLuint KOK_Skeleton::FindPosition(float animationTime, NodeAnim * nodeAnim)
  {
      for (GLuint i = 0 ; i < nodeAnim->PositionKeys.size() - 1 ; i++) {
          if (animationTime < (float)nodeAnim->PositionKeys[i + 1].time) {
              return i;
          }
      }

      assert(0);

      return 0;
  }

  void KOK_Skeleton::CalcInterpolatedScaling(glm::vec3& out, float animationTime, NodeAnim * nodeAnim)
  {
    if (nodeAnim->ScaleKeys.size() == 1)
    {
        out = nodeAnim->ScaleKeys[0].value;
        return;
    }

    GLuint ScalingIndex = FindScaling(animationTime, nodeAnim);
    GLuint NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < nodeAnim->ScaleKeys.size());
    GLfloat DeltaTime = (GLfloat)(nodeAnim->ScaleKeys[NextScalingIndex].time - nodeAnim->ScaleKeys[ScalingIndex].time);
    GLfloat Factor = (animationTime - (GLfloat)nodeAnim->ScaleKeys[ScalingIndex].time) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    glm::vec3 Start = nodeAnim->ScaleKeys[ScalingIndex].value;
    glm::vec3 End   = nodeAnim->ScaleKeys[NextScalingIndex].value;
    glm::vec3 Delta = End - Start;
    out = Start + Factor * Delta;
  }

  void KOK_Skeleton::CalcInterpolatedRotation(glm::quat& out, float animationTime, NodeAnim * nodeAnim)
  {
  	// we need at least two values to interpolate...
      if (nodeAnim->RotationKeys.size() == 1) {
          out = nodeAnim->RotationKeys[0].value;
          return;
      }

      GLuint RotationIndex = FindRotation(animationTime, nodeAnim);
      GLuint NextRotationIndex = (RotationIndex + 1);
      assert(NextRotationIndex < nodeAnim->RotationKeys.size());
      GLfloat DeltaTime = (GLfloat)(nodeAnim->RotationKeys[NextRotationIndex].time - nodeAnim->RotationKeys[RotationIndex].time);
      GLfloat Factor = (animationTime - (GLfloat)nodeAnim->RotationKeys[RotationIndex].time) / DeltaTime;
      assert(Factor >= 0.0f && Factor <= 1.0f);
      glm::quat StartRotationQ = nodeAnim->RotationKeys[RotationIndex].qvalue;
      glm::quat EndRotationQ   = nodeAnim->RotationKeys[NextRotationIndex].qvalue;
      out = glm::mix(StartRotationQ, EndRotationQ, Factor);
      out = glm::normalize(out);
  }

  void KOK_Skeleton::CalcInterpolatedPosition(glm::vec3& out, float animationTime, NodeAnim * nodeAnim)
  {
      if (nodeAnim->PositionKeys.size() == 1) {
          out = nodeAnim->PositionKeys[0].value;
          return;
      }

      GLuint PositionIndex = FindPosition(animationTime, nodeAnim);
      GLuint NextPositionIndex = (PositionIndex + 1);
      assert(NextPositionIndex < nodeAnim->PositionKeys.size());
      GLfloat DeltaTime = (GLfloat)(nodeAnim->PositionKeys[NextPositionIndex].time - nodeAnim->PositionKeys[PositionIndex].time);
      GLfloat Factor = (animationTime - (GLfloat)nodeAnim->PositionKeys[PositionIndex].time) / DeltaTime;
      assert(Factor >= 0.0f && Factor <= 1.0f);
      glm::vec3 Start = nodeAnim->PositionKeys[PositionIndex].value;
      glm::vec3 End = nodeAnim->PositionKeys[NextPositionIndex].value;
      glm::vec3 Delta = End - Start;
      out = Start + Factor * Delta;
  }

  void KOK_Skeleton::BoneTransform(GLfloat timeInSeconds)
  {

    glm::mat4 identity = glm::mat4(1.0f);

    glm::mat4 m_GlobalInverseTransform = _rootNode.transformation;
    m_GlobalInverseTransform = glm::inverse(m_GlobalInverseTransform);

    GLfloat timeInTicks;

    _boneTransforms.resize(_m_NumBones);

    //test if we are blending to a new animation
    if(_blending)
    {
      //factor 0.0 to 1.0 of current interpolation
      _blendLevel = (timeInSeconds - _blendTime) / _blendDuration;

      _animations[_nextAnimation].TransformBone(_rootNode, identity, m_GlobalInverseTransform,
        _m_BoneInfo, _m_BoneMapping, _blendLevel, &_animations[_currentAnimation]);

      //check if we are done blending
      if (_blendLevel >= 1.0f)
      {
        _blending = false;
        _currentAnimation = _nextAnimation;
      }
    }
    else //normal animation loop
    {
      timeInTicks = timeInSeconds * _animations[_currentAnimation].ticksPerSecond;

      _animations[_currentAnimation].animationTime =
        fmod(timeInTicks, _animations[_currentAnimation].duration);

      _animations[_currentAnimation].TransformBone(_rootNode, identity, m_GlobalInverseTransform,
        _m_BoneInfo, _m_BoneMapping);
    }

    for (GLuint i = 0; i < _m_NumBones; i++)
    {
      _boneTransforms[i] = _m_BoneInfo[i].finalTransformation;
    }


    VertexTransforms();
  }

  glm::mat4 aiMatrixToGlm(aiMatrix4x4 from)
  {
    glm::mat4 out;
    assert(sizeof(out) == sizeof(from));
    memcpy(&out, &from, sizeof(from));
    return glm::transpose(out);
  }

  void KOK_Skeleton::LoadBones(aiMesh * mesh)
  {
    for (GLuint i = 0; i < mesh->mNumBones; i++)
    {
      GLuint boneIndex = 0;
      string boneName(mesh->mBones[i]->mName.data);


      if (_m_BoneMapping.find(boneName) == _m_BoneMapping.end())
      {
        boneIndex = _m_NumBones;
        _m_NumBones++;
        BoneInfo bi;
        _m_BoneInfo.push_back(bi);
        _m_BoneInfo[boneIndex].boneOffset = aiMatrixToGlm(mesh->mBones[i]->mOffsetMatrix);
        _m_BoneMapping[boneName] = boneIndex;
      }
      else
      {
        boneIndex = _m_BoneMapping[boneName];
      }

      for (GLuint q = 0; q < mesh->mBones[i]->mNumWeights; q++)
      {
        GLint vertexID = mesh->mBones[i]->mWeights[q].mVertexId;
        GLfloat weight = mesh->mBones[i]->mWeights[q].mWeight;

        //if (weight <= 0) continue;

        AddBoneData(boneIndex, weight, vertexID);

      }
    }
  }

  void KOK_Skeleton::VertexTransforms()
  {
    glUseProgram(_computeShader);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, _boneUniformBuffer);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(glm::mat4) * _m_NumBones, &_boneTransforms[0]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glDispatchCompute(_meshData->_vertices.size(), 1, 1);

    //cpu implementation
    //for(GLint i = 0; i < _meshData->_vertices.size(); i++)
    //{
    //  glm::mat4 boneTrans = _boneTransforms[_VBD[i].boneID[0]] * _VBD[i].weights[0];
    //  boneTrans += _boneTransforms[_VBD[i].boneID[1]] * _VBD[i].weights[1];
    //  boneTrans += _boneTransforms[_VBD[i].boneID[2]] * _VBD[i].weights[2];
    //  boneTrans += _boneTransforms[_VBD[i].boneID[3]] * _VBD[i].weights[3];

    //  glm::vec4 tr = boneTrans * glm::vec4(_meshData->_vertices[i].position, 1.0f);
    //  _meshData->_vertices[i].transPosition = glm::vec3(tr.x, tr.y, tr.z);
  }

}
