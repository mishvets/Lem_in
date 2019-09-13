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
	int 				x_level;
	int					y_numant;
	struct s_room_lst	*next;
	t_link				*link;
}						t_room_lst;

typedef struct 			s_way
{
	int 				len;
	t_link				*next_point;
	struct s_way		*next;
}						t_way;

typedef struct			s_general
{
	char 				flag;
	int					num_ants;
	int 				num_rooms;
	char				*start_room;
	char 				*finish_room;
	t_room_lst			**r_arr;
	char				*visit;
	t_way				*ways;
}						t_general;

int						ft_parse(int fd, t_general *farm);
int						ft_room_read(char *line, t_room_lst **r_lst,
							t_general *farm);
int						ft_room_prepeare(t_room_lst **r_lst, t_general *farm);
void					ft_lst_room_del(t_room_lst **alst);
int						ft_link_add(t_link **list, int num_room);
int						ft_link_read(char *line, t_general *farm);
int						ft_find_way(t_general *farm);
void					ft_del_link(t_link *link, char flag);
void					ft_del_way(t_way *way, char flag);
void                    ft_transfer_ants(t_general *farm, int num_steps);
void                    ft_move_all_ants(t_general *farm);
#endif