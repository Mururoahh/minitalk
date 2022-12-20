/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:27:21 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/20 17:05:27 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include "libft.h"
# include "ft_printf.h"
# include "error.h"

typedef struct	s_msg_info
{
	pid_t			pid;
	char			*msg;
	size_t			msg_size;
	size_t			msg_index;
	int				byte_pos;
	int				bit_count;
}					t_msg_info;

#endif
