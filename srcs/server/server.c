/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:26:43 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/02 13:55:33 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_message(t_msg_info *msg)
{
	pid_t	pid_tmp;

	pid_tmp = msg->pid;
	write(1, msg->msg, msg->msg_size);
	free(msg->msg);
	ft_bzero(msg, sizeof(t_msg_info));
	if (kill(pid_tmp, SIGUSR2) == -1)
		kill_error();
}

void	receive_size(size_t bit, t_msg_info *msg)
{
	bit <<= msg->bit_count;
	msg->msg_size |= bit;
	msg->bit_count++;
	if (msg->bit_count == 32)
	{
		msg->msg = malloc(msg->msg_size * sizeof(char));
		if (msg->msg == NULL)
			malloc_error();
		ft_bzero(msg->msg, msg->msg_size * sizeof(char));
	}
	if (kill(msg->pid, SIGUSR1) == -1)
		kill_error();
}

void	receive_msg(unsigned char bit, t_msg_info *msg)
{
	bit <<= msg->byte_pos;
	msg->msg[msg->msg_index] |= bit;
	msg->byte_pos++;
	if (msg->byte_pos == 8)
		msg->msg_index++;
	msg->byte_pos %= 8;
	if (msg->msg_index == msg->msg_size)
		print_message(msg);
	else
	{
		if (kill(msg->pid, SIGUSR1) == -1)
			kill_error();
	}
}

void	sig_listener(int sig, siginfo_t *info, void *uap)
{
	static t_msg_info	msg_info;
	unsigned char		bit;

	(void)uap;
	if (msg_info.pid == 0)
	{
		msg_info.pid = info->si_pid;
		if (kill(msg_info.pid, SIGUSR1) == -1)
			kill_error();
		return ;
	}
	if (msg_info.pid == info->si_pid || info->si_pid == 0)
	{
		if (sig == SIGUSR1)
			bit = 1;
		else
			bit = 0;
		if (msg_info.bit_count < 32)
			receive_size(bit, &msg_info);
		else
			receive_msg(bit, &msg_info);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sact;

	pid = getpid();
	ft_printf("%d\n", pid);
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = SA_SIGINFO;
	sact.sa_sigaction = sig_listener;
	if (sigaction(SIGUSR1, &sact, NULL) == -1)
		sigaction_error();
	if (sigaction(SIGUSR2, &sact, NULL) == -1)
		sigaction_error();
	while (1)
		;
}
