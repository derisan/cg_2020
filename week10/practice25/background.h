#pragma once

class Background
{
public:
    Background();

    void Draw();
    void Load();
private:
    class Texture* mTexture;
    class VertexArray* mVertexArray;
    class Shader* mShader;
};

