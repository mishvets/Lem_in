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

//static void ft_ptrinit(t_ptr *ptr, t_general *farm, char *line)
//{
//	ptr->line_ptr = &line;
//	ptr->farm_ptr = &farm;
//}
static int		ft_memclean(t_general *farm)
{
	int			i;
	t_room_lst	*crawler;
	t_link		*crwl_link;

	i = 0;
	if (farm->start_room)
		ft_strdel(&farm->start_room);
	if (farm->finish_room)
		ft_strdel(&farm->finish_room);
	if (farm->r_arr)
	{
		while (*farm->r_arr)
		{
			crawler = *farm->r_arr;
			*farm->r_arr = (*farm->r_arr)->next;
			ft_printf("Name: %s; n_room - %i; x - %i; y - %i.\nLinks: ", crawler->name_room, crawler->num_room, crawler->x, crawler->y);//
			if(crawler->link)
			{
				while (crawler->link)
				{
					crwl_link = crawler->link;
					crawler->link = crawler->link->next;
					ft_printf("%i --> ", crwl_link->num_room);//
					free(crwl_link);
					crwl_link = NULL;
				}
			}
			ft_printf(" NULL;\n");
			ft_strdel(&crawler->name_room);
			free(crawler);
			crawler = NULL;
		}
	}
	system("leaks -q lem-in");
	return (0);
}

int		main(int argc, char **argv) //main(void)
//int		main(void)
{
	int				fd;
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
	ft_printf("start - %s\n", farm->start_room);
	ft_printf("finish - %s\n", farm->finish_room);
	ft_memclean(farm);
//	ft_lst_room_del(&farm->r_arr[0]);
//	system("leaks -q lem-in");
	return (0);
}
