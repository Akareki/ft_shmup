/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:15:36 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/26 15:46:44 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"
#include <stdlib.h>


WINDOW	*shmup_title(void)
{
	WINDOW	*title;

	title = newwin(3, 19, 5, 50);
	wbkgd(title, COLOR_PAIR(2));
	box(title, ACS_VLINE, ACS_HLINE);
	wmove(title, 1, 7);
	wprintw(title, "SHMUP");
	wrefresh(title);
	return title;
}

int	menu_select(WINDOW **menu)
{
	int	selection;
	int	ch;

	selection = 0;
	wbkgd(menu[selection + 1], COLOR_PAIR(3));
	wrefresh(menu[selection + 1]);
	while (1)
	{
		ch = getch();
		if (ch == KEY_DOWN || ch == KEY_UP)
		{
			wbkgd(menu[selection + 1], COLOR_PAIR(2));
			wrefresh(menu[selection + 1]);
			if (ch == KEY_DOWN)
				selection = (selection + 1) % 4;
			else
				selection = (selection + 4 - 1) % 4;
			wbkgd(menu[selection + 1], COLOR_PAIR(3));
			wrefresh(menu[selection + 1]);
		}
		if (ch == 10)
			return (selection);
		if (ch == 27 || ch == 410)
			return (-1);
	}
}

int	shmup_menu(WINDOW **menu)
{
	menu[0] = newwin(12, 19, 9, 50);
	wbkgd(menu[0], COLOR_PAIR(2));
	box(menu[0], ACS_VLINE, ACS_HLINE);
	menu[1] = subwin(menu[0], 1, 15, 10, 53);
	wmove(menu[1], 1, 3);
	wprintw(menu[1], "NEW GAME");
	menu[2] = subwin(menu[0], 1, 15, 13, 53);
	wmove(menu[2], 1, 3);
	wprintw(menu[2], "CONTINUE");
	menu[3] = subwin(menu[0], 1, 15, 16, 53);
	wmove(menu[3], 1, 3);
	wprintw(menu[3], "CONTROLS");
	menu[4] = subwin(menu[0], 1, 15, 19, 53);
	wmove(menu[4], 1, 3);
	wprintw(menu[4], "EXIT");
	wrefresh(menu[0]);
	return (menu_select(menu));
}

void	shmup_settings(void)
{
	WINDOW	*settings[5];

	settings[0] = newwin(12, 19, 9, 50);
	wbkgd(settings[0], COLOR_PAIR(2));
	box(settings[0], ACS_VLINE, ACS_HLINE);
	settings[1] = subwin(settings[0], 1, 15, 10, 53);
	wmove(settings[1], 1, 3);
	wprintw(settings[1], "GO UP : ");
	waddch(settings[1], ACS_UARROW);
	settings[2] = subwin(settings[0], 1, 15, 13, 53);
	wmove(settings[2], 1, 3);
	wprintw(settings[2], "GO DOWN : ");
	waddch(settings[2], ACS_DARROW);
	settings[3] = subwin(settings[0], 1, 15, 16, 53);
	wmove(settings[3], 1, 3);
	wprintw(settings[3], "FIRE : <SPACE>");
	settings[4] = subwin(settings[0], 1, 15, 19, 53);
	wmove(settings[4], 1, 3);
	wprintw(settings[4], "EXIT : <ESC>");
	wrefresh(settings[0]);
	getch();

	return ;
}

int	main(void)
{
	char	*bg[25];
	int		selection;
	WINDOW	*menu[5];

	ft_shmupbg(bg);
	system("resize -s 25 80");
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
	update_bg(bg);
	while (1)
	{
		shmup_title();
		selection = shmup_menu(menu);
		delwin(menu[0]);
		touchwin(stdscr);
		refresh();
		if (selection == -1 || selection == 3)
			break ;
		if (selection == 0)
			return (ft_shmup());
		if (selection == 1)
			return (ft_shmup());
		if (selection == 2)
			shmup_settings();
	}
	endwin();
	system("clear");
	return (0);
}
