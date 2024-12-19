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

void parse_discs(char *line, t_scene *scene)
{
    t_disc disc;

    char **tokens = ft_split(line, ' ');
    if (!tokens || ft_arraylen(tokens) < 6) {
        fprintf(stderr, "Error: Invalid cylinder format for discs\n");
        ft_free_split(tokens);
        return;
    }
    if (!parse_disc_properties(tokens, &disc)) {
        fprintf(stderr, "Error: Failed to parse cylinder properties\n");
        ft_free_split(tokens);
        return;
    }
    disc.diameter = ft_atof(tokens[3]);
    disc.radius = disc.diameter / 2.0;
    disc.height = ft_atof(tokens[4]);
    if (!parse_color(tokens[5], &disc.color))
		return (handle_parse_error(tokens,
				"Error: Invalid disc color format"));
    t_disc bottom_disc;
    t_vector bottom_offset = multiply_scalar(disc.orientation, -0.5 * disc.height);
    bottom_disc.center = add(disc.center, bottom_offset);
    bottom_disc.normal = disc.orientation;
    bottom_disc.radius = disc.radius;
    bottom_disc.color = disc.color;
    t_disc top_disc;
    t_vector top_offset = multiply_scalar(disc.orientation, 0.5 * disc.height);
    top_disc.center = add(disc.center, top_offset);
    top_disc.normal = disc.orientation;
    top_disc.radius = disc.radius;
    top_disc.color = disc.color;
    if (scene->num_discs + 2 >= 65535) {
        fprintf(stderr, "Error: Maximum number of discs exceeded\n");
        ft_free_split(tokens);
        return;
    }
    scene->discs[scene->num_discs++] = bottom_disc;
    scene->discs[scene->num_discs++] = top_disc;

    printf("Parsed two discs: bottom at (%f, %f, %f), top at (%f, %f, %f)\n",
           bottom_disc.center.x, bottom_disc.center.y, bottom_disc.center.z,
           top_disc.center.x, top_disc.center.y, top_disc.center.z);

    ft_free_split(tokens);
}

