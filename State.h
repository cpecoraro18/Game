#pragma once

class State {
public:
	virtual ~State() {};
	virtual bool Init() = 0;
	virtual void HandleInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Identify()  { printf("State"); } 
	virtual void Pause() {}
	virtual void Resume() {}

};