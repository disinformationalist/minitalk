/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:28:56 by jhotchki          #+#    #+#             */
/*   Updated: 2024/01/31 09:28:58 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include "libft/libftprintf/ft_printf.h"
# include <signal.h>
# include <stdbool.h>

typedef struct s_data
{
	unsigned char	buffer;
	int				bit_num;
	int				size;
	int				msg_index;
	bool			hand_shake;
	bool			receiving_data;
}		t_data;

void	check(int ac, char **av);
void	p_error(char *error_message);
void	print_welcome(int pid);
void	ft_putstr_color(char *s, char *color);
void	ft_putchar_color(char c, char *color);
void	reset(t_data *data, char **str);
void	write_num_color(int num, char *color);

#endif
