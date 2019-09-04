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

static void ft_ptrinit(t_ptr *ptr, t_general *farm, char *line)
{
	ptr->line_ptr = &line;
	ptr->farm_ptr = &farm;
}

int main(void)
{
	int				fd;
	char			*line;
	t_general		*farm;
	t_ptr			ptr;

	line = NULL;
	if (!(farm = (t_general *)ft_memalloc(sizeof(t_general))))
		return (1);
	ft_ptrinit(&ptr, *farm, *line);
	if (!(fd = 0) && ft_parse(line, fd, farm, &ptr))
		exit(ft_memclean(&ptr));
	return (0);
}
