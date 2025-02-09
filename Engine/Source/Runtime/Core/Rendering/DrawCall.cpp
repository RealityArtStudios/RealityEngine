#include "DrawCall.hpp"

void DrawCall::SetPipelineState(const PipelineState* pipeline) {
    this->pipeline = pipeline;
}

void DrawCall::SetVertexBuffer(const GPUBuffer* buffer) {
    vertexBuffer = buffer;
}

void DrawCall::SetIndexBuffer(const GPUBuffer* buffer) {
    indexBuffer = buffer;
}

void DrawCall::AddTexture(unsigned int textureID) {
    textures.push_back(textureID);
}

void DrawCall::Execute() const {
    if(!pipeline || !vertexBuffer) return;
    
    pipeline->Bind();
    vertexBuffer->Bind();
    
    if(indexBuffer) indexBuffer->Bind();
    
    for(size_t i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }

    if(indexBuffer) {
        glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertexBuffer->GetCount());
    }
}