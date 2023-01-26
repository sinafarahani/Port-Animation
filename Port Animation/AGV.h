#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"

class AGV{
public:
    void show_panel();
    void move();

private:
    int capacity = 2;
    float time = 20.f;
    float speed = 10.f;
    DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
    DirectX::XMFLOAT3 storage = { 180.0f,1.0f,150.0f };
    DirectX::XMFLOAT3 crane = { -20.0f,1.0f,-30.0f };
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;
    bool full = false;
};
