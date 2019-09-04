/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:39:34 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 16:39:35 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

static int ft_command(char *line, int fd, t_general *farm, t_ptr *ptr)
{
	if (ft_strncmp(line, "##start", 7))
	{
		if (farm->start_room == NULL)
			farm->start_room = ft_strdup(line);
		else
			exit (ft_memclean(ptr));
	}
	else if (ft_strncmp(line, "##end", 8))
	{

	}
	return (0);
}

static int ft_read_num_ants(char *line, int fd, t_general *farm)
{
	if (get_next_line(fd, &line) < 0)
		return (1);
	while (!ft_strncmp(line, "#", 1) && ft_strncmp(line, "##", 2))
		get_next_line(fd, &line);
	farm->num_ants = ft_atoi(line);
	if (farm->num_ants <= 0)
		return (1);
	return (0);
}

int ft_parse(char *line, int fd, t_general *farm, t_ptr *ptr)
{
	farm->start_room = NULL;
	farm->finish_room = NULL;
	farm->room_name = NULL;
	if(ft_read_num_ants(line, fd, farm))
		return (1);
//	ft_printf("num_ants = %i\n", farm->num_ants);//
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp(line, "##"))
			ft_commands(line, fd, farm, ptr);
		else if ()
	}
	return (0);
}