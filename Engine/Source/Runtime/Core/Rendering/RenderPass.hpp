#pragma once
#include <vector>

class DrawCall;

class RenderPass {
public:
    void AddDrawCall(const DrawCall& drawCall);
    void Execute() const;

private:
    std::vector<DrawCall> drawCalls;
};
