#pragma once

#include "imgui/imgui.h"
#include "Model.h"
#include "TestModelProbe.h"
#include "Drawable.h"
#include "Timer.h"
#include "Window.h"
#include "BlurOutlineRenderGraph.h"
#include "ChiliMath.h"

class AGV{
public:
    AGV(Window& wnd, Rgph::BlurOutlineRenderGraph& rg);
    
    void show_panel();
    void move();
    
    int n_c = 0;
    bool loading = false;

private:
    void check_load();

    int capacity = 2;
    
    float time = 10.f;
    float speed = 0.05f;
    DirectX::XMFLOAT3 pos = { 1.0f,1.0f,1.0f };
    DirectX::XMFLOAT3 storage = { 100.0f,1.0f,100.0f };
    DirectX::XMFLOAT3 crane = { -0.0f,1.0f,5.0f };
    MP AGVProbe{ "AGV" };
    Timer t;

    bool full = false;
    bool waiting = false;

    Window& wnd;
    Rgph::BlurOutlineRenderGraph& rg;

    Model agv{ wnd.Gfx(),"Models\\AGV\\scene.gltf",1.0f / 200.0f };
};
