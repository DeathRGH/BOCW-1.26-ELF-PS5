#include "math.h"

#include "functions.h"

double sqrt(double x) {
	if (x <= 0) {
		return 0;
	}

	int exp = 0;
	x = frexp(x, &exp);
	if (exp & 1) {
		exp--;
		x *= 2;
	}

	double y = (1 + x) / 2;
	double z = 0;
	while (y != z) {
		z = y;
		y = (y + x / y) / 2;
	}

	return ldexp(y, exp / 2);
}

float Distance(float *one, float *two) {
	return sqrt(powf(one[0] - two[0], 2) + powf(one[1] - two[1], 2) + powf(one[2] - two[2], 2));
}

void VectorToAngles(const float *forward, float *angles) {
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0) {
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else {
		yaw = (atan2(forward[1], forward[0]) * 180 / MATH_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / MATH_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

float DotProduct(float *view, float *axis) {
	return (view[0] * axis[0]) + (view[1] * axis[1]) + (view[2] * axis[2]);
}
