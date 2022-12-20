/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:23:05 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/20 19:39:01 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_size(pid_t dest, size_t size)
{
	int				count;

	count = 0;
	while (count < 32)
	{
		if (size & 1)
		{
			if (kill(dest, SIGUSR2) == -1)
				kill_error();
		}
		else
		{
			if (kill(dest, SIGUSR1) == -1)
				kill_error();
		}
		pause();
		size >>= 1;
		count++;
	}
}

void	send_byte(pid_t dest, unsigned char bit)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (bit & 1)
		{
			if (kill(dest, SIGUSR2) == -1)
				kill_error();
		}
		else
		{
			if (kill(dest, SIGUSR1) == -1)
				kill_error();
		}
		pause();
		bit >>= 1;
		i++;
	}
}

void	send_message(pid_t dest, char *str)
{
	while (*str)
	{
		send_byte(dest, *str);
		str++;
	}
}

void	sig_listener(int sig, siginfo_t *info, void *uap)
{
	info = NULL;
	uap = NULL;
	if (sig == SIGUSR1)
		write(1, "ping\n", 5);
	else if (sig == SIGUSR2)
		write(1, "pong\n", 5);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sact;

	if (argc != 3)
		return (0);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = sig_listener;
	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGUSR2, &sact, NULL);
	pid = ft_atoi(argv[1]);
	send_size(pid, ft_strlen(argv[2]));
	send_message(pid, argv[2]);
	pause();
}
