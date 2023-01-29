#include "Crane.h"

Crane::Crane(Window& wnd, Rgph::BlurOutlineRenderGraph& rg, int& ship_n_c, int& AGV_n_c, bool& ship_load, bool& AGV_load, std::vector<Container>& v)
	:
	wnd(wnd),
	rg(rg),
	ship_n_c(ship_n_c),
	AGV_n_c(AGV_n_c),
	ship_load(ship_load),
	AGV_load(AGV_load),
	v(v)
{
	crane.LinkTechniques(rg);
}

void Crane::show_panel()
{
	ImGui::Begin("Crane");
		ImGui::SliderFloat("time it takes to move each container", &time, 5.f, 30.f);
	ImGui::End();
}

void Crane::show_stats()
{
	std::stringstream tmp;
	std::string tmpp;
	tmp << (counter / 144);
	tmpp = "crane waiting: " + tmp.str() + " seconds!";
	
	std::stringstream tmp2;
	std::string tmpp2;
	tmp2 << containers_handled;
	tmpp2 = "Containers handled: " + tmp2.str();

	ImGui::Begin("Stats");
	ImGui::Text(tmpp.c_str());
	ImGui::Text(tmpp2.c_str());
	ImGui::End();
}

void Crane::render()
{
	move();
	show_stats();
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
	if (handling) {
		v[ship_n_c].takeControl(x, (y + yOffset), (zOffset), 0, yrot, 0);
	}
	crane.Submit(0b1);
	if (!AGV_load || !ship_load) {
		counter++;
	}
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
	else if(AGV_load){
		if (ship_load || !first) {
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
}

void Crane::rotate()
{
	x_speed = (16.4f / (time / 6)) / 144;
	z_speed = (0.85f / (time / 6)) / 144;
	rot_speed = (PI / (time / 6)) / 144;
	if (x == 0 && z == 0 && yrot == 0 && rotated && AGV_load) {
		contained = false;
	}if (x == -16.4f && z == 0.85f && yrot == PI && !rotated && ship_load) {
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
			if (zOffset < 1.2) {
				zOffset += 0.005f;
			}
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
			if (zOffset > 0.f) {
				zOffset -= 0.005f;
			}
		}
		else {
			yrot = PI;
		}
	}
}

void Crane::contain()
{
	contained = true;
	handling = !handling;
	first = false;
	if (x == 0 && z == 0 && yrot == 0) {
		AGV_n_c++;
	}if (x == -16.4f && z == 0.85f && yrot == PI) {
		ship_n_c--;
		yOffset += 1.5f;
		if (ship_n_c <= 0) {
			yOffset = 7.f;
		}
		containers_handled++;
	}
	rotated != rotated;
}
