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
	t_room_lst	*crawler;

	i = farm->num_rooms;
	//обнуление уровня
	while (i)
		farm->r_arr[--i]->x = 0;
//	crawler
	while (i < farm->num_rooms && queue)
	{
		farm->r_arr[queue->num_room]->x
		if(queue->num_room == ft_atoi(farm->start_room))
			break;
	}
	return (0);
}
int	ft_check_ways(t_general *farm)
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
}

int ft_find_ways(t_general *farm)
{
	t_link *queue;

	//create arr visited + add to queue finish room
	if	(!(farm->visit = (char *)malloc(sizeof(char) * farm->num_rooms)) ||
			ft_link_add(&queue, ft_atoi(farm->finish_room)))
		return (1);
	ft_memset(farm->visit, 'F', farm->num_rooms);
	if (farm->ways)
	{
		ft_check_ways(farm);
		while (farm->ways)
		{

		}
	}
	if (ft_bfs(farm, queue))
	{
		return (1);
	}
}