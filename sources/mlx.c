#include <stdio.h>
#include "noise.h"
#include "mlx.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	pixelPut(t_imgdata *img, int x, int y, int color, int size)
{
	char	*dst;

	if ((x >= W || y >= H) || (x < 0 || y < 0))
		return ;
	for (int i = 0 ; i < size ; i++) {
		dst = img->addr + ((y + i) * img->size_line + x * 4);
		*(unsigned int *)dst = color;
		if (size > 1) {
			dst = img->addr + ((y + i) * img->size_line + (x + 1) * 4);
			*(unsigned int *)dst = color;
		}
	}
}

void	initMlx(void) {
	g_n.mlx.body = mlx_init();
	g_n.mlx.win = mlx_new_window(g_n.mlx.body, W, H, "noise");
	g_n.img.img = mlx_new_image(g_n.mlx.body, W, H);
	g_n.img.addr = mlx_get_data_addr(g_n.img.img, &g_n.img.bpp, \
		&g_n.img.size_line, &g_n.img.endian);

}