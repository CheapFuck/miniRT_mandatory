/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersection1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwang <diwang@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/09 15:43:33 by diwang        #+#    #+#                 */
/*   Updated: 2024/12/09 16:03:05 by diwang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define EPSILON 1e-6

// Step 2: Solve quadratic equation and check discriminant
static int	solve_quadratic(double *components, double *t1, double *t2)
{
	double	discriminant;

	discriminant = components[1] * components[1] - 4 * components[0]
		* components[2];
	if (discriminant < EPSILON)
		return (0);
	*t1 = (-components[1] - sqrt(discriminant)) / (2.0 * components[0]);
	*t2 = (-components[1] + sqrt(discriminant)) / (2.0 * components[0]);
	return (1);
}

// Step 3: Check if intersection points are within cylinder's height
static int	check_cylinder_height(t_ray *ray, t_cylinder *cylinder,
				double t, t_vector axis)
{
	t_vector	intersection;
	double		height;

	intersection = add(ray->origin, multiply_scalar(ray->direction, t));
	height = dot(subtract(intersection, cylinder->center), axis);
	return (fabs(height) <= cylinder->height / 2);
}

// Main function: Intersect ray with cylinder
int	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t)
{
	t_vector	axis;
	double		components[3];
	double		t1;
	double		t2;
	int			hit;

	axis = normalize(cylinder->orientation);
	calculate_cylinder_quadratic(ray, cylinder, components);
	if (!solve_quadratic(components, &t1, &t2))
		return (0);
	hit = 0;
	if (t1 > 0 && check_cylinder_height(ray, cylinder, t1, axis))
	{
		*t = t1;
		hit = 1;
	}
	if (t2 > 0 && check_cylinder_height(ray, cylinder, t2, axis) && (!hit || t2
			< *t))
	{
		*t = t2;
		hit = 1;
	}
	return (hit);
}

int	intersect_disc(t_ray *ray, t_disc *disc, double *t)
{
    t_vector oc;             // Vector from ray origin to disc center
    double denom;            // Dot product of ray direction and disc normal
    double t_plane;          // Distance to intersection point on plane
    t_vector p;              // Intersection point
    double distance_squared; // Squared distance from center to intersection point

    // Step 1: Calculate the denominator (ray direction · disc normal)
    denom = dot(ray->direction, disc->normal);
    if (fabs(denom) < 1e-6) // Avoid division by near-zero; ray is parallel to disc
        return (0);

    // Step 2: Find intersection distance to the plane containing the disc
    oc = subtract(disc->center, ray->origin); // Vector from ray origin to disc center
    t_plane = dot(oc, disc->normal) / denom;

    if (t_plane <= 0) // Intersection is behind the ray's origin
        return (0);

    // Step 3: Check if the intersection point is within the disc's radius
    p = add(ray->origin, scale(ray->direction, t_plane)); // Intersection point
    distance_squared = length_squared(subtract(p, disc->center));
    if (distance_squared > disc->radius * disc->radius)
        return (0); // Intersection is outside the disc

    // Valid intersection
    *t = t_plane;
    return (1);
}
