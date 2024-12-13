/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/13 15:15:54 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/13 15:16:15 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

// Vector operations
t_vector	subtract(t_vector a, t_vector b);
double		dot(t_vector a, t_vector b);
t_vector	normalize(t_vector v);
t_vector	multiply_scalar(t_vector v, double scalar);
t_vector	add(t_vector a, t_vector b);
double		length_squared(t_vector v);

#endif // UTILS_H