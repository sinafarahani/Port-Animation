#include "Ship.h"

void Ship::show_panel()
{
	ImGui::Begin("Ship");
	ImGui::SliderFloat("ArrivalTime", &arrivalTime, 0.1f, 60.f);
	ImGui::SliderInt("Capacity", &capacity, 1, 300);
	ImGui::End();
}

void Ship::move()
{
	pos.x += speed;
}
