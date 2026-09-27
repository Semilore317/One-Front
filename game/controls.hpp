#pragma once

struct KeyBinding {
	int primary;
	int alternate;

	[[nodiscard]] bool is_down() const;
	[[nodiscard]] bool is_pressed() const;
};

struct Controls {
	KeyBinding left;
	KeyBinding right;
	KeyBinding jump;
	KeyBinding down;

	KeyBinding attack1;
	KeyBinding attack2;
	KeyBinding attack3;
};

extern const Controls Keyboard_Controls;
