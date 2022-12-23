/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoahh <mururoahh@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:58:22 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/23 12:31:42 by mururoahh        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>
# include "libft.h"
# include "ft_printf.h"
# include "error.h"

enum
{
	PENDING = 0,
	RESOLVED = 1,
	SIZE_SEND = 32
};

typedef struct s_msg_state
{
	pid_t	pid;
	char	*msg;
	size_t	size;
	size_t	index;
	int		msg_bit_pos;
	int		size_bit_pos;
	int		server_state;
}			t_msg_state;

#endif
