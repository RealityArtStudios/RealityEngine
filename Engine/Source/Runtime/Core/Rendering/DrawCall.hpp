#pragma once
#include <glad/glad.h>
#include "GPUBuffer.hpp"
#include "PipelineState.hpp"
#include <vector>

class DrawCall {
public:
	void SetPipelineState(const PipelineState* pipeline);
	void SetVertexBuffer(const GPUBuffer* buffer);
	void SetIndexBuffer(const GPUBuffer* buffer);
	void AddTexture(GLuint textureID);
	void Execute() const;

private:
	const PipelineState* pipeline = nullptr;
	const GPUBuffer* vertexBuffer = nullptr;
	const GPUBuffer* indexBuffer = nullptr;
	std::vector<GLuint> textures;
};