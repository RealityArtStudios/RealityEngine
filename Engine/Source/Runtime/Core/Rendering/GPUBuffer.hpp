#pragma once
#include <glad/glad.h>
#include <vector>

class GPUBuffer {
public:
	enum Type { Vertex, Index, Uniform };

	GPUBuffer(); // Add constructor declaration

	~GPUBuffer();

	void Create(Type type, size_t size, const void* data = nullptr);
	void Update(size_t offset, size_t size, const void* data);
	void Bind() const;

	size_t GetCount() const { return elementCount; }

private:
	GLuint id = 0;
	Type bufferType;
	size_t elementCount = 0;
};