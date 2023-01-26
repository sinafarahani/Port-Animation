#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Timer.h"

class Ship{
public:
    void show_panel();
    void move();
    void render();

private:
    void check_load();
    void reset_position();

    int capacity = 150;
    float arrivalTime = 10.f;
    float speed = 10.f;
    DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
    DirectX::XMFLOAT3 crane = { -20.0f,1.0f,-30.0f };
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    const float outbound = 150.f;

    bool loading = false;
    bool waiting = false;
    MP ShipProbe{ "Ship" };
    Timer t;
};
