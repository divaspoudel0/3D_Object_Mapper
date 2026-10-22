#pragma once

#include "Includes.hpp"

class Shader
{

	private:

		GLuint shaderID;

	public:

		std::string readSource(const std::string& filepath);

		GLuint compile(GLenum type, const std::string& source);

		void createProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		void useProgram();

};