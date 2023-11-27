/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:51:02 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/26 15:46:42 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

int			score = 0;
int 		lives = 5;
t_entity	entities[30];
char		*bg[25];

void	init_stat_bar(WINDOW **stat_bar)
{
	stat_bar[0] = newwin(1, 80, 24, 0);
	wbkgd(stat_bar[0], COLOR_PAIR(2));
	stat_bar[1] = subwin(stat_bar[0], 1, 20, 24, 1);
	stat_bar[2] = subwin(stat_bar[0], 1, 20, 24, 25);
	stat_bar[3] = subwin(stat_bar[0], 1, 20, 24, 49);
	wrefresh(stat_bar[0]);
}

void	set_entity(int index, int hp, int y_pos, int x_pos, chtype sprite, chtype color)
{
	entities[index].hp = hp;
	entities[index].x_pos = x_pos;
	entities[index].y_pos = y_pos;
	entities[index].sprite = sprite;
	entities[index].color = COLOR_PAIR(color);
	delwin(entities[index].window);
	entities[index].window = newwin(1, 1, y_pos, x_pos);
	wbkgd(entities[index].window, entities[index].color);
	entities[index].timer = 0;
}

void	create_entity(int index, int hp, int y_pos, int x_pos, chtype sprite, chtype color)
{
	t_entity	entity = {hp, y_pos, x_pos, sprite, COLOR_PAIR(color), 0, 0};

	entity.window = newwin(1, 1, y_pos, x_pos);
	wbkgd(entity.window, COLOR_PAIR(color));
	entities[index] = entity;
	return ;
}

void	init_entities(void)
{
	int i;

	i = 1;
	create_entity(0, 1, 10, 1, '}', 4);
	while (i < 30)
	{
		create_entity(i, 0, 0, 0, 0, 0);
		i++;
	}
}

void	player_fire(void)
{
	int	i;

	i = 21;
	while (i < 25)
	{
		if (entities[i].hp == 0)
		{
			set_entity(i, 1, entities[0].y_pos, entities[0].x_pos + 1, 'o', 4);
			return ;
		}
		i++;
	}
	return ;
}

void	enemies_advance(void)
{
	int	i;
	int	spawn;

	i = 1;
	spawn = 0;
	while (i <= 10)
	{
		if (entities[i].hp == 0 && (random() % 1000) < 3 && spawn == 0)
		{
			set_entity(i, 1, random() % 24, 79, "X$<{"[random()%4], 5);
			spawn = 1;
		}
		if (entities[i].hp)
		{
			if (entities[i].timer % 10 == 0)
			{
				entities[i].x_pos--;
				delwin(entities[i].window);
				entities[i].window = newwin(1, 1, entities[i].y_pos, entities[i].x_pos);
				wbkgd(entities[i].window, entities[i].color);
				if (entities[i].x_pos == 0)
				{
					set_entity(i, 0, 0, 0, 0, 0);
					score -= 100;
				}	
			}
			entities[i].timer++;
		}
		i++;
	}
}

void	enemies_fire(void)
{
	int	enemy;

	enemy = 1;
	while (enemy <= 10)
	{
		if (entities[enemy].hp != 0 && entities[enemy].timer % 150 == 0 && entities[enemy + 10].hp == 0)
		{
			set_entity(enemy + 10, 1, entities[enemy].y_pos, entities[enemy].x_pos, 'o', 5);
		}
		enemy++;
	}
	return;
}

void	bullets_advance(void)
{
	int	bullet;

	bullet = 11;
	while (bullet <= 20)
	{
		if (entities[bullet].hp)
		{
			entities[bullet].x_pos--;
			delwin(entities[bullet].window);
			entities[bullet].window = newwin(1, 1, entities[bullet].y_pos, entities[bullet].x_pos);
			wbkgd(entities[bullet].window, entities[bullet].color);
			if (entities[bullet].x_pos == 0)
			{
				set_entity(bullet, 0, 0, 0, 0, 0);
			}	
		}
		bullet++;
	}
	while (bullet < 25)
	{
		if (entities[bullet].hp)
		{
			entities[bullet].x_pos++;
			delwin(entities[bullet].window);
			entities[bullet].window = newwin(1, 1, entities[bullet].y_pos, entities[bullet].x_pos);
			wbkgd(entities[bullet].window, entities[bullet].color);
			if (entities[bullet].x_pos == 79)
			{
				set_entity(bullet, 0, 0, 0, 0, 0);
			}	
		}
		bullet++;
	}
}

void	check_collisions(void)
{
	int	enemy;
	int	bullet;

	enemy = 1;
	bullet = 11;

	while (bullet <= 20)
	{
		if (entities[bullet].x_pos == 1 && entities[bullet].y_pos == entities[0].y_pos)
		{
			lives--;
		}
		bullet++;
	}
	while (enemy <= 10)
	{
		if (entities[enemy].hp !=0)
		{
			if (entities[enemy].x_pos == 1 && entities[enemy].y_pos == entities[0].y_pos)
			{
				lives--;
				set_entity(enemy, 0, 0, 0, 0, 0);
			}
			bullet = 21;
			while (bullet < 25)
			{
				if (entities[bullet].hp != 0 && entities[enemy].y_pos == entities[bullet].y_pos && entities[enemy].x_pos <= entities[bullet].x_pos)
				{
					score += 200;
					set_entity(enemy, 0, 0, 0, 0, 0);
					set_entity(bullet, 0, 0, 0, 0, 0);
				}
			bullet++;
			}
		}
		enemy++;
	}
}

int	update_entities(int ch)
{
	if (ch == KEY_DOWN || ch == KEY_UP)
	{
		if (ch == KEY_DOWN)
			entities[0].y_pos = (entities[0].y_pos + 1) % 24;
		if (ch == KEY_UP)
			entities[0].y_pos = (entities[0].y_pos + 23) % 24;
		delwin(entities[0].window);
		entities[0].window = newwin(1, 1, entities[0].y_pos, entities[0].x_pos);
		wbkgd(entities[0].window, entities[0].color);
	}
	entities[0].timer++;
	if (entities[0].timer % 30 == 0)
		player_fire();
	enemies_advance();
	enemies_fire();
	bullets_advance();
	check_collisions();
	return (0);
}

void	print_entities(void)
{
	int	i;

	i = 0;
	while (i < 30)
	{
		if (entities[i].hp != 0)
		{
			waddch(entities[i].window, entities[i].sprite);
			wrefresh(entities[i].window);
		}
		i++;
	}
}


void	print_stats(WINDOW **stat_bar)
{
	static int	time;

	time++;
	touchwin(stat_bar[0]);
	wmove(stat_bar[1], 0, 0);
	wprintw(stat_bar[1], "LIVES : %d", lives);
	wmove(stat_bar[2], 0, 0);
	wprintw(stat_bar[2], "SCORE : %06d", score);
	wmove(stat_bar[3], 0, 0);
	wprintw(stat_bar[3], "TIME : %6d", time/FPS);
	wrefresh(stat_bar[0]);
	return ;
}

void	game_over(void)
{
	WINDOW	*go_win;

	update_bg(bg);
	nodelay(stdscr, FALSE);
	go_win = newwin(9, 40, (25 - 9) / 2, (80 - 40) / 2);
	wbkgd(go_win, COLOR_PAIR(3));
	box(go_win, ACS_VLINE, ACS_HLINE);
	wmove(go_win, 2, 10);
	wprintw(go_win, "GAME OVER");
	wmove(go_win, 4, 10);
	wprintw(go_win, "SCORE : %d", score);
	wmove(go_win, 6, 10);
	wprintw(go_win, "PRESS ANY KEY TO QUIT");
	wrefresh(go_win);
	sleep(2);
	getch();
}

int	ft_shmup(void)
{
	WINDOW		*stat_bar[4];
	clock_t		frame_start;
	int			ch;

	ft_shmupbg(bg);
	init_entities();
	init_stat_bar(stat_bar);
	nodelay(stdscr, TRUE);
	refresh();
	ch = -1;
	while (ch != 27)
	{
		frame_start = clock();
		ch = getch();
		if (ch == 410)
			break;
		update_entities(ch);
		update_bg(bg);
		print_entities();
		print_stats(stat_bar);
		refresh();
		flushinp();
		usleep(1000000 / FPS + frame_start - clock());
		if (lives <= 0)
			break;
	}
	game_over();
	endwin();
	system("clear");
	return (0);
}
