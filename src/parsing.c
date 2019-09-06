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
	{
		ft_printf("Error: the number of ants must be > 0.");
		return (1);
	}
	ft_strdel(&line);
	return (0);
}



static int ft_commands(char *line, int fd, t_general *farm, t_room_lst **r_lst)
{
	if (!ft_strncmp(line, "##start", 7))
	{
//		ft_printf("%s1\n", line);
		ft_strdel(&line);
		if (farm->start_room == NULL && get_next_line(fd, &line) > 0)
		{
			if (!ft_room_read(line, r_lst))
			{
				if ((farm->start_room = ft_strsub(line, 0, (ft_strchr(line, ' ') - line))))
					return (0);
			}
			return (1);
		}
		else
		{
			ft_printf("Error: only one vertex can named 'start'\n");
			return (1);
		}
//			exit (ft_memclean(ptr));
	}
	else if (!ft_strncmp(line, "##end", 5))
	{
//		ft_printf("%s2\n", line);
		ft_strdel(&line);
		if (farm->finish_room == NULL && get_next_line(fd, &line) > 0)
		{
			if (!ft_room_read(line, r_lst))
			{
				if ((farm->finish_room = ft_strsub(line, 0, (ft_strchr(line, ' ') - line))))
					return (0);
			}
			return (1);
		}
		else
		{
			ft_printf("Error: only one vertex can named 'end'.\n");
			return (1);
		}
	}
	return (0);
}

void	ft_lst_room_del(t_room_lst **alst)
{
	t_room_lst *crawler;

	while (*alst)
	{
		crawler = (*alst);
		*alst = (*alst)->next;
		ft_printf("Name: %s; x - %i; y - %i. -->\n", crawler->name_room, crawler->x, crawler->y);//
		ft_strdel(&crawler->name_room);
		free(crawler);
		crawler = NULL;
	}
}

void ft_parserror(t_room_lst *r_lst)
{
//		ft_printf("%s\n", error);
		if (r_lst)
		{
			ft_lst_room_del(&r_lst);
		}
//		ft_strdel(&error);
}

int ft_parse(int fd, t_general *farm)
{
	int			link_start;
	t_room_lst	*r_lst;
	char		*line;
//	char 		*error;

	line = NULL;
	link_start = 0;
	r_lst = NULL;
	farm->start_room = NULL;
	farm->finish_room = NULL;
	farm->room_name = NULL;
//	error = ft_strnew(50);
	if(ft_read_num_ants(line, fd, farm))
		return (1);
	ft_printf("num_ants = %i\n", farm->num_ants);//

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strchr(line, '-') && ft_strncmp(line, "#", 1)) // not comment with '-'
		{
			link_start = 1;
		}
		// 		if (!ft_strncmp(line, "##", 2))
//			if(ft_commands(line, fd, farm))
//				return (1);

//		comment
		if (!ft_strncmp(line, "#", 1))
		{
			if (!ft_strncmp(line, "##", 2))
				if(ft_commands(line, fd, farm, &r_lst))
				{
					ft_strdel(&line);
					ft_parserror(r_lst);
					return (1);
				}
//			else
//			{
//				ft_strdel(&line);
//				get_next_line(fd, &line);
//			}
		}
//		not comment
		else
		{
			if (link_start)
			{
//			ft_links();
			}

			else
			{
				if (ft_room_read(line, &r_lst))
				{
					ft_strdel(&line);
					ft_parserror(r_lst);
					return (1);
				}
//				while (ft_strchr(line, "-") == NULL)
//				{
//					if (!ft_strncmp(line, "##", 2))
//						if(ft_commands(line, fd, farm))
//							return (1);
////					обработка комнаты
//				}
//				if(ft_strncmp(line, "#", 1))
//				{
////				перенос вершин в массив
//					link_start = 1;
//				}
			}
		}
		ft_strdel(&line);
//		if (error)
//			ft_parserror(error, r_lst);
	}
	ft_strdel(&line);
	ft_lst_room_del(&r_lst);
	return (0);
}
