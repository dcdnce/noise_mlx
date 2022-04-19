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

	const int	scale = 100;
	const int	numSteps = W / 4;
	t_vec2f		a = {0};
	t_vec2f		v = {0};
	t_vec2f		v_old = {0};
	int			color;

	for(int j = 0 ; j < 4 ; j++) {
		color = ft_create_trgb(0, j * 50, 100 + j * 40, 255);
		for (int i = 0 ; i < numSteps; ++i) {
			a.x = ((float)i / ((float)numSteps - 1) * D_kMaxVertices);
			a.y = eval(a.x);

			v_old = v;
			//v.x = (i * W / numSteps); //fullscreen
			v.x = i + (W / 4 * j);
			v.y = (H + scale) / 2 - a.y * scale;
			//if (v_old.x + v_old.y != 0)
				//dda(v_old, v);
			pixelPut(&g_n.img, v.x, v.y, color, 3);
		}
	}
	
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	//mlx_loop_hook(g_n.mlx.body, loop, NULL);
	mlx_loop(g_n.mlx.body);
};
