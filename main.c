#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mlx.h"
#include "noise.h"

t_noise	g_n;

int	loop(void *param)
{
	(void) param;
	//memset(g_n.img.addr, 0, sizeof(int) * W * H);

	//mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	return (0);
}

int	main(void) {
	initMlx();

	//noise1D();	
	noise2D();	
	
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	//mlx_loop_hook(g_n.mlx.body, loop, NULL);
	mlx_loop(g_n.mlx.body);
};
