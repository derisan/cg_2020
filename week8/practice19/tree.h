#pragma once
class Tree
{
public:
	Tree();
	~Tree();

	void Update(float dt);
	void Draw(class Shader* shader);
	void Load();

	void ScalingBush(float dt);

private:
	class Cube* mRoot;
	class Cube* mBush;

	float mSpeed;
};

