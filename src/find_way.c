/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:03:56 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/10 14:03:58 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

int ft_bfs(t_general *farm, t_link *queue)
{
	int			i;
	t_link		*crwl_link;

	i = farm->num_rooms;
	//обнуление уровня
	while (i)
		farm->r_arr[--i]->x_level = 0;
//	crawler
	while (i < farm->num_rooms && queue)
	{
		crwl_link = farm->r_arr[queue->num_room]->link;
		while (crwl_link)
		{
			if (farm->visit[crwl_link->num_room] == 'F')
			{
				//add room if not visiting before
				if(ft_link_add(&queue, crwl_link->num_room))
					return (1);
				//set level for new room in queue
				farm->r_arr[crwl_link->num_room]->x_level = i;
			}
			crwl_link = crwl_link->next;
		}
		if(queue->num_room == ft_atoi(farm->start_room))
		{
			ft_del_link(queue);
			break;
		}
		crwl_link = queue;
		queue = queue->next;
		free(crwl_link);
		crwl_link = NULL;
	}
	return (0);
}
int	ft_check_way(t_general *farm)
{
	t_way	*crawler_w;
	t_link	*crawler_r;

	crawler_w = farm->ways;
	ft_memset(farm->visit, 'F', farm->num_rooms);
//	while we have possible ways
	while (crawler_w)
	{
		crawler_r = crawler_w->next_point;
//		while path have rooms
		while(crawler_r)
		{
//			all rooms in path are visited - true
			farm->visit[crawler_r->num_room] = 'T';
			crawler_r = crawler_r->next;
		}
		crawler_w = crawler_w->next;
	}
	return (0);
}

int ft_find_way(t_general *farm)
{
	t_link *queue;

	queue = NULL;
	//create arr visited + add to queue finish room
	if	(!(farm->visit = (char *)malloc(sizeof(char) * farm->num_rooms)) ||
			ft_link_add(&queue, ft_atoi(farm->finish_room)))
		return (1);
	ft_memset(farm->visit, 'F', farm->num_rooms);
	if (farm->ways)
	{
		ft_check_way(farm);
//		while (farm->ways)
//		{
//
//		}
	}
	if (ft_bfs(farm, queue))
	{
		return (1);
	}
	return (0);
}