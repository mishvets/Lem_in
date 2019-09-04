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

static int ft_commands(char *line, int fd, t_general *farm)
{
	if (!ft_strncmp(line, "##start", 7))
	{
		ft_printf("%s1\n", line);
		ft_strdel(&line);
		if (farm->start_room == NULL && get_next_line(fd, &line) > 0)
		{
			if ((farm->start_room = ft_strdup(line)))
				return (0);
		}
		else
			return (1);
//			exit (ft_memclean(ptr));
	}
	else if (!ft_strncmp(line, "##end", 5))
	{
		ft_printf("%s2\n", line);

		ft_strdel(&line);
		if (farm->finish_room == NULL && get_next_line(fd, &line) > 0)
		{
			if ((farm->finish_room = ft_strdup(line)))
				return (0);
		}
		else
			return (1);
	}
	return (0);
}

static int ft_read_num_ants(char *line, int fd, t_general *farm)
{
	if (get_next_line(fd, &line) < 0)
		return (1);
	while (!ft_strncmp(line, "#", 1) && ft_strncmp(line, "##", 2))
	{
		ft_strdel(&line);
		get_next_line(fd, &line);
	}
	farm->num_ants = ft_atoi(line);
	if (farm->num_ants <= 0)
		return (1);
	ft_strdel(&line);
	return (0);
}

//int ft_room_read(int fd, char *line)
//{
//	while (ft_strchr(line, "-"))
//	{
//
//	}
//}

int ft_parse(char *line, int fd, t_general *farm)
{
	int link_start;

	link_start = 0;
	farm->start_room = NULL;
	farm->finish_room = NULL;
	farm->room_name = NULL;
	if(ft_read_num_ants(line, fd, farm))
		return (1);
	ft_printf("num_ants = %i\n", farm->num_ants);//
	while (get_next_line(fd, &line) > 0)
	{
//		if (!ft_strncmp(line, "##", 2))
//			if(ft_commands(line, fd, farm))
//				return (1);
		while (!ft_strncmp(line, "#", 1))
		{
			if (!ft_strncmp(line, "##", 2))
				ft_commands(line, fd, farm);
			else
			{
				ft_strdel(&line);
				get_next_line(fd, &line);
			}
		}
		if (link_start)
		{
//			link_start = 1;
		}
		else if (!link_start)
		{
//			ft_room_read(fd, line);
			while (ft_strchr(line, "-") == NULL)
			{
				if (!ft_strncmp(line, "##", 2))
					if(ft_commands(line, fd, farm))
						return (1);
//					обработка комнаты
			}
			if(ft_strncmp(line, "#", 1))
				link_start = 1;
		}

		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}