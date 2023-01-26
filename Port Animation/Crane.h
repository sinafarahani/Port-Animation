#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Timer.h"

class Crane{
public:
	void show_panel();
	void move();
private:
	float time = 10.f;
	DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	MP CraneProbe{ "Crane" };
	Timer t;
};
