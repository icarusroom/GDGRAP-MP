#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera() : MyCamera() {
    this->firstClick = true;
    this->window_height = 600;
    this->window_width = 600;
    this->lastMouseX = 0.0f;
    this->lastMouseY = 0.0f;
    this->mouseX = 0.0f;
    this->mouseY = 0.0f;
    this->theta = 45.f;
    this->phi = 90.f;
    this->camX = 0.0f;
    this->camY = 0.0f;
    this->camZ = 20.0f;
    this->aspectRatio = window_height / window_width;
    this->setProjectionMatrix(100.f);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix(float aspectRatio) const {
    return projectionMatrix;
}

void PerspectiveCamera::setProjectionMatrix(float viewAngle) {
    this->projectionMatrix = glm::perspective(glm::radians(viewAngle), this->aspectRatio, 0.1f, this->zFar);
}

void PerspectiveCamera::updateCamera(GLFWwindow* window, float deltaTime) {
    // Get the state of the left mouse button
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        // Initialize mouse position on first click
        if (firstClick) {
            firstClick = false;
            glfwGetCursorPos(window, &this->lastMouseX, &this->lastMouseY);
        }

        // Get current mouse position
        double mouseX, mouseY;
        glfwGetCursorPos(window, &this->mouseX, &this->mouseY);

        // Calculate the change in mouse position
        double deltaX = this->mouseX - this->lastMouseX;
        double deltaY = this->mouseY - this->lastMouseY;

        // Invert deltaY to match 3D graphics coordinate system
        deltaY = -deltaY;

        // Calculate the new orientation
        theta += sensitivity * static_cast<float>(deltaX);
        phi += sensitivity * static_cast<float>(deltaY);

        // Limit phi to avoid gimbal lock
        if (phi >= 180.0f)
            phi = 180.0f;
        if (phi <= 0.1f)
            phi = 0.1f;

        // Calculate new camera position
        float radius = 10.0f; // Set the radius to 20 to start at (0, 0, 20)
        camX = radius * sin(glm::radians(phi)) * cos(glm::radians(theta));
        camY = radius * cos(glm::radians(phi));
        camZ = radius * sin(glm::radians(phi)) * sin(glm::radians(theta));

        // Update camera position
        setCameraPosition(glm::vec3(camX, camY, camZ));

        // Update last mouse positions
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;

        std::cout << "Camera Position: (" << camX << ", " << camY << ", " << camZ << ")" << std::endl;
    }
    else {
        // Reset first click
        firstClick = true;
    }
}

void PerspectiveCamera::update(GLFWwindow* window, float tDeltaTime) {
    float cameraSpeed = 5.5f * tDeltaTime;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        CameraMovement(glm::normalize(glm::cross(orientation, up)) * -cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        CameraMovement(glm::normalize(glm::cross(orientation, up)) * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        CameraMovement(-cameraSpeed * orientation);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        CameraMovement(cameraSpeed * orientation);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        if (this->getCameraPosition().y < 0.0f) {
            CameraMovement(glm::vec3(0.0f, cameraSpeed, 0.0f)); // Move along positive y-axis
        }
        else if (this->getCameraPosition().y > 0.0f) {
            CameraMovement(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        CameraMovement(glm::vec3(0.0f, -cameraSpeed, 0.0f)); // Move along negative y-axis
    }
}

void PerspectiveCamera::FOV(bool is1stPerson, bool is3rdPerson, glm::vec3 playerposition) {
    if (is1stPerson) {
        setCameraPosition(glm::vec3(playerposition.x, playerposition.y, playerposition.z - 10.0f));
        this->setZfar(200.f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_CONSTANT_COLOR, GL_SRC_COLOR);
        glBlendEquation(GL_FUNC_SUBTRACT);
        glBlendColor(153.f / 254.f, 255.f / 254.f, 153.f / 254.f, 1.00);
	}
	
    if (is3rdPerson) {
        setCameraPosition(glm::vec3(playerposition.x, playerposition.y, playerposition.z + 25.0f));
		this->setZfar(50.f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
        
    }
}

void PerspectiveCamera::setZfar(float zFar) {
	this->zFar = zFar;
}

