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

t_way	*ft_way_new(t_link *way, int len)
{
	t_way *new;

	if (!(new = (t_way *)malloc(sizeof(*new))))
		return (NULL);
	new->next_point = way;
	new->len = len;
	new->next = NULL;
	return (new);
}

int	ft_way_add(t_general *farm, t_link *way, int len)
{
	t_way *crwl_way;

	crwl_way = farm->ways;
	if (crwl_way)
	{
		while (crwl_way->next)
			crwl_way = crwl_way->next;
		if (!(crwl_way->next = ft_way_new(way, len)))
			return (1);
	}
	else
	{
		if (!(farm->ways = ft_way_new(way, len)))
			return (1);
	}
	return (0);
}

int ft_create_way(t_general *farm)
{
	int			i;
	t_link		*crwl_link;
	t_link		*new_way;
	int			num_room;
	int 		min_level;

	i = 0;
	new_way = NULL;
	num_room = ft_atoi(farm->start_room);
	if (ft_link_add(&new_way, num_room))
		return (1);
	while (i++ < farm->num_rooms)
	{
		min_level = farm->num_rooms + 10;
		crwl_link = farm->r_arr[num_room]->link;
		while(crwl_link)
		{
			//search the room with the shortest len to finish
			if (farm->r_arr[crwl_link->num_room]->x_level < min_level)
			{
				min_level = farm->r_arr[crwl_link->num_room]->x_level;
				num_room = crwl_link->num_room;
			}
			crwl_link = crwl_link->next;
		}
		if(ft_link_add(&new_way, num_room))
			return (1);
		if (num_room == ft_atoi(farm->finish_room))
		{
			break;
		}
	}
	if(ft_way_add(farm, new_way, i))
		return (1);
	return (0);
}

int ft_bfs(t_general *farm, t_link *queue)
{
	int			i;
	t_link		*crwl_link;

	i = farm->num_rooms;
	//обнуление уровня
	while (i)
		farm->r_arr[--i]->x_level = 0;
//	crawler
	while (i++ < farm->num_rooms && queue)
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
				farm->r_arr[crwl_link->num_room]->x_level = farm->r_arr[queue->num_room]->x_level + 1;
				//set room like visited
				farm->visit[crwl_link->num_room] = 'T';
			}
			crwl_link = crwl_link->next;
		}
		if (queue->num_room == ft_atoi(farm->start_room))
		{
			ft_printf("Queue: ");//
			ft_del_link(queue);
			ft_printf("NULL;\n");//
			break;
		}
		crwl_link = queue;
		queue = queue->next;
		free(crwl_link);
		crwl_link = NULL;
//		++i;
	}
	if (farm->visit[ft_atoi(farm->start_room)] == 'F')
	{
		return (2);
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
	farm->visit[ft_atoi(farm->start_room)] = 'F';
	return (0);
}

int ft_find_way(t_general *farm)
{
	t_link *queue;
//	int 	search_way;

	//create arr visited
	if	(!(farm->visit = (char *)malloc(sizeof(char) * farm->num_rooms)))
		return (1);
	while (1)
	{
		ft_memset(farm->visit, 'F', farm->num_rooms);
		farm->visit[ft_atoi(farm->finish_room)] = 'T';
		queue = NULL;
		//add to queue finish room
		if	(ft_link_add(&queue, ft_atoi(farm->finish_room)))
			return (1);
		if (farm->ways)
		{
			ft_check_way(farm);
		}
		if (ft_bfs(farm, queue) == 1)
		{
			return (1);
		}
		else if (ft_bfs(farm, queue) == 2)
		{
			if (!farm->ways)
			{
				ft_printf("Error: the farm doesn't have ways from start to end room.\n");
				return (1);
			}
			return (0);
		}
		ft_create_way(farm);
	}
	return (0);
}