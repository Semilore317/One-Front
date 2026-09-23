#pragma once

#include <raylib.h>

struct Platform {
	Vector2 position;
	Vector2 size;

	bool isMoving{false};

	float startX{0.0f};
	float endX{0.0f};
	float speed{0.0f};
	float direction{1.0f};

	Vector2 movementDelta{0.0f, 0.0f};
	
	void update(float deltaTime);

	float left() const { return position.x; }
	float right() const { return position.x + size.x; }
	float top() const { return position.y; }
	float bottom() const { return position.y + size.y; }
};
