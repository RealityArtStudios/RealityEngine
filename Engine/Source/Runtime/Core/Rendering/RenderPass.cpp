#include "RenderPass.hpp"
#include "DrawCall.hpp"

void RenderPass::AddDrawCall(const DrawCall& drawCall) {
    drawCalls.push_back(drawCall);
}

void RenderPass::Execute() const {
    for(const auto& drawCall : drawCalls) {
        drawCall.Execute();
    }
}