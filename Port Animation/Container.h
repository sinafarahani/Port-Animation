#pragma once

#include "Window.h"
#include "BlurOutlineRenderGraph.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"

class Container {
public:
	Container(Window& wnd, Rgph::BlurOutlineRenderGraph& rg, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot);
	Container(const Container&) = default;
	Container& operator=(const Container&) = default;
	void render();
private:
	Window& wnd;
	Rgph::BlurOutlineRenderGraph& rg;

	Model container{ wnd.Gfx(),"Models\\Container\\12281_Container_v2_L2.obj",1.0f / 200.0f };
};