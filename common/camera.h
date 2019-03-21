#ifndef CAMERA_H
#define CAMERA_H

#include <Glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default Values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	// Attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera Options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	float lastX = 1280 / 2.0f;
	float lastY = 720 / 2.0f;
	bool firstMouse = true;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	mat4 GetViewMatrix() {
		return lookAt(Position, Position + Front, Up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	void  ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch) {
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		ProcessMouseMovement(xoffset, yoffset);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		ProcessMouseScroll(yoffset);
	}

private:
	void updateCameraVectors() {
		vec3 front;
		front.x = cos(radians(Yaw)) * cos(radians(Pitch));
		front.y = sin(radians(Pitch));
		front.z = sin(radians(Yaw)) * cos(radians(Pitch));
		Front = normalize(front);

		Right = normalize(cross(Front, WorldUp));
		Up = normalize(cross(Right, Front));
	}
};
#endif
