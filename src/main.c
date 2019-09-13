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

	if (!farm)
	{
		return (0);
	}
	if (farm->start_room)
	{
		if (farm->flag & 1)
			ft_printf("start - %s\n", farm->start_room);
		ft_strdel(&farm->start_room);
	}
	if (farm->finish_room)
	{
		if (farm->flag & 1)
			ft_printf("finish - %s\n", farm->finish_room);
		ft_strdel(&farm->finish_room);
	}
	if (farm->r_arr)
	{
		while (*farm->r_arr)
		{
			crawler = *farm->r_arr;
			*farm->r_arr = (*farm->r_arr)->next;
			if (farm->flag & 1)
				ft_printf("Name: %s; n_room - %i.\nLinks: ", crawler->name_room, crawler->num_room);
			if (crawler->link)
			{
				ft_del_link(crawler->link, farm->flag);
			}
			if (farm->flag & 1)
				ft_printf(" NULL;\n");
			ft_strdel(&crawler->name_room);
			free(crawler);
			crawler = NULL;
		}
	}
	if (farm->visit)
		ft_strdel(&farm->visit);
	if (farm->ways)
		ft_del_way(farm->ways, farm->flag);
//	system("leaks -q lem-in");
	return (0);
}

void ft_del_link(t_link *link, char flag)
{
	t_link		*crwl_link;

	while (link)
	{
		crwl_link = link;
		link = link->next;
		if (flag & 1)
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
		ft_strdel(&crawler->name_room);
		free(crawler);
		crawler = NULL;
	}
}

void	ft_del_way(t_way *way, char flag)
{
	t_way	*crawler_w;

	while(way)
	{
		crawler_w = way;
		way = way->next;
		if (flag & 1)
			ft_printf("Way_len - %i: ", crawler_w->len);
		if (crawler_w->next_point)
		{
			ft_del_link(crawler_w->next_point, flag);
		}
		if (flag & 1)
			ft_printf("NULL;\n");
		free(crawler_w);
		crawler_w = NULL;
	}
}

int 	ft_prepeare(int	argc, char **argv, t_general *farm)
{
	if (argc > 1)
	{
		if(!ft_strncmp(argv[1], "--", 2))
		{
			if (!ft_strncmp(argv[1], "--help", 6))
			{
				ft_printf("options:\n\tg\t: show general information "
			  "about farm;\n\tc\t:print comments;\n\te\t: error manager.\n");
				return (1);
			}
			else if (ft_cntchr(argv[1], 'g') > 1
			|| ft_cntchr(argv[1], 'e') > 1 || ft_cntchr(argv[1], 'c') > 1)
			{
				ft_printf("usage: %s --[flag ...]\n", argv[0]);
				return (1);
			}
			else if (ft_cntchr(argv[1], 'g') == 1)
				farm->flag |= 1;
			else if (ft_cntchr(argv[1], 'e') == 1)
				farm->flag |= 2;
			else if (ft_cntchr(argv[1], 'c') == 1)
				farm->flag |= 4;
		}
		else
		{
			ft_printf("usage: %s --[flag ...]\n", argv[0]);
			return (1);
		}
	}
	farm->r_arr = NULL;
	farm->start_room = NULL;
	farm->finish_room = NULL;
	farm->visit = NULL;
	farm->ways = NULL;
	return (0);
}

void	ft_general_info(t_general *farm, int num_steps)
{
	ft_printf("num ants: %i\n", farm->num_ants);
	ft_printf("total num rooms: %i\n", farm->num_rooms);
	ft_printf("num steps: %i\n", num_steps);
}

int		main(int argc, char **argv) //main(void)
{
	int				fd;
	int				num_steps;
	t_general		*farm;

	if (!(farm = (t_general *)ft_memalloc(sizeof(t_general))))
		return (1);
	if (ft_prepeare(argc, argv, farm))
		exit(ft_memclean(farm));
//	if ((fd = open(argv[2], O_RDONLY)) < 0 || argc < 0) // del!
//	{
//		ft_printf("error read from file\n");
//		return 0;
//	}
	fd = 0;
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
	if (farm->flag & 1)
		ft_general_info(farm, num_steps);
	ft_memclean(farm);
	return (0);
}
