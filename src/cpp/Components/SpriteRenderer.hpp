#pragma once

#include <SDL.h>

#include "Sprite.hpp"
#include "Transform.hpp"

class SpriteRenderer
{
public:
	Transform *transform;
	Sprite *sprite;
	SDL_RendererFlip flipState = SDL_FLIP_NONE;

	void Update()
	{
		this->sprite->Update(transform);

		this->sprite->destRect.x = static_cast<int>(transform->position.x);
		this->sprite->destRect.y = static_cast<int>(transform->position.y);
		this->sprite->destRect.w = this->transform->scale.x * this->transform->width;
		this->sprite->destRect.h = this->transform->scale.y * this->transform->height;
	}

	void Draw()
	{
		TextureManager::Draw(this->sprite->texture, this->sprite->srcRect, this->sprite->destRect, this->flipState);
	}

	void Play(const char *key)
	{
		this->sprite->Play(key);
	}
};
