/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:37:31 by jhotchki          #+#    #+#             */
/*   Updated: 2024/02/04 11:37:36 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	p_error(char *error_message)
{
	ft_putstr_color(error_message, "\033[1;31m");
	ft_putchar('\n');
	exit(1);
}

void	check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
		p_error("Syntax: ./client <pid> <\"message to send\">");
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
			p_error("Error: Invalid pid");
		else if (ft_atoi(av[1]) <= 11)
			p_error("Error: Cannot enter pid <= 11 (kernal processes)");
		i++;
	}
	if (!av[2][0])
		p_error("Error: Empty Message");
}

void	reset(t_data *data, char **str)
{
	free(*str);
	*str = NULL;
	data->receiving_data = 0;
	data->msg_index = 0;
	data->hand_shake = 0;
}
