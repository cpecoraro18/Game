#include "RenderComponent.h"

RenderComponent::RenderComponent(int srcx, int srcy, int srcw, int srch, int destx, int desty, int destw, int desth, int nFrames, int frameSpeed,
	const char* tex, GameDataRef data): data(data), frames(nFrames), speed(frameSpeed) {
	src.x = srcx;
	src.y = srcy;
	src.w = srcw;
	src.h = srch;

	dest.x = destx;
	dest.y = desty;
	dest.w = destw;
	dest.h = desth;
	if (nFrames > 1) {
		animated = true;
	}
	else {
		animated = false;
	}

	texture = data->texmanager.GetTexture(tex);
}


void RenderComponent::Update() {


}

void RenderComponent::Draw(int angle) {
	data->texmanager.Draw(texture, src, dest, data->renderer, angle);
}