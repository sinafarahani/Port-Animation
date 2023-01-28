#include "Container.h"

Container::Container(Window& wnd, Rgph::BlurOutlineRenderGraph& rg, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot)
	:
	wnd(wnd),
	rg(rg)
{
	container.LinkTechniques(rg);
	container.SetRootTransform(dx::XMMatrixRotationX(rot.x) *
		dx::XMMatrixRotationY(rot.y) *
		dx::XMMatrixRotationZ(rot.z) *
		dx::XMMatrixTranslation(pos.x, pos.y, pos.z));
}

void Container::render()
{
	container.Submit(0b1);
}
