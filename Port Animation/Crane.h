#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Window.h"
#include "BlurOutlineRenderGraph.h"
#include "ChiliMath.h"
#include "Container.h"

class Crane{
public:
	Crane(Window& wnd, Rgph::BlurOutlineRenderGraph& rg, int& ship_n_c, int& AGV_n_c, bool& ship_load, bool& AGV_load, std::vector<Container>& v);

	void show_panel();
	void show_stats();
	void render();
	void move();
private:
	void rotate();
	void contain();

	float time = 20.f;
	MP CraneProbe{ "Crane" };

	int& ship_n_c;
	int& AGV_n_c;
	bool& ship_load;
	bool& AGV_load;

	float yrot = PI;
	float x = -16.4f;
	float y = 0;
	float z = 0.85f;
	float x_speed = (16.4f / (time / 6)) / 144;
	float y_speed = (-5.f / (time / 6)) / 144;
	float z_speed = (0.85f / (time / 6)) / 144;
	float rot_speed = (PI / (time / 6)) / 144;

	float yOffset = 7.f;
	float zOffset = 0.f;

	bool rotated = false;
	bool contained = false;
	bool first = true;
	int containers_handled = 0;
	bool handling = false;
	long int counter = 0;
	std::vector<Container>& v;

	Window& wnd;
	Rgph::BlurOutlineRenderGraph& rg;

	Model crane{ wnd.Gfx(),"Models\\Crane.obj",1.0f / 10.0f };

};
