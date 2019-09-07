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

int ft_link_read(char *line, t_general *farm)
{
	char	**couple;
	int 	i;

	i = 0;
	if (ft_cntwrd(line, '-') != 2)
		return (1);
	couple = ft_strsplit(line, '-');
	if (ft_strcmp(couple[0], couple[1]))//if the same do nthg
	{
		while (i <= farm->num_rooms || check < 2)
		{
			if (!ft_strcmp(farm->r_arr[i]->name_room, couple[0]) ||
			!ft_strcmp(farm->r_arr[i]->name_room, couple[1]))
			{
				check += 1;
//				create link
			}
			++i;
		}
		if (check != 2)
		{
			ft_printf("Error: room in this link doesn't exist '%s'.\n", line);
			return (1);
		}
	}
	return (0);
}