#include "AGV.h"

AGV::AGV(Window& wnd, Rgph::BlurOutlineRenderGraph& rg)
	:
	wnd(wnd),
	rg(rg)
{
	agv.SetRootTransform(
		dx::XMMatrixTranslation(10.f, 20.f, 1.f)
	);
	agv.LinkTechniques(rg);
}

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
	auto& tf = AGVProbe.get_tf_root(agv);
	agv.Submit(0b1);
	if (tf.zRot >= (1.5f * PI))
		tf.zRot -= (2 * PI);
	if (full && !waiting) {
		if (tf.x < storage.x) {
			if (tf.zRot < (PI))
				tf.zRot += (speed / 4);
			tf.x += speed;
		}
		else if (tf.y < storage.z) {
			if (tf.zRot < (1.5f * PI) && tf.zRot > 0)
				tf.zRot += (speed / 4);
			tf.y += speed;
		}
		else{
			t.Mark();
			waiting = true;
		}
	}
	else if(!full && !waiting) {
		if (tf.x > crane.x) {
			if (tf.zRot < 0)
				tf.zRot += (speed / 4);
			tf.x -= speed;
		}
		else if (tf.y > crane.z) {
			if (tf.zRot < (PI / 2.f))
				tf.zRot += (speed / 4);
			tf.y -= speed;
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
	full = true;
}
