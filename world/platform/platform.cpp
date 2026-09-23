#include "platform.hpp"

void Platform::update(float deltaTime) {
	movementDelta = {0.0f, 0.0f};

	if(!isMoving)
		return;

	const float previousX = position.x;

	position.x += speed * direction * deltaTime;

	if(position.x >= endX){
		position.x = endX;
		direction = -1.0f;
	}else if(position.x <= startX){
		position.x = startX;
		direction = 1.0f;
	}
	movementDelta.x = position.x - previousX;
}