/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <pforesti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:30:22 by pforesti          #+#    #+#             */
/*   Updated: 2022/11/02 19:21:35 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

/**
 * @brief Apply perlin smoothstep to a value in range [0-1].
 * 
 * @param t 
 * @return float 
 */
static inline float pSmoothstep(float t) {
	return (t * t * (3 - 2 * t));
}

/**
 * @brief Return the value of v in the noiseMap. 
 * Computes the nearest vertices of v according 
 * to the 2D lattice. Interpolates to find the 
 * corresponding value.
 * #####################################################
 * Step 1 - Find the nearest vertices.
 *	C00-----C10
 *	|         |
 *	|   v     |
 *	|         |
 *	C01-----C11
 * #####################################################
 * Step 2 - Use tx to interpolate between the vertices
 *	- the 1st dimension.
 * 	Getting nx0 & nx1.
 *	C00-nx0--C10
 *	|    |     |
 *	|    v     |
 *	|    |     |
 *	C01-nx1--C11
 * #####################################################
 * Step 3 - Use ty to interpolate between nx0 & nx1
 *	- the 2nd dimension
 *	Return the value.
 * #####################################################
 * @param v coordinate on the noiseMap.
 * @return float - Value of the given coords.
 */
float	billinearInterpolation(const t_vec2f v)
{
	/*	Step 1	*/
	int	c00 = (int)v.x + (int)v.y * (int)D_kMaxVertices;
	if (c00 >= D_kMaxVertices * D_kMaxVertices)
		c00 = 0;
	int	c10 = c00 + 1;
	int c01 = c00 + D_kMaxVertices;
	int	c11 = c10 + D_kMaxVertices;
	/*	Step 2	*/
	float tx = v.x - (int)v.x;
	tx = pSmoothstep(tx);
	float nx0 = lerp(g_n.r2[c00], g_n.r2[c10], tx);
	float nx1 = lerp(g_n.r2[c01], g_n.r2[c11], tx);
	/*	Step 3	*/
	float ty = v.y - (int)v.y;
	ty = pSmoothstep(ty);
	return (lerp(nx0, nx1, ty));
}