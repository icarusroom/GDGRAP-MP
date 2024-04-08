#pragma once

#include "Light.h"

class Directional : public Light {
    private:
        glm::vec3 direction;
        glm::vec3 lightColor;
        glm::vec3 ambientColor;
        const float intensitySpeed = 2.0f;

    public:
        Directional(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path, std::string Tex_Path, 
            glm::vec3 position, float scale, glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr,
            float specStr, float specPhong);
        glm::vec3 getDirection() { return this->direction; }
        void setDirection(glm::vec3 direction) { this->direction = direction; }
        void update(GLFWwindow*, float tDeltaTime);
        glm::vec3 getLightColor(bool isPerspective) override { return this->lightColor; }
        glm::vec3 getAmbientColor(bool isPerspective) override { return this->ambientColor; }
};





