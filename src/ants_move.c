/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 20:03:38 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/11 20:03:40 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

void    ft_move_all_ants(t_general *farm)
{
	while (farm->num_ants)
	{
		ft_printf("L%i-%s ", farm->num_ants--,
				farm->r_arr[ft_atoi(farm->finish_room)]->name_room);
	}
	ft_printf("\n");
}

int ft_one_way_move(int new_ant, t_way *way, t_general *farm)
{
	t_link *crwl_l;

	crwl_l = way->next_point;
	//while not "start" room (crwl_l->next == NULL)
	while (crwl_l->next)
	{
		if (crwl_l->num_room == ft_atoi(farm->start_room))
		{
			++farm->r_arr[ft_atoi(farm->start_room)]->y_numant;
		}
		else if (crwl_l->next->num_room == ft_atoi(farm->finish_room) &&
				 new_ant > 0)
		{
			--farm->r_arr[ft_atoi(farm->finish_room)]->y_numant;
			farm->r_arr[crwl_l->num_room]->y_numant = new_ant;
		}
		else
		{
			farm->r_arr[crwl_l->num_room]->y_numant =
					farm->r_arr[crwl_l->next->num_room]->y_numant;

		}
		farm->r_arr[crwl_l->next->num_room]->y_numant = -1;
		ft_printf("L%i-%s ", farm->r_arr[crwl_l->num_room]->y_numant,
				  farm->r_arr[crwl_l->num_room]->name_room);
		crwl_l = crwl_l->next;
	}
	return (0);
}

void ft_transfer_ants(t_general *farm, int num_steps)
{
    t_way	*crwl_w;
    int 	num_ant;

    while (num_steps--)
	{
		crwl_w = farm->ways;
		while (crwl_w)
		{
			num_ant = farm->num_ants - farm->r_arr[ft_atoi(farm->start_room)]->y_numant;
			if (num_steps >= crwl_w->len)
				ft_one_way_move(num_ant, crwl_w, farm);
			crwl_w = crwl_w->next;
		}
		ft_printf("\n");
	}
}

//int ft_print_result(t_general *farm)
//{
//	while (i != farm->num_ants)
//	ft_printf("L%i-%s", num_ant, farm->r_arr[farm->ways->next_point->num_room]->name_room);
//}