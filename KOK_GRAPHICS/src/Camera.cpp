#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

const double Camera::TO_RADS = 3.141592654 / 180.0; // The value of 1 degree in radians

Camera::Camera(GLFWwindow * window, float theWindowWidth, float theWindowHeight)
{
	this->window = window;
	initCamera();

	windowWidth  = theWindowWidth;
	windowHeight = theWindowHeight;

	// Calculate the middle of the window
	windowMidX = windowWidth  / 2.0f;
	windowMidY = windowHeight / 2.0f;

	glfwSetCursorPos(window, windowMidX, windowMidY);

	firstMouse = true;
	menuActive = false;
	menuReset = true;
}

Camera::~Camera()
{
	// Nothing to do here - we don't need to free memory as all member variables
	// were declared on the stack.
}

void Camera::initCamera()
{
	// Set position, rotation and speed values to zero
	position= glm::vec3(0.0f,0.7f,0.0f);
	rotation= glm::vec3(0.0f);
	speed= glm::vec3(0.05f);

	// How fast we move (higher values mean we move and strafe faster)
	movementSpeedFactor = 1.0;

	pitchSensitivity = 0.2; // How sensitive mouse movements affect looking up and down
	yawSensitivity   = 0.2; // How sensitive mouse movements affect looking left and right

	// To begin with, we aren't holding down any keys
	holdingForward     = false;
	holdingBackward    = false;
	holdingLeftStrafe  = false;
	holdingRightStrafe = false;
}

// Function to convert degrees to radians
const double Camera::toRads(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}

// Function to deal with mouse position changes
void Camera::handleMouseMove(double xpos, double ypos)
{
	if(menuActive) return;

 	if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = -(xpos - lastX);
    float yoffset = -(lastY - ypos);

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    rotation = glm::normalize(front);
}

// Function to calculate which direction we need to move the camera and by what amount
void Camera::move(double deltaTime)
{

	if (holdingForward)
	{
		position += speed * rotation * glm::vec3(1,0,1);
	}

	if (holdingBackward)
	{
		position -= speed * rotation * glm::vec3(1,0,1);
	}

	if (holdingLeftStrafe)
	{
		position -= glm::normalize(glm::cross(rotation, glm::vec3(0,1,0))) * speed * glm::vec3(1,0,1);
	}

	if (holdingRightStrafe)
	{
		position += glm::normalize(glm::cross(rotation, glm::vec3(0,1,0))) * speed * glm::vec3(1,0,1);
	}
}
