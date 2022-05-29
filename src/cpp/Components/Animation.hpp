#pragma once

// Will be handling all the animations
struct Animation
{
	int index;
	int frames;
	int speed;

	~Animation() {}
	Animation() {}
	Animation(int i, int f, int s)
	{
		this->index = i;
		this->frames = f;
		this->speed = s;
	}
};

class AnimationMap
{
public:
	std::map<const char *, Animation> animations;
	const char* key = "";
	AnimationMap() {}
	~AnimationMap() {}
};
