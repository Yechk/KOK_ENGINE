#ifndef KOK_PARTICLESYSTEM_H
#define KOK_PARTICLESYSTEM_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <vector>
#include <string.h>
#include <stdio.h>

using namespace std;


struct ParticleMesh
{
  glm::vec2 texCoords[4];
  glm::vec3 vertices[4];
  vector<GLuint> indices;
  vector<GLuint> textures;

  ParticleMesh();
};

struct ParticleDynamicData
{
  glm::vec4 position; //scale is encoded as w in position
  GLfloat alpha;
};

struct ParticleData
{
  ParticleDynamicData positionData;

  bool active;
  glm::vec3 offset;
  glm::vec4 velocity;
  glm::vec3 acceleration;
  GLfloat scale;
  GLdouble life;
  GLdouble time;

  GLfloat cameraDistance;

  void Active(bool isActive) {active = isActive;};
  ParticleData() : velocity{glm::vec4(0.0f)}, offset{glm::vec3(0.0f)}, scale{1.0f}, acceleration{glm::vec3(0.0f)}, active{false} {};
  ParticleData(glm::vec4 vel, glm::vec3 acc, glm::vec3 off, GLfloat sca, GLdouble lfe, GLdouble tm) :
    velocity{vel}, offset{off}, scale{sca}, life{lfe}, time{tm}, cameraDistance{0.0f}, acceleration{acc}, active{false} {};

  ParticleData(const ParticleData& old);
  void Init(const ParticleData& old);

  void Update(GLdouble elapsedTime, GLuint &activeParticles, const ParticleData& old, glm::vec3 camPos);

  void RandVelocity(glm::vec3 min, glm::vec3 max);

  bool operator<(ParticleData& that)
  {
    return this->cameraDistance > that.cameraDistance;
  }

};


class KOK_ParticleSystem
{

public:
  KOK_ParticleSystem(const GLuint& maxParticles, const GLuint& texture, const GLdouble& spawnRate=0.0, const GLuint& burst=1);

  void Draw(const GLuint& shader, const glm::mat4& projection, const glm::mat4& view, const GLdouble& elapsedTime);

  static inline float RandFloat(float min, float max)
  {
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
  };

  void SpawnParticle(const GLdouble& elapsedTime);

  const GLuint& ActiveParticles() const {return _activeParticles;};

private:

  GLuint _maxParticles;
  GLuint _activeParticles;
  GLdouble _spawnRate;
  GLuint _burst;

  GLdouble _spawnTime;

  GLuint _texture;

  ParticleMesh particleMesh;

  vector<ParticleData> _particles;
  ParticleData _defaultParticle;

  glm::vec3 worldPosition;


  GLuint VAO, VBO_STATIC, VBO_DYNAMIC, EBO;

};


#endif
