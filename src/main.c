#include "base.h"
#include "math.h"
#include "frame.h"
#include "renderer.h"

const vec3f vs[] = {
	{ .x =  0.5f, .y =  0.5f, .z = 0.5f },
	{ .x = -0.5f, .y =  0.5f, .z = 0.5f },
	{ .x = -0.5f, .y = -0.5f, .z = 0.5f },
	{ .x =  0.5f, .y = -0.5f, .z = 0.5f },

	{ .x =  0.5f, .y =  0.5f, .z = -0.5f },
	{ .x = -0.5f, .y =  0.5f, .z = -0.5f },
	{ .x = -0.5f, .y = -0.5f, .z = -0.5f },
	{ .x =  0.5f, .y = -0.5f, .z = -0.5f },
};

#define DEL 0xFFFF

const uint16_t fs[] = {
	0, 1, 2, 3, DEL,
	4, 5, 6, 7, DEL,
	0, 4, DEL,
	1, 5, DEL,
	2, 6, DEL,
	3, 7, DEL,
	DEL,
};

float angle = 0;

// TODO: fix the drawLinef function
void update(void) {
	// TODO: get the actual dt
	const float dt = 1/60.0f;
	uint16_t start;

	angle += 0.5f*PI*dt;
	if (angle > DEG2RAD(360.0f)) angle = 0.0f;

	for (uint32_t idx = 0; idx < FRAME_WIDTH*FRAME_HEIGHT; idx += 1) {
		frame_buffer[0][idx] = RGBA(0, 0, 0, 0);
	}

	start = fs[0];
	for (uint16_t idx = 0; idx < sizeof(fs)/sizeof(fs[0]); idx += 1) {
		vec3f a;
		vec3f b;
		uint16_t end_idx;

		if (start == DEL) break;

		a = vs[fs[idx]];

		a = rotate_xz(a, angle);
		a = rotate_yz(a, angle);
		a = rotate_xy(a, angle);

		a.z += 5.0f;

		end_idx = fs[idx + 1];
		if (end_idx == DEL) {
			end_idx = start;
			idx += 1;
			start = fs[idx + 1];
		}

		b = vs[end_idx];

		b = rotate_xz(b, angle);
		b = rotate_yz(b, angle);
		b = rotate_xy(b, angle);

		b.z += 5.0f;

		drawLinef(screenf(project(a)), screenf(project(b)), RGB(255, 0, 255));
	}

	for (uint16_t idx = 0; idx < sizeof(vs)/sizeof(vs[0]); idx += 1) {
		const uint8_t mag = 256/(sizeof(vs)/sizeof(vs[0]));

		vec3f v = vs[idx];

		v = rotate_xz(v, angle);
		v = rotate_yz(v, angle);
		v = rotate_xy(v, angle);

		v.z += 5.0f;

		putPoint(screen(project(v)), RGB(255, ((idx+1) * mag) - 1, 255));
	}

	frame_buffer[0][0] = 0xFF0000FF;
	frame_buffer[0][1] = 0xFF00FF00;
	frame_buffer[0][2] = 0xFFFF0000;
}

