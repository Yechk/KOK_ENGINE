//mesh class
#ifndef KOK_SKELETON_H
#define KOK_SKELETON_H

#define NUM_BONES_PER_VERTEX 4

#define GLM_ENABLE_EXPERIMENTAL

using namespace std;

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "shader.h"
#include "KOK_Mesh.h"
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace KOK_Graphics
{

  glm::mat4 aiMatrixToGlm(aiMatrix4x4 from);

  struct VertexBoneData
  {
    GLuint boneID[NUM_BONES_PER_VERTEX] = {0};
    float weights[NUM_BONES_PER_VERTEX] = {0.0f};
  };

  struct BoneInfo
  {
    glm::mat4 boneOffset;

    glm::mat4 finalTransformation;

    BoneInfo()
    {
        boneOffset = glm::mat4(0.0);
        finalTransformation = glm::mat4(0.0);
    }
  };

  struct AnimationKey
  {
    union
    {
      glm::vec3 value;
      glm::quat qvalue;
    };


    GLfloat time;

    AnimationKey(glm::vec3 v, GLfloat t) : value{v}, time{t} {};
    AnimationKey(glm::quat v, GLfloat t) : qvalue{v}, time{t} {};
    AnimationKey();
  };

  struct NodeAnim
  {
    string name;

    glm::vec3 scaling;
    glm::quat rotationQ;
    glm::vec3 translation;

    vector<AnimationKey> PositionKeys;
    vector<AnimationKey> RotationKeys;
    vector<AnimationKey> ScaleKeys;

    NodeAnim(vector<AnimationKey> pos, vector<AnimationKey> rot, vector<AnimationKey> sca ) :
      PositionKeys{pos}, RotationKeys{rot}, ScaleKeys{sca} {};
  };

  struct BoneNode
  {
    string nodeName;

    glm::mat4 transformation;

    vector<BoneNode> children;

    BoneNode() {};

    BoneNode(const aiNode * node, const aiScene * m_Scene);
  };

  struct Animation
  {
    map<string, NodeAnim*> nodeAnims;

    GLfloat duration;
    GLfloat ticksPerSecond;


    GLfloat animationTime;

    bool loop;

    Animation() :
      duration{1.0f},
      ticksPerSecond{30.0f},
      animationTime{0.0f},
      loop{true}{};

    Animation(const aiScene * m_Scene);

    void TransformBone(NodeAnim * nodeAnim, float animationTime);

    void TransformBone(const BoneNode& node, const glm::mat4& ParentTransform, glm::mat4 globalInverse,
      vector<BoneInfo>& _m_BoneInfo, map<string,uint>& _m_BoneMapping);

    void TransformBone(const BoneNode& node, const glm::mat4& ParentTransform, glm::mat4 globalInverse,
      vector<BoneInfo>& _m_BoneInfo, map<string,uint>& _m_BoneMapping, GLfloat factor, Animation * nextAnim);
  };

  class KOK_Skeleton
  {
  public:
  	//functions
  	KOK_Skeleton(MeshData * meshData, GLuint computeShader, string path, string name);
    KOK_Skeleton();

    void AddAnimation(string path, string name);

    void SwitchAnimation(string name, GLfloat timeInSeconds);

    void AddBoneData(const GLuint& boneID, const float& weight, const GLuint& vertexID);
    void BoneTransform(GLfloat timeInSeconds);
    static void CalcInterpolatedScaling(glm::vec3& out, float animationTime, NodeAnim * nodeAnim);
    static void CalcInterpolatedRotation(glm::quat& out, float animationTime, NodeAnim * nodeAnim);
    static void CalcInterpolatedPosition(glm::vec3& out, float animationTime, NodeAnim * nodeAnim);

    static GLuint FindRotation(const float& animationTime, NodeAnim * nodeAnim);
    static GLuint FindScaling(const float& animationTime, NodeAnim * nodeAnim);
    static GLuint FindPosition(const float& animationTime, NodeAnim * nodeAnim);

    void VertexTransforms();

    void LoadBones(aiMesh * mesh);



  private:
    //holds bone data
    vector<VertexBoneData> _VBD;
    vector<glm::mat4> _boneTransforms;

    GLuint _m_NumBones;
    vector<BoneInfo> _m_BoneInfo;
    map<string,uint> _m_BoneMapping;

    BoneNode _rootNode;

    bool _blending;
    GLfloat _blendLevel;
    GLfloat _blendDuration;
    GLfloat _blendTime;

    map<string, Animation> _animations;

    string _nextAnimation;
    string _currentAnimation;

    GLuint _boneUniformBuffer;
    GLuint _VBDBuffer;
    GLuint _computeShader;

    //pointer to vertex data
    MeshData * _meshData;

  };
  //
}

#endif
