/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:26:43 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/20 19:55:45 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_message(t_msg_info *msg)
{
	write(1, msg->msg, msg->msg_size);
	usleep(10000);
	if (kill(msg->pid, SIGUSR2) == -1)
		kill_error();
	ft_printf("\nsig sended\n");
	msg->pid = 0;
	free(msg->msg);
	//msg->msg = NULL;
	msg->msg_size = 0;
	msg->msg_index = 0;
	msg->byte_pos = 0;
	msg->bit_count = 0;
}

void	receive_size(unsigned char bit, t_msg_info *msg)
{
	bit <<= msg->bit_count;
	msg->msg_size |= bit;
	msg->bit_count++;
	if (msg->bit_count == 32)
	{
		msg->msg = malloc(msg->msg_size * sizeof(char));
		if (msg->msg == NULL)
			malloc_error();
	}
	usleep(10000);
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
	usleep(10000);
	if (kill(msg->pid, SIGUSR1) == -1)
		kill_error();
}

void	sig_listener(int sig, siginfo_t *info, void *uap)
{
	static t_msg_info	msg_info;
	unsigned char		bit;

	uap = NULL;
	if (msg_info.pid == 0)
	{
		if (info->si_pid && info->si_code <= 0)
			msg_info.pid = info->si_pid;
	}
	if (msg_info.pid == info->si_pid && info->si_code <= 0)
	{
		if (sig == SIGUSR1)
			bit = 0;
		else
			bit = 1;
		if (msg_info.bit_count < 32)
			receive_size(bit, &msg_info);
		else
		{
			receive_msg(bit, &msg_info);
			if (msg_info.msg_index == msg_info.msg_size)
				print_message(&msg_info);	
		}	
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
	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGUSR2, &sact, NULL);
	while (1)
		;
}
