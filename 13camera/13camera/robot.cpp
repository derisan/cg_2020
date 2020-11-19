#include "robot.h"

#include "mesh_component.h"

Robot::Robot(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mBox{ nullptr }
{
	auto mc = new MeshComponent{ this, "Assets/robot.gpmesh" };

	SetScale(0.1f);
	SetPosition(glm::vec3{ 0.0f, -1.0f, 0.0f });
}

void Robot::UpdateActor()
{

}