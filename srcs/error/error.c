/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:53:01 by hferraud          #+#    #+#             */
/*   Updated: 2022/12/20 16:56:23 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	malloc_error(void)
{
	ft_putstr_fd("Malloc Error", 2);
	exit(1);
}

void	kill_error(void)
{
	ft_putstr_fd("Kill Error", 2);
	exit(1);
}
