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
#include <math.h>  // for sqrt and isnan

t_vector normalize(t_vector v)
{
    double length;
    t_vector result;

    // Check if any component of the vector is NaN or invalid
    if (isnan(v.x) || isnan(v.y) || isnan(v.z)) {
        // Handle the invalid case
        result.x = 0;
        result.y = 0;
        result.z = 0;
        return result;
    }

    // Calculate the length of the vector
    length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    // Check for zero-length vector
    if (length == 0) {
        // Handle zero-length vector
        result.x = 0;
        result.y = 0;
        result.z = 0;
        return result;
    }

    // Proceed with normalization
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;

    return result;
}
