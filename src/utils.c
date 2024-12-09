/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 16:02:06 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:02:07 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	multiply_scalar(t_vector v, double scalar)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

t_vector	normalize(t_vector v)
{
	double		length;
	t_vector	result;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}
