#include "Camera.h"

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 10.0f);
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	newMousePos = glm::vec2(InputManager::mouseX, InputManager::mouseY);
	oldMousePos = newMousePos;
}

void Camera::CameraControls()
{
	if (InputManager::IfKeyDown(SDL_SCANCODE_W))
	{
		position += movementSpeed * forward;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_S))
	{
		position -= movementSpeed * forward;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_A))
	{
		glm::vec3 direction = glm::cross(forward, up);
		position -= movementSpeed * direction;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_D))
	{
		glm::vec3 direction = glm::cross(forward, up);
		position += movementSpeed * direction;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_SPACE))
	{
		position += movementSpeed * up;
	}
	if (InputManager::IfKeyDown(SDL_SCANCODE_X))
	{
		position -= movementSpeed * up;
	}

	MouseMovement();
}

void Camera::MouseMovement()
{
	if (InputManager::IfMouseButtonDown(0))
	{
		newMousePos = glm::vec2(InputManager::mouseX, InputManager::mouseY);

		if (firstMouse)
		{
			oldMousePos = newMousePos;
			firstMouse = false;
		}

		float xoffset = newMousePos.x - oldMousePos.x;
		float yoffset = oldMousePos.y - newMousePos.y; // reversed since y-coordinates go from bottom to top
		oldMousePos = newMousePos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		forward = glm::normalize(front);
	}
	else
	{
		firstMouse = true;
	}
}

void Camera::UpdateCamera()
{
	view = glm::lookAt(position, position + forward, up);
}