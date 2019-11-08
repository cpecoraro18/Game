#include "Button.h"

Button::Button(GameDataRef data, float x, float y, float w, float h):data(data) {
	src.x = src.y = 0;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	src.h = 32;
	src.w = 32;

}
Button::Button(GameDataRef data, float x, float y, float h, float w, int nFrames, int frameSpeed): data(data) {
	src.x = src.y = 0;
	dest.x = x;
	dest.y = y;
	dest.h = dest.w = 45;
	src.h = 32;
	src.w = 32;

	animated = true;
	frames = nFrames;
	speed = frameSpeed;
}
void Button::loadtexture(const char* path, const char* name, int tilex, int tiley) {
	data->texmanager.LoadTexture(path, name, data->renderer);
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Button::loadtexture(const char* name, int tilex, int tiley) {
	this->texture = data->texmanager.GetTexture(name);
	src.x = tilex;
	src.y = tiley;
}
void Button::update() {

}
void Button::draw() {
	data->texmanager.Draw(texture, src, dest, data->renderer);
}
void Button::handleClick() {
	src.x = 32;

}