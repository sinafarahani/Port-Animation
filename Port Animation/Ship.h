#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Timer.h"
#include "Window.h"
#include "BlurOutlineRenderGraph.h"
#include "ChiliMath.h"
#include "Container.h"
#include "Mesh.h"
#include <vector>

class Ship{
public:
    Ship(Window& wnd , Rgph::BlurOutlineRenderGraph& rg);

    void show_panel();
    void move();
    void render();

private:
    void check_load();
    void reset(auto& tf);
    void create_containers();
    int capacity = 1;
    int user_capacity;
    float arrivalTime = 10.f;
    float speed = 0.05f;
    DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
    DirectX::XMFLOAT3 rot = { 0.0f,0.0f,0.0f };
    DirectX::XMFLOAT3 crane = { 0.0f, 0.0f, 0.0f };
    float roll = 0.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;

    const float outbound = 150.f;

    bool loading = false;
    bool waiting = false;
    bool container_created = false;
    MP ShipProbe{ "Ship" };
    Timer t;

    Window& wnd;
    Rgph::BlurOutlineRenderGraph& rg;

    Model ship{ wnd.Gfx(),"Models\\Ship\\Cargo Ship 06a.obj",6.0f };
    std::vector<Container> container;
};
