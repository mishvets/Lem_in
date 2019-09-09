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

int ft_link_add(t_general *farm, int r1, int r2)
{
	t_link *new;
	t_link *crawler;

	crawler = farm->r_arr[r1]->link;
	if (crawler)
	{
		while (crawler->next)
		{
			if (r2 == crawler->num_room)
				return (1);
			crawler = crawler->next;
		}
		if (!(new = (t_link *)malloc(sizeof(*new))))
			return (1);
		new->num_room = r2;
		new->next = NULL;
		crawler->next = new;
	}
	else
	{
		if (!(new = (t_link *)malloc(sizeof(*new))))
			return (1);
		new->num_room = r2;
		new->next = NULL;
		farm->r_arr[r1]->link = new;
	}
	return (0);
}

int ft_valid_link(t_general *farm, int *room1, int *room2, char **couple)
{
	int 	i;

	i = 0;
	while (i < farm->num_rooms && (*room1 < 0 || *room2 < 0))
	{
		if (!ft_strcmp(farm->r_arr[i]->name_room, couple[0]))
		{
			if (!ft_strcmp(couple[0], couple[1]))//if the same do nthg
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
		ft_printf("Error: room in this link doesn't exist '%s-%s'.\n", couple[0],
				couple[1]);
		return (1);
	}
	return (0);
}

int ft_link_read(char *line, t_general *farm)
{
	char	**couple;
	int 	room1;
	int 	room2;


//	i = 0;
	room1 = -1;
	room2 = -1;
	if (ft_cntwrd(line, '-') != 2 || ft_cntchr(line, '-') != 1)
	{
		ft_printf("Error: bad link '%s'.\n", line);
		return (1);
	}
	couple = ft_strsplit(line, '-');
//	if (ft_strcmp(couple[0], couple[1]))//if the same do nthg
//	{
	if (ft_valid_link(farm, &room1, &room2, couple) == 1)
	{
		ft_strdeli(couple, 3);
		return (1);
	}
	else if (room1 >= 0 && room2 >= 0)
	{
		ft_strdeli(couple, 3);
		if (ft_link_add(farm, room1, room2) && ft_link_add(farm, room2, room1))
			return (1);
	}
	return (0);
//		while (i <= farm->num_rooms || check < 2)
//		{
//			if (!ft_strcmp(farm->r_arr[i]->name_room, couple[0]))
//			{
//				if (ft_strcmp(couple[0], couple[1]))//if the same do nthg
//					check = 2;
//				else
//				{
//					check += 1;
//					ft_link_add();
//				}
//			}
//			else if (!ft_strcmp(farm->r_arr[i]->name_room, couple[1]))
//			{
//				check += 1;
////				create link
//			}
//			++i;
//		}
//		if (check != 2)
//		{
//			ft_printf("Error: room in this link doesn't exist '%s'.\n", line);
//			return (1);
//		}
//	}
}