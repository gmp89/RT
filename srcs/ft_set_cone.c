/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 17:54:45 by gpetrov           #+#    #+#             */
/*   Updated: 2014/03/27 19:55:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libft.h"

static void		ft_set_cone_origin(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's origin x is not a digit");
	data->x = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's origin y is not a digit");
	data->y = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's origin z is not a digit");
	data->z = ft_atod(line);
}

static void		ft_set_cone_dir(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's dir x is not a digit");
	data->x2 = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's dir y is not a digit");
	data->y2 = ft_atod(line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's dir z is not a digit");
	data->z2 = ft_atod(line);
}

static void		ft_set_cone_const(double *cons, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's const is not a digit");
	*cons = ft_atod(line);
}

static void		ft_set_cone_color(t_data *data, char **line, int fd)
{
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's color RED is not a digit");
	data->r = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's color GREEN is not a digit");
	data->g = (double)ft_atoi(*line);
	get_next_line(fd, line);
	if (ft_check_if_nbr(*line) == -1)
		ft_error("[ERROR SCENE] - Cone's color BLUE is not a digit");
	data->b = (double)ft_atoi(*line);
}

void			ft_set_cone(t_data *data, char **line, int fd)
{
	double		cons;

	data->ref = 0;
	ft_error_init(&data->origin, &data->dir, &data->color, &data->co);
	while (ft_strcmp("#end_object", *line) != 0)
	{
		if (ft_strcmp("#origin", *line) == 0 && (data->origin = '1'))
			ft_set_cone_origin(data, line, fd);
		else if (ft_strcmp("#dir", *line) == 0 && (data->dir = '1'))
			ft_set_cone_dir(data, line, fd);
		else if (ft_strcmp("#const", *line) == 0 && (data->co = '1'))
			ft_set_cone_const(&cons, line, fd);
		else if (ft_strcmp("#color", *line) == 0 && (data->color = '1'))
			ft_set_cone_color(data, line, fd);
		else if (ft_strcmp("#ref", *line) == 0)
			ft_set_cone_ref(&data->ref, line, fd);
		if (get_next_line(fd, line) <= 0)
			ft_error("[ERROR OBJECT] - Object cone has no end");
	}
	if (data->origin == '0' || data->dir == '0' ||
		data->co == '0' || data->color == '0' || data->ref == '0')
		ft_error("[ERROR OBJECT] - Cone's spec missing");
	cone_new(vector_new(data->x, data->y, data->z), cons
	, color_set(data->r, data->g, data->b, data->ref)
	, vector_new(data->x2, data->y2, data->z2));
}
