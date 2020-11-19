#include "tree.h"

#include "mesh_component.h"
#include "box_component.h"
#include "mesh.h"

Tree::Tree(Gfw* gfw, Gfw::Layer layer)
	: Actor{ gfw, layer },
	mBox{ nullptr }
{
	auto mc = new MeshComponent{ this, "Assets/tree.gpmesh" };
	mBox = new BoxComponent{ this };
	mBox->SetObjectBox(mc->GetMesh()->GetBox());

	SetScale(0.1f);
}