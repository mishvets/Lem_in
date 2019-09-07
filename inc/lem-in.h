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

typedef struct 			s_link
{
	int 				num_room;
	struct s_link		*next;
}						t_link;

typedef struct			s_room_lst
{
	int					num_room;
	char				*name_room;
	int 				x;
	int					y;
	struct s_room_lst	*next;
	t_link				*link;
}						t_room_lst;

typedef struct			s_general
{
	int					num_ants;
	int 				num_rooms;
	char				*start_room;
	char 				*finish_room;
	t_room_lst			**r_arr;
}						t_general;

//typedef struct	s_ptr
//{
//	char		**line_ptr;
//	t_general	**farm_ptr;
//}				t_ptr;

int						ft_parse(int fd, t_general *farm);
void					ft_strdeli(char **arr, size_t i);
int						ft_room_read(char *line, t_room_lst **r_lst);
int						ft_room_prepeare(t_room_lst **r_lst, t_general *farm);
void					ft_lst_room_del(t_room_lst **alst);
int						ft_link_read(char *line, t_general *farm);
//int				ft_memclean(t_ptr *ptr);
#endif