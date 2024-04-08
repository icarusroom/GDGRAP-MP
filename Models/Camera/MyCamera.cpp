#include "MyCamera.h"

MyCamera::MyCamera() {
	this->cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = (glm::vec3(0.f, 1.f, 0.f));

	this->setCameraPosition(glm::vec3(0.0f, 1.0f, 25.0f));

	setViewMatrix();
}

void MyCamera::CameraMovement(glm::vec3 movement) {
	this->cameraPos += movement;
	setViewMatrix();
}

void MyCamera::setCameraPosition(glm::vec3 position) {
	this->cameraPos = position;
	setViewMatrix();
}

void MyCamera::setOrientation(glm::vec3 orientation) {

	this->orientation = orientation;
	setViewMatrix();
}

void MyCamera::setViewMatrix() {
	this->view_matrix = glm::lookAt(this->cameraPos, this->cameraPos + this->orientation, up);
}

glm::mat4 MyCamera::getViewMatrix() {
	return this->view_matrix;
}

glm::vec3 MyCamera::getCameraPosition() {
	return this->cameraPos;
}


