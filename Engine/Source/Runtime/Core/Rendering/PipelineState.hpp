#pragma once
#include <glad/glad.h>
#include <string>
#include <unordered_map>

class PipelineState {
public:
	bool LoadShader(const std::string& vertexSource, const std::string& fragmentSource);
	void Bind() const;

	GLint GetUniformLocation(const std::string& name) const;

private:
	GLuint program = 0;
	mutable std::unordered_map<std::string, GLint> uniformLocations;

	GLuint CompileShader(GLenum type, const std::string& source) const;
};