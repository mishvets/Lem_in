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

int ft_print_result(t_general *farm)
{
	while (i != farm->num_ants)
	ft_printf("L%i-%s", num_ant, farm->r_arr[farm->ways->next_point->num_room]->name_room);
}