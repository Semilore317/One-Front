#include "game/controls.hpp"

#include "raylib.h"
#include <iostream>

namespace {
bool expect(bool condition, const char *description) {
	if (condition)
		return true;

	std::cerr << description << '\n';
	return false;
}

bool expect_binding(const KeyBinding &binding,
                    int primary,
                    int alternate,
                    const char *description) {
	return expect(binding.primary == primary && binding.alternate == alternate,
	              description);
}
} // namespace

int main() {
	bool passed = true;
	passed &= expect_binding(
	    Keyboard_Controls.left, KEY_A, KEY_LEFT, "left bindings should match");
	passed &= expect_binding(Keyboard_Controls.right,
	                         KEY_D,
	                         KEY_RIGHT,
	                         "right bindings should match");
	passed &= expect_binding(
	    Keyboard_Controls.jump, KEY_W, KEY_UP, "jump bindings should match");
	passed &= expect_binding(
	    Keyboard_Controls.down, KEY_S, KEY_DOWN, "down bindings should match");
	passed &= expect_binding(Keyboard_Controls.attack1,
	                         KEY_J,
	                         KEY_Z,
	                         "primary attack bindings should match");
	passed &= expect_binding(Keyboard_Controls.attack2,
	                         KEY_K,
	                         KEY_X,
	                         "secondary attack bindings should match");
	passed &= expect_binding(Keyboard_Controls.attack3,
	                         KEY_L,
	                         KEY_C,
	                         "tertiary attack bindings should match");

	return passed ? 0 : 1;
}
