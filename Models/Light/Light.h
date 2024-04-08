#pragma once

#include "../GameObject.h"

class Light : public GameObject {
	private:
		glm::vec3 lightColor;
		glm::vec3 ambientColor;
		float ambientStr;
		float specStr;
		float specPhong;
		float intensity;
		
	protected:
		glm::vec3 position;

	public:
		Light(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path, std::string Tex_Path, glm::vec3 position, float scale, glm::vec3 lightColor, glm::vec3 ambientColor, float ambientStr,
		float specStr, float specPhong);

		virtual glm::vec3 getLightColor(bool isCenter);
		virtual glm::vec3 getAmbientColor(bool isCenter);

		inline float getAmbientStr() { return this->ambientStr; }
		inline float getSpecStr() { return this->specStr; }
		inline float getSpecPhong() { return this->specPhong; }
		inline float getIntensity() { return this->intensity; }

		void lightMovement(glm::vec3 position) { this->position += position; }
		void setLight(glm::vec3 lightColor) { this->lightColor = lightColor; }
		void setAmbientColor(glm::vec3 ambientColor) { this->ambientColor = ambientColor; }
		void setAmbientStr(float ambientStr) { this->ambientStr = ambientStr; }
		void setSpecStr(float specStr) { this->specStr = specStr; }
		void setSpecPhong(float specPhong) { this->specPhong = specPhong; }
		void increaseIntensity(float intensity) { this->intensity += intensity; }
	};



