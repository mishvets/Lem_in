/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:22:49 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/07 17:22:51 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

t_link	*ft_link_new(int num_room)
{
	t_link *new;

	if (!(new = (t_link *)malloc(sizeof(*new))))
		return (NULL);
	new->num_room = num_room;
	new->next = NULL;
	return (new);
}

int		ft_link_add(t_link **list, int num_room)
{
	t_link *crawler;

	crawler = *list;
	if (crawler)
	{
		while (crawler->next)
		{
			if (num_room == crawler->num_room)//the same room
				return (2);
			crawler = crawler->next;
		}
		if (!(crawler->next = ft_link_new(num_room)))
			return (1);
	}
	else
	{
		if (!(*list = ft_link_new(num_room)))
			return (1);
	}
	return (0);
}

int		ft_valid_link(t_general *farm, int *room1, int *room2, char **couple)
{
	int	i;

	i = 0;
	while (i < farm->num_rooms && (*room1 < 0 || *room2 < 0))
	{
		if (!ft_strcmp(farm->r_arr[i]->name_room, couple[0]))
		{
			if (!ft_strcmp(couple[0], couple[1]))
				return (2);
			else
				*room1 = i;
		}
		else if (!ft_strcmp(farm->r_arr[i]->name_room, couple[1]))
		{
			*room2 = i;
		}
		++i;
	}
	if (*room1 < 0 || *room2 < 0)
	{
		ft_printf("Error: room in this link doesn't exist '%s-%s'.\n",
				couple[0], couple[1]);
		return (1);
	}
	return (0);
}

int		ft_link_read(char *line, t_general *farm)
{
	char	**couple;
	int		room1;
	int		room2;

	room1 = -1;
	room2 = -1;
	if (ft_cntwrd(line, '-') != 2 || ft_cntchr(line, '-') != 1)
	{
		ft_printf("Error: bad link '%s'.\n", line);
		return (1);
	}
	couple = ft_strsplit(line, '-');
	if (ft_valid_link(farm, &room1, &room2, couple) == 1)
	{
		ft_strdeli(couple, 3);
		return (1);
	}
	else if (room1 >= 0 && room2 >= 0)
	{
		ft_strdeli(couple, 3);
		if (ft_link_add(&farm->r_arr[room1]->link, room2) == 1 ||
		ft_link_add(&farm->r_arr[room2]->link, room1) == 1)
			return (1);
	}
	return (0);
}
