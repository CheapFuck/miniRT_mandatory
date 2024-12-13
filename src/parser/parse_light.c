/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:47:07 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 15:47:10 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_light_position(char **tokens, t_light *light)
{
	char	**pos;

	pos = split_and_validate(tokens[1], 3);
	if (!pos)
	{
		ft_free_split(pos);
		ft_free_split(tokens);
		exit_with_error("Invalid light position format");
		return (0);
	}
	light->pos.x = ft_atof(pos[0]);
	light->pos.y = ft_atof(pos[1]);
	light->pos.z = ft_atof(pos[2]);
	ft_free_split(pos);
	return (1);
}

int	parse_light_brightness(char **tokens, t_light *light)
{
	light->brightness = ft_atof(tokens[2]);
	if (light->brightness < 0 || light->brightness > 1)
	{
		ft_free_split(tokens);
		exit_with_error("Light brightness out of range (0 to 1)");
		return (0);
	}
	return (1);
}

int	parse_light_color(char **tokens, t_light *light)
{
	char	**color;

	color = split_and_validate(tokens[3], 3);
	if (!color)
	{
		ft_free_split(color);
		ft_free_split(tokens);
		exit_with_error("Invalid light color format");
		return (0);
	}
	light->color.r = ft_atoi(color[0]);
	light->color.g = ft_atoi(color[1]);
	light->color.b = ft_atoi(color[2]);
	if (light->color.r < 0 || light->color.r > 255
		|| light->color.g < 0 || light->color.g > 255
		|| light->color.b < 0 || light->color.b > 255)
	{
		ft_free_split(color);
		ft_free_split(tokens);
		exit_with_error("Light color out of range (0 to 255)");
		return (0);
	}
	ft_free_split(color);
	return (1);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**tokens;
	t_light	light;

	tokens = ft_split(line, ' ');
	if (!tokens || ft_arraylen(tokens) != 4)
	{
		ft_free_split(tokens);
		exit_with_error("Invalid light format");
	}
	if (!parse_light_position(tokens, &light)
		|| !parse_light_brightness(tokens, &light)
		|| !parse_light_color(tokens, &light))
	{
		ft_free_split(tokens);
		return ;
	}
	scene->lights[scene->num_lights] = light;
	scene->num_lights++;
	ft_free_split(tokens);
}

void	parse_ambient(char *line, t_scene *scene)
{
	char	**tokens;
	char	**colors;

	tokens = ft_split(line, ' ');
	if (!tokens || ft_arraylen(tokens) != 3)
		exit_with_error("Invalid ambient light format");
	scene->ambient.ratio = ft_atof(tokens[1]);
	printf("ambient.ratio is: %f\n", scene->ambient.ratio);
	colors = ft_split(tokens[2], ',');
	if (!colors || ft_arraylen(colors) != 3)
		exit_with_error("Invalid ambient color format");
	scene->ambient.color.r = ft_atoi(colors[0]);
	scene->ambient.color.g = ft_atoi(colors[1]);
	scene->ambient.color.b = ft_atoi(colors[2]);
	// printf("ambient.color.r is: %d\n", scene->ambient.color.r);
	// printf("ambient.color.g is: %d\n", scene->ambient.color.g);
	// printf("ambient.color.b is: %d\n", scene->ambient.color.b);

	ft_free_split(tokens);
	ft_free_split(colors);
}
