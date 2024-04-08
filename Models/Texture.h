#pragma once

#include<glad/glad.h>
#include "../stb_image.h"

#include "shader.h"

class Texture {
	private:
		GLuint texture;
		int img_width;
		int img_height;
		int colorChannels;

	public:	
		Texture(std::string Tex_Path, bool isPNG);
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();

	public:
		GLuint getTexture() const { return this->texture; }
};

