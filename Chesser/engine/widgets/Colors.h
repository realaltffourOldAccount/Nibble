/**
 * @file Colors.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contians the definition of colors.
 * @version 0.1
 * @date 2019-06-08
 *
 */

namespace GEngine {
namespace Widgets {
namespace Colors {
struct Color {
	float _r, _g, _b, _a;
	Color(float r, float g, float b, float a) {
		this->_r = r;
		this->_g = g;
		this->_b = b;
		this->_a = a;
	}
	Color(void) {
		this->_r = 0.0f;
		this->_g = 0.0f;
		this->_b = 0.0f;
		this->_r = 1.0f;
	}
};

// TODO: Add more Colors.

static Color cl_red = Color(1.0f, 0.0f, 0.0f, 1.0f);
static Color cl_green = Color(0.0f, 1.0f, 0.0f, 1.0f);
static Color cl_blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
static Color cl_invis = Color(0.0f, 0.0f, 0.0f, 0.0f);
static Color cl_black = Color(0.0f, 0.0f, 0.0f, 1.0f);
static Color cl_white = Color(1.0f, 1.0f, 1.0f, 1.0f);

}  // namespace Colors
}  // namespace Widgets
}  // namespace GEngine