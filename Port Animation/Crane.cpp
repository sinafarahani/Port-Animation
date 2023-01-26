#include "Crane.h"

void Crane::show_panel()
{
	ImGui::Begin("Crane");
		ImGui::SliderFloat("time it takes to move each container", &time, 0.1f, 20.f);
	ImGui::End();
}

void Crane::move()
{
}
