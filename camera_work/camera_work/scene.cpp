#include "scene.h"

Scene::Scene(Gfw* gfw)
	: mGfw{ gfw },
	mState{ State::kActive }
{

}