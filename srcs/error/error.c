/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoahh <mururoahh@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:53:01 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/23 21:22:43 by mururoahh        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <errno.h>

void	malloc_error(void)
{
	ft_putstr_fd("Malloc Error\n", 2);
	exit(1);
}

void	kill_error(void)
{
	ft_putstr_fd("Kill Error\n", 2);
	exit(1);
}

void	arg_error(void)
{
	ft_putstr_fd("Arg Error\n", 2);
	exit(0);
}