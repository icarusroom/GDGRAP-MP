#include "Player.h"

const bool Player::isPlayer = true;

Player::Player(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path, std::string Tex_Path, glm::vec3 position, float scale, bool isPNG)
	: GameObject(Mesh_Path, Vert_Path, Frag_Path, Tex_Path, position, scale, isPlayer, isPNG) {
}

Player::~Player() {
}

void Player::update(GLFWwindow* window, float tDeltaTime) {

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->position.x -= 5.5f * tDeltaTime; // Move along negative x-axis
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->position.x += 5.5f * tDeltaTime; // Move along positive x-axis
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if (this->position.y < 0.0f) {
            this->position.y += 5.5f * tDeltaTime; // Move along positive y-axis
        }
        else if (this->position.y > 0.0f) {
            this->position.y = 0.0f;
        }
        printPositionY();
			
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        this->position.y -= 5.5f * tDeltaTime; // Move along negative y-axis
        printPositionY();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->position.z += 5.5f * tDeltaTime; // Move along positive z-axis
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->position.z -= 5.5f * tDeltaTime; // Move along negative z-axis
    }
}

void Player::printPositionY() {
    // If the whole number part of the position.y changes print it
    float roundedY = std::round(this->position.y);
    // Check if very close to 0 so that it prints 0;
    if (std::abs(roundedY) < 1e-6) {
        roundedY = 0.0f;
    }
    if (roundedY != std::round(previousY)) {
        std::cout << "Current Depth: " << roundedY << std::endl;
        previousY = this->position.y;
    }
}

