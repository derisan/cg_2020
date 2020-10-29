#pragma once
#include "object.h"
class Line :
    public Object
{
public:
	Line(const glm::vec3& start, const glm::vec3& end);
    ~Line();

    void Update(float dt) override;
    void Draw(class Shader* shader) override;
    void Load() override;

private:
    class VertexArray* mVertexArray;
    
    glm::vec3 mStart;
    glm::vec3 mEnd;
};

