#include "../../includes/minirt.h"

t_color	combine_color(t_color light_color, t_color object_color)
{
	t_color	result;

	result.r = fmin(255, (light_color.r / 255.0) * object_color.r);
	result.g = fmin(255, (light_color.g / 255.0) * object_color.g);
	result.b = fmin(255, (light_color.b / 255.0) * object_color.b);
	return (result);
}

t_vector	random_point_on_light(t_light light)
{
	double		theta;
	double		r;
	t_vector	random_point;

	theta = ((double)rand() / RAND_MAX) * 2 * M_PI;
	r = light.radius * sqrt((double)rand() / RAND_MAX);
	random_point.x = light.pos.x + r * cos(theta);
	random_point.y = light.pos.y + r * sin(theta);
	random_point.z = light.pos.z;
	return (random_point);
}

// Generate a shadow ray towards a random point on the light
static t_ray	generate_shadow_ray(t_vector hit_point, t_light light)
{
	t_ray		shadow_ray;
	t_vector	light_point;
	t_vector	shadow_ray_dir;

	light_point = random_point_on_light(light);
	shadow_ray_dir = normalize(subtract(light_point, hit_point));
	shadow_ray.origin = add(hit_point, multiply_scalar(shadow_ray_dir, 1e-4));
	shadow_ray.direction = shadow_ray_dir;
	return (shadow_ray);
}

// Compute the distance between two points
static double	compute_distance(t_vector a, t_vector b)
{
	t_vector	diff;

	diff = subtract(a, b);
	return (sqrt(dot(diff, diff)));
}

// Check if a shadow ray intersects any objects in the scene
static int	is_in_shadow(t_ray *shadow_ray, t_scene *scene,
	double light_distance)
{
	int			j;
	double		t_shadow;

	j = 0;
	while (j < scene->num_spheres)
	{
		t_shadow = INFINITY;
		if (intersect_sphere(shadow_ray, &scene->spheres[j], &t_shadow)
			&& t_shadow < light_distance)
			return (1);
		j++;
	}
	return (0);
}

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
