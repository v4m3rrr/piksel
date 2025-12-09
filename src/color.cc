#include "piksel/color.hh"

namespace piksel {
	const Color Color::Red{ glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	const Color Color::Green{ glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) };
	const Color Color::Blue{ glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) };
	const Color Color::Black{ glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	const Color Color::White{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) };
}
