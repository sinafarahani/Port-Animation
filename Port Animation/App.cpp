#include "App.h"
#include <algorithm>
#include "ChiliMath.h"
#include "imgui/imgui.h"
#include "ChiliUtil.h"
#include "Testing.h"
#include "PerfLog.h"
#include "Testing.h"
#include "Camera.h"
#include "Channels.h"

namespace dx = DirectX;

App::App(const std::string& commandLine)
	:
	commandLine(commandLine),
	wnd(1280, 720, "Test App"),
	scriptCommander(TokenizeQuoted(commandLine)),
	light(wnd.Gfx(), { 10.0f,5.0f,0.0f }),
	ship(wnd, rg),
	crane(wnd, rg),
	vehicle(wnd, rg)
{
	cameras.AddCamera( std::make_unique<Camera>( wnd.Gfx(),"A",dx::XMFLOAT3{ -13.5f,6.0f,3.5f },0.0f,PI / 2.0f ) );
	//cameras.AddCamera( light.ShareCamera() );

	//cube.SetPos( { 10.0f,5.0f,6.0f } );
	
	//cube.LinkTechniques( rg );
	light.LinkTechniques( rg );
	sponza.LinkTechniques( rg );
	cameras.LinkTechniques( rg );

	rg.BindShadowCamera( *light.ShareCamera() );
}

void App::HandleInput( float dt )
{
	while( const auto e = wnd.kbd.ReadKey() )
	{
		if( !e->IsPress() )
		{
			continue;
		}

		switch( e->GetCode() )
		{
		case VK_ESCAPE:
			if( wnd.CursorEnabled() )
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_RETURN:
			savingDepth = true;
			break;
		}
	}

	if( !wnd.CursorEnabled() )
	{
		if( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			cameras->Translate( { 0.0f,0.0f,dt } );
		}
		if( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			cameras->Translate( { -dt,0.0f,0.0f } );
		}
		if( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			cameras->Translate( { 0.0f,0.0f,-dt } );
		}
		if( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			cameras->Translate( { dt,0.0f,0.0f } );
		}
		if( wnd.kbd.KeyIsPressed( VK_SPACE ) )
		{
			cameras->Translate( { 0.0f,dt,0.0f } );
		}
		if( wnd.kbd.KeyIsPressed( VK_CONTROL ) )
		{
			cameras->Translate( { 0.0f,-dt,0.0f } );
		}
	}

	while( const auto delta = wnd.mouse.ReadRawDelta() )
	{
		if( !wnd.CursorEnabled() )
		{
			cameras->Rotate(((float)delta->x) / 4, ((float)delta->y) / 4);
		}
	}
}

void App::DoFrame( float dt )
{
	wnd.Gfx().BeginFrame( 0.07f,0.0f,0.12f );
	light.Bind( wnd.Gfx(),cameras->GetMatrix() );
	rg.BindMainCamera( cameras.GetActiveCamera() );
		
	//light.Submit( Chan::main );
	//cube.Submit( Chan::main );
	//sponza.Submit( Chan::main );
	cameras.Submit( Chan::main );

	
	//sponza.Submit( Chan::shadow );
	//cube.Submit( Chan::shadow );
	//sponza.Submit( Chan::shadow );

	
	
	// imgui windows
	sponzeProbe.SpawnWindow( sponza );
	bool test = false;
	auto& tf = sponzeProbe.get_tf_child(sponza, 0);
	if (!test) {
		if (tf.x < 50) {
			tf.x++;
		}
	}
	if (tf.x >= 50)
		test = true;
	if(test) {
		auto& tf2 = sponzeProbe.get_tf_root(sponza);
		if (tf2.x < 50) {
			tf2.x++;
		}
	}
	auto& tf3 = sponzeProbe.get_tf_child(sponza, 5);
	
	//cameras.SpawnWindow( wnd.Gfx() );
	//light.SpawnControlWindow();
	//cube.SpawnControlWindow( wnd.Gfx(),"Cube 1" );
	
	if (ImGui::Begin("Animation"))
	{
		if (!Start) {
			if (ImGui::Button("Start"))
			{
				Start = true;
			}
		}
		else {
			if (ImGui::Button("Stop"))
			{
				Start = false;
			}
		}
	}
	ImGui::End();
	if (!Start) {
		crane.show_panel();
		vehicle.show_panel();
		ship.show_panel();
	}
	else {
		ship.render();
		crane.render();
		vehicle.move();
	}
	
	//rg.RenderWindows( wnd.Gfx() );

	// present
	rg.Execute(wnd.Gfx());
	wnd.Gfx().EndFrame();
	rg.Reset();
}


App::~App()
{}

int App::Go()
{
	while( true )
	{
		// process all messages pending, but to not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		const auto dt = timer.Mark() * speed_factor;
		HandleInput( dt );
		DoFrame( dt );
	}
}