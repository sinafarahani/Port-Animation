#include "AGV.h"

void AGV::show_panel()
{
	ImGui::Begin("Vehicle");
	ImGui::SliderFloat("Time between two vehicle", &time, 1.f, 60.f);
	ImGui::SliderFloat("Speed", &speed, 0.f, 1.f);
	ImGui::SliderInt("Capacity", &capacity, 1, 10);
	ImGui::End();
}

void AGV::move()
{
	if (full) {
		if (pos.x < storage.x) {
			pos.x += speed;
		}
		else if (pos.z < storage.z) {
			if (pitch < 180) {
				pitch += speed;
			}
			else {
				pos.z += speed;
			}
		}
		else {
			t.Mark();
			waiting = true;
		}
	}
	else if(!full && !waiting) {
		if (pos.x < crane.x) {
			pos.x -= speed;
		}
		else if (pos.z < crane.z) {
			if (pitch > 0) {
				pitch -= speed;
			}
			else {
				pos.z -= speed;
			}
		}
		else {
			check_load();
		}
	}
	else {
		if (t.Peek() > time) {
			waiting = false;
			full = false;
		}
	}
}

void AGV::check_load()
{

}
