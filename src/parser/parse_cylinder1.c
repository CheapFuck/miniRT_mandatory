/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:59:46 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:03:27 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	parse_cylinder(char *line, t_scene *scene)
{
	t_cylinder	cylinder;
	char		**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || ft_arraylen(tokens) != 6)
	{
		perror("Error: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(tokens[0], "cy", 2) != 0)
		return (handle_parse_error(tokens, "Error: Invalid cylinder format"));
	if (!parse_cylinder_properties(tokens, &cylinder))
		return (handle_parse_error(tokens,
				"Error: Invalid cylinder properties"));
	cylinder.diameter = ft_atof(tokens[3]);
	cylinder.height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &cylinder.color))
		return (handle_parse_error(tokens,
				"Error: Invalid cylinder color format"));
	cylinder.radius = cylinder.diameter / 2.0;
	if (scene->num_cylinders >= 65536)
		return (handle_parse_error(tokens, "Error: Cylinder array is full\n"));
	scene->cylinders[scene->num_cylinders] = cylinder;
	scene->num_cylinders++;
	clean_2d_array(tokens);
}
