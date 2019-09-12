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
		if (crwl_l->num_room == ft_atoi(farm->finish_room))
		{
			if (farm->r_arr[crwl_l->next->num_room]->y_numant > 0)
			{
				++farm->r_arr[ft_atoi(farm->finish_room)]->y_numant;
				ft_printf("L%i-%s ", farm->r_arr[crwl_l->next->num_room]->y_numant,
						  farm->r_arr[crwl_l->num_room]->name_room);
				farm->r_arr[crwl_l->next->num_room]->y_numant = -1;
			}
//			farm->r_arr[crwl_l->next->num_room]->y_numant = -1;
		}
		else if (crwl_l->next->num_room == ft_atoi(farm->start_room))
		{
			if(new_ant > 0)
			{
				--farm->r_arr[ft_atoi(farm->start_room)]->y_numant;
				farm->r_arr[crwl_l->num_room]->y_numant = new_ant;
			}
		}
		else
		{
			farm->r_arr[crwl_l->num_room]->y_numant =
					farm->r_arr[crwl_l->next->num_room]->y_numant;
			farm->r_arr[crwl_l->next->num_room]->y_numant = -1;
		}
		if (farm->r_arr[crwl_l->num_room]->y_numant > 0 && crwl_l->num_room != ft_atoi(farm->finish_room))
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

    while (farm->r_arr[ft_atoi(farm->finish_room)]->y_numant != farm->num_ants)
	{
		crwl_w = farm->ways;
		while (crwl_w)
		{
			num_ant = -1;
			if (num_steps >= crwl_w->len && farm->r_arr[ft_atoi(farm->start_room)]->y_numant)
			{
				num_ant = farm->num_ants - farm->r_arr[ft_atoi(farm->start_room)]->y_numant + 1;
			}
			ft_one_way_move(num_ant, crwl_w, farm);
			crwl_w = crwl_w->next;
		}
		num_steps--;
		ft_printf("\n");
	}
}
