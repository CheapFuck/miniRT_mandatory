/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:44:16 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:03:13 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Compute the shadow factor for a given point
double	compute_shadow_factor(t_vector hit_point, t_light light,
			t_scene *scene, int num_samples)
{
	int			unblocked_rays;
	int			i;
	t_ray		shadow_ray;
	double		light_distance;

	unblocked_rays = 0;
	i = 0;
	while (i < num_samples)
	{
		shadow_ray = generate_shadow_ray(hit_point, light);
		light_distance = compute_distance(random_point_on_light(light),
				hit_point);
		if (!is_in_shadow(&shadow_ray, scene, light_distance))
			unblocked_rays++;
		i++;
	}
	return ((double)unblocked_rays / num_samples);
}

static t_color	compute_ambient_light(t_color light_contribution,
	double ambient_ratio)
{
	light_contribution.r = 255 * ambient_ratio;
	light_contribution.g = 255 * ambient_ratio;
	light_contribution.b = 255 * ambient_ratio;
	return (light_contribution);
}

static t_color	compute_light_contribution(t_vector hit_point, t_vector normal,
	t_light light, t_scene *scene)
{
	t_vector	light_dir;
	double		shadow_factor;
	double		diffuse_intensity;
	t_color		contribution;

	contribution = (t_color){0, 0, 0};
	shadow_factor = compute_shadow_factor(hit_point, light, scene, SAMPLES);
	if (shadow_factor > 0)
	{
		light_dir = normalize(subtract(light.pos, hit_point));
		diffuse_intensity = fmax(0.0, dot(normal, light_dir))
			* light.brightness * shadow_factor;
		contribution.r = 255 * diffuse_intensity;
		contribution.g = 255 * diffuse_intensity;
		contribution.b = 255 * diffuse_intensity;
	}
	return (contribution);
}

t_color	apply_lighting(t_vector hit_point, t_vector normal,
	t_color object_color, t_scene *scene)
{
	int			i;
	t_color		light_contribution;
	t_color		current_contribution;

	light_contribution = compute_ambient_light((t_color){0, 0, 0},
			scene->ambient.ratio);
	i = 0;
	while (i < scene->num_lights)
	{
		current_contribution = compute_light_contribution(hit_point, normal,
				scene->lights[i], scene);
		light_contribution.r += current_contribution.r;
		light_contribution.g += current_contribution.g;
		light_contribution.b += current_contribution.b;
		i++;
	}
	return (combine_color(light_contribution, object_color));
}

t_vector	compute_reflection(t_vector light_dir, t_vector normal)
{
	t_vector	scaled_normal;

	scaled_normal = multiply_scalar(normal, 2.0 * dot(normal, light_dir));
	return (subtract(scaled_normal, light_dir));
}
