/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: thivan-d <thivan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/19 14:10:57 by thivan-d      #+#    #+#                 */
/*   Updated: 2025/01/19 14:10:59 by thivan-d      ########   odam.nl         */
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
