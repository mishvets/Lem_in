/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:06:52 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 18:06:54 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem-in.h"

int		ft_memclean(t_ptr *ptr)
{
	if (ptr->line_ptr)
		ft_strdel(ptr->line_ptr);
	if (ptr->)
	return (0);
}