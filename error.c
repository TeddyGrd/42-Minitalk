/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:01:02 by tguerran          #+#    #+#             */
/*   Updated: 2024/04/11 13:44:44 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_error(void)
{
	ft_printf("le pid n est pas bon");
	exit(1);
}

int	check_error(char **argv)
{
	if (ft_atoi(argv[1]) <= 0)
	{
		ft_printf("nope :) \n");
		return (1);
	}
	return (0);
}
