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
	ft_strdel(&line);
	if (farm->num_ants <= 0)
	{
		ft_printf("Error: the number of ants must be > 0.");
		return (1);
	}
	return (0);
}

static int ft_commands(char **line, int fd, t_general *farm, t_room_lst **r_lst)
{
	if (!ft_strncmp(*line, "##start", 7))
	{
		ft_strdel(line);
		if (farm->start_room == NULL && get_next_line(fd, line) > 0)
		{
			if (!ft_room_read(*line, r_lst))
			{
				if ((farm->start_room = ft_strsub(*line, 0, (ft_strchr(*line, ' ') - *line))))
					return (0);
			}
			return (1);
		}
		else
		{
			ft_printf("Error: only one vertex can named 'start'\n");
			return (1);
		}
	}
	else if (!ft_strncmp(*line, "##end", 5))
	{
		ft_strdel(line);
		if (farm->finish_room == NULL && get_next_line(fd, line) > 0)
		{
			if (!ft_room_read(*line, r_lst))
			{
				if ((farm->finish_room = ft_strsub(*line, 0, (ft_strchr(*line, ' ') - *line))))
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
		ft_printf("Name: %s; n_room - %i; x - %i; y - %i. -->\n", crawler->name_room, crawler->num_room, crawler->x, crawler->y);//
		ft_strdel(&crawler->name_room);
		free(crawler);
		crawler = NULL;
	}
}

void ft_parserror(t_room_lst *r_lst, char **line)
{
//		ft_printf("%s\n", error);
		if (line)
			ft_strdel(line);
		if (r_lst)
		{
//			ft_printf("r_lst not empty!\n");
			ft_lst_room_del(&r_lst);
		}
}

int ft_parse(int fd, t_general *farm)
{
	int			link_start;
	t_room_lst	*r_lst;
	char		*line;

	line = NULL;
	link_start = 0;
	r_lst = NULL;
	farm->r_arr = NULL;
	farm->start_room = NULL;
	farm->finish_room = NULL;
	farm->visit = NULL;
	farm->ways = NULL;
	if(ft_read_num_ants(line, fd, farm))
		return (1);
	ft_printf("num_ants = %i\n", farm->num_ants);//

	while (get_next_line(fd, &line) > 0)
	{
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
				if(ft_commands(&line, fd, farm, &r_lst))
				{
					ft_parserror(r_lst, &line);
					return (1);
				}
		}
//		not comment
		else
		{
			if (link_start)
			{
				if (ft_link_read(line, farm))
				{
					ft_parserror(r_lst, &line);
					return (1);
				}
			}

			else
			{
				if (ft_room_read(line, &r_lst))
				{
					ft_parserror(r_lst, &line);
					return (1);
				}
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (0);
}
