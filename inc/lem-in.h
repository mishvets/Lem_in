/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:58:18 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 14:58:20 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

typedef struct			s_coordinate
{
	int					x;
	int					y;
}						t_coordinate;

int						ft_find_place_for_frag(t_player user,
												  t_coordinate *place);
#endif