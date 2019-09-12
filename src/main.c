/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:31:00 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 16:31:02 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"
#include <fcntl.h> //del!

static int		ft_memclean(t_general *farm)
{
	t_room_lst	*crawler;
//	t_link		*crwl_link;
//	t_way		*crawler_w;

	if (farm->start_room)
	{
		ft_printf("start - %s\n", farm->start_room);
		ft_strdel(&farm->start_room);
	}
	if (farm->finish_room)
	{
		ft_printf("finish - %s\n", farm->finish_room);
		ft_strdel(&farm->finish_room);
	}
	if (farm->r_arr)
	{
		while (*farm->r_arr)
		{
			crawler = *farm->r_arr;
			*farm->r_arr = (*farm->r_arr)->next;
			ft_printf("Name: %s; n_room - %i; x_level - %i.\nLinks: ", crawler->name_room, crawler->num_room, crawler->x_level);//
			if(crawler->link)
			{
				ft_del_link(crawler->link);
			}
			ft_printf(" NULL;\n");
			ft_strdel(&crawler->name_room);
			free(crawler);
			crawler = NULL;
		}
	}
	if (farm->visit)
		ft_strdel(&farm->visit);
	if (farm->ways)
		ft_del_way(farm->ways);
	system("leaks -q lem-in");
	return (0);
}

void ft_del_link(t_link *link)
{
	t_link		*crwl_link;

	while (link)
	{
		crwl_link = link;
		link = link->next;
		ft_printf("%i --> ", crwl_link->num_room);//
		free(crwl_link);
		crwl_link = NULL;
	}
}

void	ft_lst_room_del(t_room_lst **alst)
{
	t_room_lst *crawler;

	while (*alst)
	{
		crawler = (*alst);
		*alst = (*alst)->next;
		ft_printf("Name: %s; n_room - %i; x_level - %i; y_numant - %i. -->\n", crawler->name_room, crawler->num_room, crawler->x_level, crawler->y_numant);//
		ft_strdel(&crawler->name_room);
		free(crawler);
		crawler = NULL;
	}
}

void	ft_del_way(t_way *way)
{
	t_way	*crawler_w;

	while(way)
	{
		crawler_w = way;
		way = way->next;
		ft_printf("Way_len - %i: ", crawler_w->len);//
		if (crawler_w->next_point)
		{
			ft_del_link(crawler_w->next_point);
		}
		ft_printf("NULL;\n");//
		free(crawler_w);
		crawler_w = NULL;
	}
}

int		main(int argc, char **argv) //main(void)
//int		main(void)
{
	int				fd;
	int				num_steps;
	t_general		*farm;

	if (!(farm = (t_general *)ft_memalloc(sizeof(t_general))))
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0 || argc < 0) // del!
	{
		ft_printf("error read from file\n");
		return 0;
	}
//	fd = 0;
	if (ft_parse(fd, farm))
	{
		exit(ft_memclean(farm));
	}
	if ((num_steps = ft_find_way(farm)) < 0)
	{
		exit(ft_memclean(farm));
	}
    if (num_steps == 1)
    {
//        move all ants
		ft_move_all_ants(farm);
    }
    else
	{
		ft_transfer_ants(farm, num_steps);
	}
	ft_memclean(farm);
//	ft_lst_room_del(&farm->r_arr[0]);
	return (0);
}
