#pragma once
#include "pch.h"
#include "glutils.h"

#include <vector>
// NOTE: Make sure your test meshes use the correct vertex format!

// Shits and giggles
struct SimpleVertex
{
    glm::vec2 position;
    glm::vec3 color;
};

class SimpleMesh
{
public:
    SimpleMesh(const std::vector<SimpleVertex>& __vectices, const std::vector<unsigned int>& __indices);
    std::vector<SimpleVertex> vertices;
    std::vector<unsigned int> indices;

    void Draw();

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};