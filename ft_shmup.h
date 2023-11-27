/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 09:24:09 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/26 15:01:13 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_SHMUP_H
# define FT_SHMUP_H
# define FPS 60
# include <ncurses.h>
# include <curses.h>
# include <time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_entity {
	int				hp;
	int				y_pos;
	int				x_pos;
	chtype			sprite;
	chtype			color;
	WINDOW			*window;
	unsigned int	timer;
} t_entity;

void	ft_shmupbg(char **bg);
int		ft_shmup(void);
void	update_bg(char **bg);


#endif
