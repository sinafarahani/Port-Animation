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
	if (!loading && !waiting) {
		pos.x += speed;
		if (pos.x > outbound) {
			waiting = true;
			t.Mark();
		}
	}
	else if (!waiting) {
		check_load();
	}
	else {
		if (t.Peek() > arrivalTime) {
			waiting = false;
			reset_position();
		}
	}
	if (pos.x >= crane.x) {
		loading = true;
	}
	
}

void Ship::render()
{
	move();
	if (!waiting) {

	}
}

void Ship::check_load()
{

}

void Ship::reset_position()
{
	pos = { 1.0f,1.0f,1.0f };
}
