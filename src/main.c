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

//static void ft_ptrinit(t_ptr *ptr, t_general *farm, char *line)
//{
//	ptr->line_ptr = &line;
//	ptr->farm_ptr = &farm;
//}
static int		ft_memclean(char *line, t_general *farm)
{
//	int i;

//	i = 0;
	if (line)
		ft_strdel(&line);
	if (farm->start_room)
		ft_strdel(&farm->start_room);
	if (farm->finish_room)
		ft_strdel(&farm->finish_room);
//	if (farm->room_name)
//		while ()
	system("leaks -q lem-in");
	return (0);
}

int main(void)
{
	int				fd;
	char			*line;
	t_general		*farm;
//	t_ptr			ptr;

	line = NULL;
	if (!(farm = (t_general *)ft_memalloc(sizeof(t_general))))
		return (1);
//	ft_ptrinit(&ptr, *farm, *line);
	if (!(fd = 0) && ft_parse(line, fd, farm))
		exit(ft_memclean(line, farm));
	ft_printf("start - %s\n", farm->start_room);
	ft_printf("finish - %s\n", farm->finish_room);
	system("leaks -q lem-in");
	return (0);
}
