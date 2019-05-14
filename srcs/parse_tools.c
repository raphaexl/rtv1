/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:09:08 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/14 17:07:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	int		ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
			|| c == '\r' || c == '\f' || c == '\v');
}

float			ft_atof(const char *str)
{
	const	char			*p;
	float					number;
	int						i;

	while (ft_isspace(*str))
		str++;
	p = str;
	if (*str == '+' || *str == '-')
		p++;
	number = 0.0;
	while (*p && *p <= '9' && *p >= '0')
	{
		number += *p - '0';
		if (*(p + 1) <= '9' && *(p + 1) >= '0')
			number *= 10.0;
		p++;
	}
	if (*p++ == '.')
	{
		i = 0;
		while (*p && *p <= '9' && *p >= '0' && ++i)
			number += ((float)(*p++ - '0') / pow(10, i));
	}
	return ((*str == '-') ? (-number) : (number));
}

t_vector		ft_vector_read(int fd)
{
	char		*line;
	char		**tab;
	t_vector	vect;
	int			i;

	i = -1;
	vect.x = 0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
			ft_print_error("vertor error");
		vect.x = ft_atof(tab[0]);
		vect.y = ft_atof(tab[1]);
		vect.z = ft_atof(tab[2]);
		while (++i < 3)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	return (vect);
}

t_color			ft_color_read(int fd)
{
	t_color		c;
	char		*line;
	char		**tab;
	int			i;

	i = -1;
	c.red = 0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
			ft_print_error("color error");
		c.red = ft_atof(tab[0]);
		c.green = ft_atof(tab[1]);
		c.blue = ft_atof(tab[2]);
		while (++i < 3)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	return (c);
}

t_material		ft_material_read(int fd)
{
	char		*line;
	t_material	material;
	char		**tab;
	int			i;

	i = -1;
	material.diffuse.blue = 1.0;
	material.diffuse = ft_color_read(fd);
	material.specular = ft_color_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		material.spec_pow = ft_atof(line);
	else
		ft_error();
	if (ft_get_next_line(fd, &line) != 1 && (!line))
		ft_print_error("material properties :)");
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
		ft_print_error("meterial properties error");
	material.reflection = ft_atof(tab[0]);
	material.refraction = ft_atof(tab[1]);
	material.chess = ft_atoi(tab[2]);
	while (++i < 3)
		free(tab[i]);
	free(tab);
	tab = NULL;
	return (material);
}
