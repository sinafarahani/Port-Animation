#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Timer.h"
#include "Window.h"
#include "BlurOutlineRenderGraph.h"
#include "ChiliMath.h"

class Crane{
public:
	Crane(Window& wnd, Rgph::BlurOutlineRenderGraph& rg);

	void show_panel();
	void render();
	void move();
private:
	void rotate();
	void contain();

	float time = 10.f;
	MP CraneProbe{ "Crane" };
	Timer t;

	float yrot = PI;
	float x = -16.4f;
	float y = 0;
	float z = 0.85f;
	float x_speed = (16.4f / (time / 6)) / 144;
	float y_speed = (-5.f / (time / 6)) / 144;
	float z_speed = (0.85f / (time / 6)) / 144;
	float rot_speed = (PI / (time / 6)) / 144;
	bool rotated = false;
	bool contained = false;

	Window& wnd;
	Rgph::BlurOutlineRenderGraph& rg;

	Model crane{ wnd.Gfx(),"Models\\Crane.obj",1.0f / 10.0f };

};
