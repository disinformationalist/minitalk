/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:28:31 by jhotchki          #+#    #+#             */
/*   Updated: 2024/01/31 09:28:33 by jhotchki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_flag = 0;

static void	confirm_sig(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGUSR1)
		g_flag = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_color("Message Successfully Recieved! ✅\n", "\033[1;93m");
		exit(0);
	}
}

static void	config_sig(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = confirm_sig;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}

static void	send_char(int pid, unsigned char octet)
{
	int					i;
	unsigned char		bit;

	i = 7;
	while (i >= 0)
	{
		g_flag = 0;
		bit = (octet >> i) & 1;
		if (bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (!g_flag)
			pause();
	}
}

static void	send_size(int pid, int size)
{
	int	i;
	int	bit;

	i = sizeof(int) * 8 - 1;
	while (i >= 0)
	{
		g_flag = 0;
		bit = (size >> i) & 1;
		if (bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (!g_flag)
			pause();
	}
}

int	main(int ac, char **av)
{
	int			i;
	const char	*msg;
	int			server_pid;
	int			msg_size;

	check(ac, av);
	config_sig();
	i = -1;
	server_pid = ft_atoi(av[1]);
	kill(server_pid, SIGUSR1);
	usleep(500);
	if (!g_flag)
		p_error("Pid entered does not match server or server is busy, retry");
	msg = av[2];
	msg_size = ft_strlen(msg);
	send_size(server_pid, msg_size);
	while (msg[++i])
		send_char(server_pid, msg[i]);
	send_char(server_pid, '\0');
	return (0);
}
