#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mlx.h"
#include "noise.h"

int	loop(void *param)
{
	(void) param;
	//memset(g_n.img.addr, 0, sizeof(int) * W * H);

	//mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	return (0);
}

int	main(void) {
	initMlx();

	valueNoise1D(2011);

	const int	amplitude = 50;
	const int	numSteps = W;
	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};
	int			color;
	color = ft_create_trgb(0, 50, 100, 255);

	for (int i = 0 ; i < numSteps; ++i) {
		a.x = ((float)i / ((float)numSteps - 1) * D_kMaxVertices);
		a.y = eval(a.x);

		v_old = v;
		v.x = (i * W / numSteps);
		v.y = (H + amplitude) / 2 - a.y * amplitude;
		if (v_old.x + v_old.y != 0)
			dda(v_old, v, 10);
		//pixelPut(&g_n.img, v.x, v.y, color, 10);
	}
	
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	//mlx_loop_hook(g_n.mlx.body, loop, NULL);
	mlx_loop(g_n.mlx.body);
};
