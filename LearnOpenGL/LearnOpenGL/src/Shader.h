#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <GLAD/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
class Shader
{
private:
	unsigned int m_id;
	std::map<std::string, int> m_uniformLocationMap;
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void bind() const;
	void unbind() const;


	//set uniforms
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value) ;

	~Shader();

private:
	int getKnownUniformLocation(const std::string& name);
};

#endif