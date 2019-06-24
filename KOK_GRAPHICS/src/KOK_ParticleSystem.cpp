#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

#include <string.h>
#include <stdio.h>

#include <algorithm>

#include <stdio.h>
#include <iostream>

using namespace std;

#include "KOK_ParticleSystem.h"
#include "shader.h"

KOK_ParticleSystem::KOK_ParticleSystem(GLuint maxParticles, GLuint texture, GLdouble spawnRate, GLuint burst)
{
  _maxParticles = maxParticles;
  particleMesh = ParticleMesh();
  worldPosition = glm::vec3(0.0f,1.0f,0.0f);

  _activeParticles = 0;
  _spawnRate = spawnRate;
  _burst = burst;

  _spawnTime = 0.0f;

  _texture = texture;

  _defaultParticle = ParticleData(glm::vec4(0.0f), glm::vec3(0.0f,-0.001f, 0.0f), worldPosition, 0.05f, 1.5, 0.0);

  for (GLuint i = 0; i < maxParticles; i++)
  {
    _defaultParticle.RandVelocity(glm::vec3(-0.1f), glm::vec3(0.1f));
    _particles.push_back(ParticleData(_defaultParticle));
  }

  //add buffers

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO_DYNAMIC);
  glGenBuffers(1, &VBO_STATIC);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_STATIC);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec2) + sizeof(glm::vec3)) * 4, &particleMesh.texCoords[0], GL_STATIC_DRAW);

  //vertex coords
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

  glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetof(ParticleMesh, vertices));

  glBindBuffer(GL_ARRAY_BUFFER, VBO_DYNAMIC);
  glBufferData(GL_ARRAY_BUFFER, _particles.size() * sizeof(ParticleDynamicData), &_particles[0], GL_DYNAMIC_DRAW);

  //vertex positions
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*)offsetof(ParticleDynamicData, position));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ParticleData), (void*)offsetof(ParticleDynamicData, alpha));
  glVertexAttribDivisor(3, 1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, particleMesh.indices.size() * sizeof(GLuint), &particleMesh.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

}

void KOK_ParticleSystem::SpawnParticle(GLdouble elapsedTime)
{
  _spawnTime = elapsedTime;

  if(_activeParticles < _maxParticles)
  {
    for(int i = 0; i < _maxParticles; i++)
    {
      if(!_particles[i].active)
      {
        _particles[i].active = true;
        _particles[i].RandVelocity(glm::vec3(-0.02f, 0.03f, -0.02f), glm::vec3(0.02f, 0.08f, 0.02f));
        _particles[i].time = elapsedTime;
        _particles[i].life = RandFloat(0.5f, 2.0f);
        _activeParticles += 1;
        return;
      }
    }
  }
}

void KOK_ParticleSystem::Draw(GLuint shader, glm::mat4 projection, glm::mat4 view, GLdouble elapsedTime)
{
  glm::mat4 camWorld = glm::inverse(view);
  glm::vec3 camPos = glm::vec3(camWorld[3][0], camWorld[3][1], camWorld[3][1]);

  for(int i = 0; i < _maxParticles; i++)
  {
    _particles[i].Update(elapsedTime, _activeParticles, _defaultParticle, camPos);
  }

  if(_spawnRate == 0.0 || abs(_spawnTime - elapsedTime) > _spawnRate)
  {
    for(int i = 0; i < _burst; i++) SpawnParticle(elapsedTime);
  }

  if(_activeParticles == 0) return;

  glm::vec3 cameraRight = {view[0][0], view[1][0], view[2][0]};
  glm::vec3 cameraUp = {view[0][1], view[1][1], view[2][1]};

  glm::mat4 VP = projection * view;

  SetUniformVec3(shader, "cameraRight", cameraRight.x, cameraRight.y, cameraRight.z);
  SetUniformVec3(shader, "cameraUp", cameraUp.x, cameraUp.y, cameraUp.z);
  SetUniformMat4(shader, "VP", VP);
  SetUniformTexture(shader, "diffuseTex" , 0);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texture);

  //std::sort(&_particles[0], &_particles[_particles.size()-1]);

  glBindVertexArray(VAO);
  //sub the data for all particle transforms
  glBindBuffer(GL_ARRAY_BUFFER, VBO_DYNAMIC);
  glBufferSubData(GL_ARRAY_BUFFER, 0, _particles.size() * sizeof(ParticleDynamicData), &_particles[0]);
  //
  glDrawElementsInstanced(GL_TRIANGLES, particleMesh.indices.size(), GL_UNSIGNED_INT, 0, _maxParticles);
  glBindVertexArray(0);
}

ParticleMesh::ParticleMesh()
{
  vertices[0] = glm::vec3(-1.0f,0.0f,-1.0f);
  vertices[1] = glm::vec3(1.0f,0.0f,-1.0f);
  vertices[2] = glm::vec3(1.0f,0.0f,1.0f);
  vertices[3] = glm::vec3(-1.0f,0.0f,1.0f);

  texCoords[0] = glm::vec2(0.0f,0.0f);
  texCoords[1] = glm::vec2(1.0f,0.0f);
  texCoords[2] = glm::vec2(1.0f,1.0f);
  texCoords[3] = glm::vec2(0.0f,1.0f);

  indices.push_back(0);
  indices.push_back(1);
  indices.push_back(2);
  indices.push_back(0);
  indices.push_back(2);
  indices.push_back(3);
}

void ParticleData::RandVelocity(glm::vec3 min, glm::vec3 max)
{
  glm::vec3 randNums;

  randNums.x = KOK_ParticleSystem::RandFloat(min.x, max.x);
  randNums.y = KOK_ParticleSystem::RandFloat(min.y, max.y);
  randNums.z = KOK_ParticleSystem::RandFloat(min.z, max.z);

  velocity = glm::vec4(randNums, 0.0f);
}

void ParticleData::Init(const ParticleData& old)
{
  active = false;
  velocity = glm::vec4(0.0f);
  offset = old.offset;
  scale = old.scale;
  life = old.life;
  time = 0.0f;
  cameraDistance = 0.0f;
  acceleration = old.acceleration;

  positionData.position = glm::vec4(0.0f);
  positionData.alpha = 0.0f;
}

ParticleData::ParticleData(const ParticleData& old)
{
  Init(old);
}

void ParticleData::Update(GLdouble elapsedTime, GLuint &activeParticles, const ParticleData& old, glm::vec3 camPos)
{
  if(active)
  {
    if(abs(time - elapsedTime) > life)
    {
      Init(old);
      activeParticles -= 1;
    }
    else
    {
      velocity.x += acceleration.x;
      velocity.y += acceleration.y;
      velocity.z += acceleration.z;
      offset += glm::vec3(velocity);
      scale -= velocity.w;

      cameraDistance = glm::distance(offset, camPos);

      positionData.position = glm::vec4(offset, scale);

      GLfloat delta = (float)(abs(time - elapsedTime) / (life + 0.01));
      positionData.alpha = 1.0f - (delta - glm::floor(delta));
    }

  }
}
