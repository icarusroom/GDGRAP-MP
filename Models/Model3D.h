#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../tiny_obj_loader.h"
#include "../stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>

class Model3D {
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint shaderProgram;
		GLuint texture;
		glm::vec3 position;
		float scale;
		tinyobj::attrib_t attributes;
		std::vector<GLuint> mesh_indices;
		std::vector<GLfloat> fullVertexData;
		int img_width;
		int img_height;
		int colorChannels;
		glm::mat4 IdentityMatrix;

	protected:
		float x;
		float y;
		float z;

	public:
		Model3D(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path, std::string Tex_Path,
			glm::vec3 position, float scale);
		~Model3D();
		void draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::vec3 lightPos, glm::vec3 lightColor, float ambientStr, glm::vec3 ambientColor, float specStr, float specPhong, float brightness, glm::vec3 dir_direction,
			glm::vec3 dir_light_color, float dir_ambient_str, glm::vec3 dir_ambient_color,
			float dir_spec_str, float dir_spec_phong, float dir_intensity, glm::vec3 cameraPos);
		void draw(glm::mat4 transformationMatrix, glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::vec3 light_color);
		void loadShaders(std::string Vert_Path, std::string Frag_Path);
		void loadMesh(std::string Mesh_Path);
		void loadTexture(std::string Tex_Path);
		void loadVertices();
		void update(GLFWwindow* window, float tDeltaTime);
		glm::mat4 TransformationMatrix() const;
		void setScale(glm::vec3 scale);
		void setPosition(glm::vec3 position);
		inline glm::vec3 getPosition() { return position; }
		inline GLuint getVAO() { return VAO; }
		inline GLuint getVBO() { return VBO; }
		inline GLuint getShaderProgram() { return shaderProgram; }
		inline GLuint getTexture() { return texture; }
		inline std::vector<GLuint> getMeshIndices() { return mesh_indices; }
		inline std::vector<GLfloat> getFullVertexData() { return fullVertexData; }
		inline int getImgWidth() { return img_width; }
		inline int getImgHeight() { return img_height; }
};

