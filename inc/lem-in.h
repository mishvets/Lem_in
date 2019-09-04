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

typedef struct	s_general
{
	int			num_ants;
	char		*start_room;
	char 		*finish_room;
	char		**room_name;
}				t_general;

//typedef struct	s_ptr
//{
//	char		**line_ptr;
//	t_general	**farm_ptr;
//}				t_ptr;

int				ft_parse(char *line, int fd, t_general *farm);
//int				ft_memclean(t_ptr *ptr);
#endif