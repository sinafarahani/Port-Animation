#include "Crane.h"

Crane::Crane(Window& wnd, Rgph::BlurOutlineRenderGraph& rg)
	:
	wnd(wnd),
	rg(rg)
{
	crane.LinkTechniques(rg);
}

void Crane::show_panel()
{
	ImGui::Begin("Crane");
		ImGui::SliderFloat("time it takes to move each container", &time, 0.1f, 20.f);
	ImGui::End();
	
}

void Crane::render()
{
	move();
	for (int i = 1926; i < 1958; i++) {
		auto& tf = CraneProbe.get_tf_child(crane, i);
		tf.y = y;
	}
	for (int i = 1448; i < 1972; i++) {
		auto& tf = CraneProbe.get_tf_child(crane, i);
		tf.yRot = yrot;
		tf.x = x;
		tf.z = z;
	}
	crane.Submit(0b1);
}

void Crane::move()
{
	y_speed = (5.f / (time / 6)) / 144;
	if (contained) {
		if (y == 0) {
			rotate();
		}
		else if (y < 0) {
			y += y_speed;
		}
		else {
			y = 0;
			rotated = !rotated;
		}
	}
	else {
		if (y == -5.f) {
			contain();
		}
		else if (y > -5.f) {
			y -= y_speed;
		}
		else {
			y = -5.f;
		}
	}
}

void Crane::rotate()
{
	x_speed = (16.4f / (time / 6)) / 144;
	z_speed = (0.85f / (time / 6)) / 144;
	rot_speed = (PI / (time / 6)) / 144;
	if (x == 0 && z == 0 && yrot == 0 && rotated) {
		contained = false;
	}if (x == -16.4f && z == 0.85f && yrot == PI && !rotated) {
		contained = false;
	}
	if (rotated) {
		if (x < 0) {
			x += x_speed;
		}
		else {
			x = 0;
		}
		if (z > 0) {
			z -= z_speed;
		}
		else {
			z = 0;
		}
		if (yrot > 0) {
			yrot -= rot_speed;
		}
		else {
			yrot = 0;
		}
	}
	else {
		if (x > -16.4f) {
			x -= x_speed;
		}
		else {
			x = -16.4f;
		}
		if (z < 0.85f) {
			z += z_speed;
		}
		else {
			z = 0.85f;
		}
		if (yrot < PI) {
			yrot += rot_speed;
		}
		else {
			yrot = PI;
		}
	}
}

void Crane::contain()
{
	contained = true;
	rotated != rotated;
}
