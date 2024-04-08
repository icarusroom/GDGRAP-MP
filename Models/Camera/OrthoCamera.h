#pragma once

#include "MyCamera.h"

class OrthoCamera : public MyCamera {
	public:
		glm::mat4 projectionMatrix;

	public:
		OrthoCamera();
		glm::mat4 getProjectionMatrix(float aspectRatio) const;
};

