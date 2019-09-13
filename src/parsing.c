/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:39:34 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 16:39:35 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

int			ft_atoi_ants(const char *strptr)
{
	size_t					i;
	unsigned long int	num;

	i = 0;
	num = 0;
	while (ft_isspace(strptr[i]))
		++i;
	if (strptr[i] == '+')
		++i;
	else if (strptr[i] == '-')
		return (-1);
	while (ft_isdigit(strptr[i]))
		num = num * 10 + strptr[i++] - '0';
	if (num > 2147483647 || i != ft_strlen(strptr) || i > 10)
		return (-1);
	return (num);
}

static int ft_read_num_ants(char *line, int fd, t_general *farm)
{
	size_t i;

	i = 0;
	if (get_next_line(fd, &line) < 0)
		return (1);
	ft_printf("%s\n", line);
	while (!ft_strncmp(line, "#", 1) && ft_strncmp(line, "##", 2))
	{
		ft_strdel(&line);
		get_next_line(fd, &line);
		ft_printf("%s\n", line);
	}
//	while (ft_isdigit(line[i]))
//		i++;
//	if (i != ft_strlen(line))
//	{
//		if (farm->flag & 2)
//			ft_printf("Error: incorrect number of ants '%s'.\n", line);
//		return (1);
//	}
	farm->num_ants = ft_atoi_ants(line);
	ft_strdel(&line);
	if (farm->num_ants <= 0)
	{
		if (farm->flag & 2)
			ft_printf("Error: the number of ants must be > 0 and < 2147483648.\n");
		return (1);
	}
	return (0);
}

static int ft_commands(char **line, int fd, t_general *farm, t_room_lst **r_lst)
{
	if (!ft_strcmp(*line, "##start"))
	{
		ft_strdel(line);
		if (farm->start_room == NULL && get_next_line(fd, line) > 0)
		{
			ft_printf("%s\n", *line);
			if (!ft_room_read(*line, r_lst, farm))
			{
				if ((farm->start_room = ft_strsub(*line, 0, (ft_strchr(*line, ' ') - *line))))
					return (0);
			}
			return (1);
		}
		else
		{
			if (farm->flag & 2)
				ft_printf("Error: only one vertex can named 'start'\n");
			return (1);
		}
	}
	else if (!ft_strcmp(*line, "##end"))
	{
		ft_strdel(line);
		if (farm->finish_room == NULL && get_next_line(fd, line) > 0)
		{
			ft_printf("%s\n", *line);
			if (!ft_room_read(*line, r_lst, farm))
			{
				if ((farm->finish_room = ft_strsub(*line, 0, (ft_strchr(*line, ' ') - *line))))
					return (0);
			}
			return (1);
		}
		else
		{
			if (farm->flag & 2)
				ft_printf("Error: only one vertex can named 'end'.\n");
			return (1);
		}
	}
	return (0);
}

int ft_parserror(t_room_lst *r_lst, char **line)
{
		if (line)
			ft_strdel(line);
		if (r_lst)
			ft_lst_room_del(&r_lst);
	return (1);
}

int ft_parse(int fd, t_general *farm)
{
	int			link_start;
	t_room_lst	*r_lst;
	char		*line;

	line = NULL;
	link_start = 0;
	r_lst = NULL;
	if(ft_read_num_ants(line, fd, farm))
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("%s\n", line);
		if (ft_strchr(line, '-') && ft_strncmp(line, "#", 1) && !link_start) // not comment with '-'
		{
			link_start = 1;
			if(ft_room_prepeare(&r_lst, farm))
				return (1);
		}
//		comment
		if (!ft_strncmp(line, "#", 1))
		{
			if (!ft_strncmp(line, "##", 2))
			{
				if (ft_commands(&line, fd, farm, &r_lst))
					return (ft_parserror(r_lst, &line));
			}
			else if (farm->flag & 4)
					ft_printf("%s\n", line);
		}
//		not comment
		else
		{
			if (link_start)
			{
				if (ft_link_read(line, farm))
					return (ft_parserror(r_lst, &line));
			}
			else
			{
				if (ft_room_read(line, &r_lst, farm))
					return (ft_parserror(r_lst, &line));
			}
		}
		ft_strdel(&line);
	}
	ft_printf("\n");
	ft_strdel(&line);
	if (!link_start)
	{
		if (farm->flag & 2)
			ft_printf("Error: no links in the map.\n");
		return (ft_parserror(r_lst, &line));
	}
	return (0);
}
