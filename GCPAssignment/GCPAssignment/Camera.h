#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>

#include "InputManager.h"

class Camera
{
private:

	bool firstMouse = true;
	float pitch = 0.0f, yaw = -90.0f;

	const float movementSpeed = 0.1f;
	glm::vec2 oldMousePos, newMousePos;

	glm::vec3 forward;
	glm::vec3 up;

public:

	glm::vec3 position;
	int time = 0;

	Camera();

	void CameraControls();
	void MouseMovement();
	void UpdateCamera();

	glm::mat4 view;

};

#endif

