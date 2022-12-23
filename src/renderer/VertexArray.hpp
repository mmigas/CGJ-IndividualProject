#pragma once

class VertexArray {
private:
    GLuint id;
    std::vector<Vertex> vertices;
public:
    VertexArray();
};
