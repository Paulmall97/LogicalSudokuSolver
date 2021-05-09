#pragma once

#include <cstdint>

static bool outOfBoundsValue(const uint8_t value) {
	return value > 0 && value <= 9;
}