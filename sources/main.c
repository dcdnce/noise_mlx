/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:16:32 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 19:40:21 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

t_noise	g_n;

static int	quit(void)
{
	exit(EXIT_FAILURE);
}

static int	loop(void *param)
{
	(void) param;
	//memset(g_n.img.addr, 0, sizeof(int) * W * H);

	//mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	//Error handling
	if (ac != 3 \
		|| (strcmp("1d", av[1]) && strcmp("2d", av[1])))
	{
		printf("Bad arguments.\n"\
			"Usage: [dimension {\"1d\"-\"2d\"}] [seed {int}]\n");
		return (-1);
	}

	//Init the minilibx library
	initMlx();

	//Which tool
	if (!strcmp(av[1], "1d"))
		noise1D(atoi(av[2]));	
	else
		noise2D(atoi(av[2]));	
	
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	mlx_hook(g_n.mlx.win, 17, 0, quit, &g_n);
	//mlx_loop_hook(g_n.mlx.body, loop, NULL);
	mlx_loop(g_n.mlx.body);
}
