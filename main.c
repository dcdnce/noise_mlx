#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mlx.h"
#include "noise.h"

unsigned long long	frameCount = 0;
const	int			scale = 10;

int	loop(void *param)
{
	(void) param;
	memset(g_n.img.addr, 0, sizeof(int) * W * H);

	const int	numSteps = W;
	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};

	for (int i = 0 ; i < numSteps - 1; ++i) {
		a.x = ((float)i / ((float)numSteps - 1) * D_kMaxVertices);
		a.y = eval(a.x);
		// printf("Noise at %f : %f\n", a.x, a.y);
		v_old = v;
		v.x = (i * W / numSteps) + frameCount * 2; //x
		v.x = fmodf(v.x, W);
		v.y = ((H + scale) / 2 - a.y * scale); //10
		// if (v_old.x + v_old.y != 0)
		// 	dda(v_old, v);

		// v.y.g = v.y * g.max / 800
		// v.y.b = v.y * b.max / 800
		pixelPut(&g_n.img, v.x, v.y, 0x0067b4f8);
	}

	frameCount++;
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	return (0);
}

int	main(void) {
	initMlx();

	valueNoise1D(2011);

	mlx_loop_hook(g_n.mlx.body, loop, NULL);

	mlx_loop(g_n.mlx.body);
};
