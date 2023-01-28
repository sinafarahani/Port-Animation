#include "Ship.h"

Ship::Ship(Window& wnd, Rgph::BlurOutlineRenderGraph& rg)
	:
	wnd(wnd),
	rg(rg)
{
	ship.SetRootTransform(dx::XMMatrixRotationY(PI / 2.f) *
		dx::XMMatrixTranslation(-20.f, 0.f, -100.f));
	ship.LinkTechniques(rg);
}

void Ship::show_panel()
{
	ImGui::Begin("Ship");
	ImGui::SliderFloat("ArrivalTime", &arrivalTime, 0.1f, 60.f);
	ImGui::SliderInt("Capacity", &capacity, 1, 100);
	ImGui::End();
	n_c = capacity;
}

void Ship::move()
{
	auto& tf = ShipProbe.get_tf_root(ship);
	if (!loading && !waiting) {
		tf.z += speed;
		if ((tf.z - speed) < crane.z && (tf.z + speed) > crane.z) {
			loading = true;
			tf.z += 2 * speed;
		}
		if (tf.z > outbound) {
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
			reset(tf);
		}
	}
}

void Ship::render()
{
	if (!container_created) {
		create_containers();
	}
	move();
	if (!waiting) {
		for (auto& c : container) {
			c.render();
		}
		ship.Submit(0b1);
	}
}

void Ship::check_load()
{
	if (n_c <= 0) {
		loading = false;
	}
}

void Ship::reset(auto& tf)
{
	tf.z = -100;
	n_c = capacity;
}

void Ship::create_containers()
{
	for (int i = 0; i < capacity; i++) {
		Container c{ wnd, rg, pos, rot };
		container.push_back(c);
		c.render();
		pos.y += 1.5f;
	}
	container_created = true;
}
