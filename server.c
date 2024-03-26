/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:27:59 by jhotchki          #+#    #+#             */
/*   Updated: 2024/01/31 09:28:04 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_flag = 0;

static void	size_bit_handler(int sig_val, t_data *data, char **str)
{
	data->size = data->size | (sig_val == SIGUSR1);
	(data->bit_num)++;
	if (data->bit_num == sizeof(int) * 8)
	{
		if (*str == NULL)
		{
			*str = (char *)malloc((data->size + 1) * sizeof(char));
			if (!*str)
				p_error("Error: malloc failure");
		}
		data->bit_num = 0;
		data->size = 0;
		data->receiving_data = 1;
	}
	else
		data->size = data->size << 1;
}

void	timeout(t_data *data, char **str)
{
	int	counter;

	counter = -1;
	while (!g_flag && ++counter < 10001)
		usleep(1);
	if (g_flag == 1)
		g_flag = 0;
	else
		reset(data, str);
}

static void	handle_data_bit(int sig_val, t_data *data, \
	char **str, int sender_pid)
{
	data->buffer = data->buffer | (sig_val == SIGUSR1);
	(data->bit_num)++;
	if (data->bit_num == 8)
	{
		(*str)[data->msg_index] = data->buffer;
		(data->msg_index)++;
		if (data->buffer == '\0')
		{
			ft_putstr_color("Message from client pid [", "\033[1;34m");
			write_num_color(sender_pid, "\033[1;96m");
			ft_putstr_color("]: ", "\033[1;34m");
			ft_putstr_color(*str, "\033[1;32m");
			ft_putchar('\n');
			reset(data, str);
			kill(sender_pid, SIGUSR2);
		}
		data->buffer = 0;
		data->bit_num = 0;
	}
	else
		data->buffer = data->buffer << 1;
	timeout(data, str);
}

static void	sig_handler(int sig_val, siginfo_t *info, void *context)
{
	static char		*str = NULL;
	static t_data	data;

	(void)context;
	if ((sig_val == SIGUSR1 || sig_val == SIGUSR2) && data.hand_shake == true)
		g_flag = 1;
	if (data.hand_shake == false && !(data.receiving_data))
	{
		kill(info->si_pid, SIGUSR1);
		data.hand_shake = true;
	}
	else if (!(data.receiving_data))
		size_bit_handler(sig_val, &data, &str);
	else
		handle_data_bit(sig_val, &data, &str, info->si_pid);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sigact;

	pid = getpid();
	sigact.sa_sigaction = &sig_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	print_welcome(pid);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		p_error("Error setting signal handler for SIGUSR1\n");
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		p_error("Error setting signal handler for SIGUSR2\n");
	while (1)
		pause();
	return (0);
}
