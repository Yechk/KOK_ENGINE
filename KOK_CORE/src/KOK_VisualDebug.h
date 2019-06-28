#ifndef KOK_VISUALDEBUG
#define KOK_VISUALDEBUG

#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <vector>

using namespace std;


class KOK_VisualDebug
{
  GLuint VAO,VBO;

  GLuint shader;

public:

  KOK_VisualDebug()
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LoadDebugShader();
  };

  void DrawDebug(vector<glm::vec3> &lines, glm::mat4 projection, glm::mat4 view)
  {
    glUseProgram(shader);

    glm::mat4 mat = projection * view;
    glUniformMatrix4fv(glGetUniformLocation(shader, "vp"), 1, GL_FALSE, &mat[0][0]);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * lines.size(), &lines[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, lines.size());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

protected:

  void LoadDebugShader()
  {
    	// Create the shaders
    	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    	std::string VertexShaderCode =
          "#version 460 core\n"
          "layout (location = 0) in vec3 aPos;\n"
          "uniform mat4 vp;"
          "void main()\n"
          "{\n"
          "   gl_Position = vp * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
          "}\0";

    	std::string FragmentShaderCode =
          "#version 460 core\n"
          "out vec4 FragColor;\n"
          "void main()\n"
          "{\n"
          "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
          "}\n\0";



    	GLint Result = GL_FALSE;
    	int InfoLogLength;



    	// Compile Vertex Shader
    	printf("Compiling shader Debug");
    	char const * VertexSourcePointer = VertexShaderCode.c_str();
    	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    	glCompileShader(VertexShaderID);

    	// Check Vertex Shader
    	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    	if ( InfoLogLength > 0 ){
    		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
    		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    		printf("%s\n", &VertexShaderErrorMessage[0]);
    	}



    	// Compile Fragment Shader
    	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    	glCompileShader(FragmentShaderID);

    	// Check Fragment Shader
    	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    	if ( InfoLogLength > 0 ){
    		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
    		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    		printf("%s\n", &FragmentShaderErrorMessage[0]);
    	}



    	// Link the program
    	printf("Linking program\n");
    	shader = glCreateProgram();
    	glAttachShader(shader, VertexShaderID);
    	glAttachShader(shader, FragmentShaderID);
    	glLinkProgram(shader);

    	// Check the program
    	glGetProgramiv(shader, GL_LINK_STATUS, &Result);
    	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    	if ( InfoLogLength > 0 ){
    		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
    		glGetProgramInfoLog(shader, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    		printf("%s\n", &ProgramErrorMessage[0]);
    	}

    	glDeleteShader(VertexShaderID);
    	glDeleteShader(FragmentShaderID);
  }
};

#endif
