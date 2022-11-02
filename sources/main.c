/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:16:32 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 19:20:29 by pforesti         ###   ########.fr       */
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
	if (ac != 2)
	{
		printf("Please enter a valid seed.\n");
		return (-1);
	}

	initMlx();

	noise2D(atoi(av[1]));	
	
	mlx_put_image_to_window(g_n.mlx.body, g_n.mlx.win, g_n.img.img, 0, 0);
	mlx_hook(g_n.mlx.win, 17, 0, quit, &g_n);
	//mlx_loop_hook(g_n.mlx.body, loop, NULL);
	mlx_loop(g_n.mlx.body);
}
