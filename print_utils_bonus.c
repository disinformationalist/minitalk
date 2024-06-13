/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:29:24 by jhotchki          #+#    #+#             */
/*   Updated: 2024/01/31 09:29:28 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putchar_color(char c, char *color)
{
	write(1, color, 7);
	write(1, &c, 1);
	write(1, "\033[0m", 5);
}

void	ft_putstr_color(char *s, char *color)
{
	write(1, color, 7);
	while (*s)
		write(1, s++, 1);
	write(1, "\033[0m", 5);
}

void	write_num_color(int num, char *color)
{
	if (num / 10)
		write_num_color(num / 10, color);
	write(1, color, 7);
	write(1, &("0123456789"[num % 10]), 1);
	write(1, "\033[0m", 5);
}

void	print_welcome_2(int pid, char *color)
{
	int	temp;
	int	count;
	int	n;

	temp = pid;
	count = 0;
	ft_putstr_color(" ║░░✯✯✯✯✯✯ SERVER PID: ", color);
	while (temp)
	{
		temp /= 10;
		count++;
	}
	n = 10 - count;
	write_num_color(pid, "\033[1;92m");
	while (--n)
		write(1, " ", 1);
	ft_putstr_color("╔══════╗ BROUGHT TO YOU BY: ", color);
	ft_putstr_color("JHOTCHKI", "\033[1;92m");
	ft_putstr_color("✯✯✯✯✯✯░░║\n", color);
	ft_putstr_color(" ╚═══════════════════════════════╣  📡 "
		" ╠═════════════════════════════════════╝\n", color);
	ft_putstr_color("             ✯ ✯ ✯", "\033[1;93m");
	ft_putstr_color("═══════════════╝      ╚═════════════════", color);
	ft_putstr_color(" ✯ ✯ ✯                  \n", "\033[1;93m");
}

void	print_welcome(int pid)
{
	char	*color;

	color = "\033[94m";
	ft_putstr_color(" ╔════════════════════════════════════"
		"════════════════════════════════════════╗\n", color);
	ft_putstr_color(" ║░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░"
		"░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░║\n", color);
	ft_putstr_color(" ║░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
		"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒███╗▒▒▒███╗▒██╗▒███╗▒▒██╗▒██╗▒██"
		"██████╗▒▒▒████╗▒▒▒▒██╗▒▒▒▒▒▒▒██╗▒██╗▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒████╗▒████║▒██║▒████╗▒██║▒██║▒▒▒"
		"▒██╔══╝▒▒██╔═██╗▒▒▒██║▒▒▒▒▒▒▒██║██╔╝▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒██╔████╔██║▒██║▒██╔██╗██║▒██║▒▒▒"
		"▒██║▒▒▒▒████████╗▒▒██║▒▒▒▒▒▒▒████╔╝▒▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒██║╚██╔╝██║▒██║▒██║╚████║▒██║▒▒▒"
		"▒██║▒▒▒▒██╔═══██║▒▒██║▒▒▒▒▒▒▒██╔██╗▒▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒██║▒╚═╝▒██║▒██║▒██║▒╚███║▒██║▒▒▒"
		"▒██║▒▒▒▒██║▒▒▒██║▒▒███████╗▒▒██║╚██╗▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒╚═╝▒▒▒▒▒╚═╝▒╚═╝▒╚═╝▒▒╚══╝▒╚═╝▒▒▒"
		"▒╚═╝▒▒▒▒╚═╝▒▒▒╚═╝▒▒╚══════╝▒▒╚═╝▒╚═╝▒▒░░║\n", color);
	ft_putstr_color(" ║░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒"
		"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░║\n", color);
	print_welcome_2(pid, color);
}
