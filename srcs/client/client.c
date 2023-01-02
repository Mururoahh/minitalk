/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:23:05 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/02 13:55:21 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_msg_state	g_msginf;

void	send_size(pid_t dest, size_t size, int bit_pos)
{
	size >>= bit_pos;
	g_msginf.size_bit_pos++;
	if (size & 1)
	{
		if (kill(dest, SIGUSR1) == -1)
			kill_error();
	}
	else
	{
		if (kill(dest, SIGUSR2) == -1)
			kill_error();
	}
}

void	send_message(pid_t dest, unsigned char bit)
{
	g_msginf.msg_bit_pos++;
	if (g_msginf.msg_bit_pos == 8)
		g_msginf.index++;
	g_msginf.msg_bit_pos %= 8;
	if (bit & 1)
	{
		if (kill(dest, SIGUSR1) == -1)
			kill_error();
	}
	else
	{
		if (kill(dest, SIGUSR2) == -1)
			kill_error();
	}
}

void	sig_listener(int sig, siginfo_t *info, void *uap)
{
	(void)uap;
	(void)info;
	if (sig == SIGUSR2)
	{
		ft_printf("Message received !\n");
		exit (0);
	}
	else
	{
		if (g_msginf.server_state == PENDING)
			g_msginf.server_state = RESOLVED;
		if (g_msginf.size_bit_pos < SIZE_SEND)
			send_size(g_msginf.pid, g_msginf.size, g_msginf.size_bit_pos);
		else
			send_message(g_msginf.pid,
				g_msginf.msg[g_msginf.index] >> g_msginf.msg_bit_pos);
	}
}

void	init_msg_info(pid_t	pid, char *msg)
{
	g_msginf.pid = pid;
	g_msginf.msg = msg;
	g_msginf.size = ft_strlen(msg);
	g_msginf.index = 0;
	g_msginf.size_bit_pos = 0;
	g_msginf.msg_bit_pos = 0;
	g_msginf.server_state = PENDING;
}

int	main(int argc, char **argv)
{
	struct sigaction	sact;

	if (argc != 3)
		arg_error();
	init_msg_info(ft_atoi(argv[1]), argv[2]);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = sig_listener;
	if (sigaction(SIGUSR1, &sact, NULL) == -1)
		sigaction_error();
	if (sigaction(SIGUSR2, &sact, NULL) == -1)
		sigaction_error();
	if (kill(g_msginf.pid, SIGUSR1))
		kill_error();
	while (1)
		;
}
