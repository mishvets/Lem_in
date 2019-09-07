/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 21:17:49 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/06 21:17:51 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

t_room_lst	*ft_lstnewroom(char *name, int x, int y)
{
	t_room_lst *new;

	if (!(new = (t_room_lst *)malloc(sizeof(*new))))
		return (NULL);
	if (!(new->name_room = ft_strdup(name)))
	{
		free(new);
		return (NULL);
	}
	new->x = x;
	new->y = y;
	new->next = NULL;
	new->link = NULL;
	return (new);
}

void		ft_lstaddroom(t_room_lst **alst, t_room_lst *new)
{
	t_room_lst	*crawler;

	crawler = *alst;
	if (crawler)
	{
		while (crawler->next)
			crawler = crawler->next;
		crawler->next = new;
	}
	else
		*alst = new;
}

int			ft_valid_room(char **tmp, t_room_lst *r_lst, char *line)
{
	if (!ft_isdigit(tmp[1][0]) || !ft_isdigit(tmp[2][0]))
	{
		ft_printf("Error: bad coordinates in vertex '%s'.\n", line);
		return (1);
	}
	if (tmp[0][0] == 'L')
	{
		ft_printf("Error: name of vertex can't start from 'L'.\n");
		return (1);
	}
	while (r_lst)
	{
		if (!ft_strcmp(r_lst->name_room, tmp[0]))
		{
			ft_printf("Error: vertex names must be unique.\n");
			return (1);
		}
		if (ft_atoi(tmp[1]) == r_lst->x && ft_atoi(tmp[2]) == r_lst->y)
		{
			ft_printf("Error: vertex coordinates must be unique.\n");
			return (1);
		}
		r_lst = r_lst->next;
	}
	return (0);
}

int			ft_room_read(char *line, t_room_lst **r_lst)
{
	char		**tmp;
	t_room_lst	*new;

	if (ft_cntwrd(line, ' ') != 3)
	{
		ft_printf("Error: bad number of vertex's arguments "
			"in string '%s'.\n", line);
		return (1);
	}
	tmp = ft_strsplit(line, ' ');
	if (ft_valid_room(tmp, *r_lst, line))
	{
		ft_strdeli(tmp, 3);
		return (1);
	}
	new = ft_lstnewroom(tmp[0], ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	ft_lstaddroom(r_lst, new);
	ft_strdeli(tmp, 3);
	return (0);
}

int 		ft_room_prepeare(t_room_lst **r_lst, t_general *farm)
{
	int 		i;
	t_room_lst	*crawler;

	crawler = (*r_lst);
	i = 0;
	if (farm->start_room == NULL || farm->finish_room == NULL)
	{
		ft_printf("Error: each map must have 'start' and 'end'.\n");
		return (1);
	}
	while (crawler)
	{
		crawler->num_room = i++;
		crawler = crawler->next;
	}
	if (!(farm->r_arr = (t_room_lst **)ft_memalloc(sizeof(farm->r_arr) * i)))
		return (1);
	i = 0;
	while (*r_lst)
	{
		crawler = (*r_lst);
		(*r_lst) = (*r_lst)->next;
//		crawler->next = NULL;
		farm->r_arr[i++] = crawler;
	}

	return (0);
}
