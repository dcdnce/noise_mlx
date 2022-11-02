/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicFractalSum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:06:08 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 19:08:38 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

/**
 * @brief Basic fractal sum function.
 * Summing up the contribution of several noises layers
 * Frequency * lacunarity for each layer. 
 * Scale * gain for each layer.
 * @param v 
 * @param h 
 * @param w 
 */
void	basicFractalSum(t_vec2f	v, int h,  int w)
{
	const int	layers = 5;
	float		scale = 1.0f;
	float		freq = 0.015f;
	float		lacunarity = 1.8f;
	float		gain = 0.35f;
	v.x *= freq;
	v.y *= freq;
	for (int j = 0 ; j < layers ; j++) {
		g_n.noiseMap[w + h * W] += billinearInterpolation(v) * scale;
		scale *= gain;
		v.x *= lacunarity;
		v.y *= lacunarity;
	}
}