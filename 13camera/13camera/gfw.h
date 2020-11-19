#pragma once

#include <string>
#include <unordered_map>
#include <stack>

class Gfw
{
public:
	enum Layer
	{
		kPlayer,
		kRobot,
		kObstacle,
		kDefault
	};

	Gfw();

	bool Init(int* argc, char** argv, int w = 1024, int h = 768);
	void Run(bool* keyState, int x, int y);
	void Shutdown();

	void ChangeScene(const std::string& scene);
	void PushScene(const std::string& scene);
	void PopScene();

	void AddActorAt(class Actor* actor, Layer layer);
	void RemoveActorAt(class Actor* actor, Layer layer);
	void RemoveAllActors();

	void AddMesh(class MeshComponent* mesh);
	void RemoveMesh(class MeshComponent* mesh);
	
	// Getters
	bool GetShouldClose() const { return mShouldClose; }
	int GetScrWidth() const { return mScrWidth; }
	int GetScrHeight() const { return mScrHeight; }

	std::vector<class Actor*>& GetActorsAt(Layer layer) { return mActors[layer]; }
	std::vector<class MeshComponent*> GetMeshes() { return mMeshes; }

	// Setters
	void SetShouldClose(bool value) { mShouldClose = value; }

	// Constants
	const float dt{ 16.f / 1000.f };

private:
	void ProcessInput(bool* keyState, int x, int y);
	void Update();
	void Draw();

	std::stack<class Scene*> mScenes;
	std::unordered_map<std::string, class Scene*> mScenesMap;

	std::vector<std::vector<class Actor*>> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class MeshComponent*> mMeshes;

	int mScrWidth;
	int mScrHeight;

	bool mShouldClose;
	bool mIsUpdating;
};

