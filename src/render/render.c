#include "../../includes/minirt.h"

// typedef struct	s_render_data
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;
// 	t_scene		*scene;
// 	int			current_row;
// 	bool		render_complete;
// }	t_render_data;

// Function declarations
t_ray		create_ray(int x, int y, t_camera *camera);
t_vector	world_to_local(t_vector point, t_vector orientation,
				t_vector center);

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

// Function to create a ray from the camera for a specific pixel
t_ray	create_ray(int x, int y, t_camera *camera)
{
	t_ray	ray;

	ray.origin = camera->pos;
    //Calculate direction from camera to pixel (simple perspective projection)
	ray.direction.x = (2 * (x + 0.5) / (double)WIDTH - 1) * tan(camera->fov
			/ 2 * M_PI / 180);
	ray.direction.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * tan(camera->fov
			/ 2 * M_PI / 180);
	ray.direction.z = 1; // Assume camera is looking along the positive z-axis
	ray.direction = normalize(ray.direction);
	return (ray);
}

t_vector	cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector	world_to_local(t_vector point, t_vector orientation,
	t_vector center)
{
	t_vector	local_point;
	t_vector	up;
	t_vector	right;
	t_vector	forward;
	t_vector	temp_vector;

	local_point = subtract(point, center);
	up = orientation;
	if (fabs(up.y) < 0.999)
		temp_vector = (t_vector){0, 1, 0};
	else
		temp_vector = (t_vector){1, 0, 0};
	right = normalize(cross(up, temp_vector));
	if (fabs(up.y) < 0.999)
		temp_vector = (t_vector){0, 1, 0};
	else
		temp_vector = (t_vector){0, 1, 0};
	right = normalize(cross(up, temp_vector));
	forward = cross(right, up);
	return ((t_vector)
		{
			dot(local_point, right),
			dot(local_point, up),
			dot(local_point, forward)
		});
}

// Handle sphere intersections and update color
static int	handle_spheres(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_sphere;
	t_vector	hit_point;
	t_vector	normal;

	hit = 0;
	i = 0;
	while (i < scene->num_spheres)
	{
		t_sphere = *t;
		if (intersect_sphere(ray, &scene->spheres[i], &t_sphere)
			&& t_sphere < *t)
		{
			*t = t_sphere;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			normal = normalize(subtract(hit_point, scene->spheres[i].center));
			*final_color = apply_lighting(hit_point, normal,
					scene->spheres[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}

// Handle cylinder intersections and update color
static int	handle_cylinders(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_cylinder;
	t_vector	hit_point;
	t_vector	normal;

	hit = 0;
	i = 0;
	while (i < scene->num_cylinders)
	{
		t_cylinder = *t;
		if (intersect_cylinder(ray, &scene->cylinders[i], &t_cylinder)
			&& t_cylinder < *t)
		{
			*t = t_cylinder;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			normal = normalize(subtract(hit_point, scene->cylinders[i].center));
			*final_color = apply_lighting(hit_point, normal,
					scene->cylinders[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}

// Handle plane intersections and update color
static int	handle_planes(t_ray *ray, t_scene *scene, double *t,
					t_color *final_color)
{
	int			i;
	int			hit;
	double		t_plane;
	t_vector	hit_point;

	hit = 0;
	i = 0;
	while (i < scene->num_planes)
	{
		t_plane = *t;
		if (intersect_plane(ray, &scene->planes[i], &t_plane)
			&& t_plane < *t)
		{
			*t = t_plane;
			hit_point = add(ray->origin, multiply_scalar(ray->direction, *t));
			*final_color = apply_lighting(hit_point, scene->planes[i].normal,
					scene->planes[i].color, scene);
			hit = 1;
		}
		i++;
	}
	return (hit);
}

// Trace ray and determine pixel color
static uint32_t	trace_ray(t_ray ray, t_scene *scene)
{
	double		t;
	t_color		final_color;
	int			hit;

	t = INFINITY;
	hit = 0;
	final_color = (t_color){0, 0, 0};
	if (handle_spheres(&ray, scene, &t, &final_color))
		hit = 1;
	if (handle_cylinders(&ray, scene, &t, &final_color))
		hit = 1;
	if (handle_planes(&ray, scene, &t, &final_color))
		hit = 1;
	if (hit)
		return ((final_color.r << 24) | (final_color.g << 16)
			| (final_color.b << 8) | 0xFF);
	return (0x000000FF);
}

// Main function for rendering the next row
void	render_next_row(void *param)
{
	t_render_data	*data;
	int				x;
	t_ray			ray;
	uint32_t		color;

	data = (t_render_data *)param;
	if (data->current_row >= HEIGHT)
	{
		data->render_complete = true;
		printf("Rendering complete!\n");
		mlx_terminate(data->mlx);
		free(data);
		exit(EXIT_SUCCESS);
		return ;
	}
	x = 0;
	while (x < WIDTH)
	{
		ray = create_ray(x, data->current_row, &data->scene->camera);
		color = trace_ray(ray, data->scene);
		mlx_put_pixel(data->img, x, data->current_row, color);
		x++;
	}
	data->current_row++;
}

// Allocate and initialize render data
static t_render_data	*init_render_data(mlx_t *mlx, t_scene *scene,
										mlx_image_t *img)
{
	t_render_data	*data;

	data = malloc(sizeof(t_render_data));
	if (!data)
		exit_with_error("Failed to allocate render data");
	data->mlx = mlx;
	data->img = img;
	data->scene = scene;
	data->current_row = 0;
	data->render_complete = false;
	return (data);
}

// Create and initialize an MLX image
static mlx_image_t	*create_image(mlx_t *mlx)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit_with_error("Error creating image");
	return (img);
}

// Main render scene function
void	render_scene(mlx_t *mlx, t_scene *scene)
{
	mlx_image_t		*img;
	t_render_data	*data;

	img = create_image(mlx);
	data = init_render_data(mlx, scene, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, render_next_row, data);
	mlx_loop(mlx);
	mlx_terminate(mlx); //no need?
	// free(data);
}
