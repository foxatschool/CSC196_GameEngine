#include "EnginePCH.h"
#include "MeshRenderer.h"
#include "Renderer/Mesh.h"


void shovel::MeshRenderer::Update(float dt)
{
	//
}

void shovel::MeshRenderer::Draw(Renderer& renderer)
{
	auto mesh = Resources().Get<Mesh>(meshName);
	if (mesh)
	{
		mesh->Draw(renderer, owner->transform);
	}
}
