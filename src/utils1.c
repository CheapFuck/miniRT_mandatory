/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:45:15 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:01:56 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	exit_with_error(const char *msg)
{
	if (msg)
		fprintf(stderr, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
