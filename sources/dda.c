#include "noise.h"
#include <math.h>

void	dda(t_vec2f a, t_vec2f b, const int size, const int color) {
	int		i = 0;
	int		step;
	float	dx = b.x - a.x;
	float	dy = b.y - a.y;

	(fabs(dx) > fabs(dy)) ? (step = fabs(dx)) : (step = fabs(dy));
	dx /= step;
	dy /= step;
	while (i <= step) {
		pixelPut(&g_n.img, a.x, a.y, color, size);
		a.x += dx;
		a.y += dy;
		i += 1;
	}
}