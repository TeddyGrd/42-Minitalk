/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:48 by tguerran          #+#    #+#             */
/*   Updated: 2024/03/18 15:40:21 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
 
void	char_to_bin(unsigned char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & 128)
		{
			if (kill(pid, SIGUSR2) == -1)
				signal_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				signal_error();
		}
		c <<= 1;
		bit++;
		pause();
	}
}

void	sent_text(char *str, int pid)
{
	int	i;

	i = 0;
	while (str[i])
		char_to_bin(str[i++], pid);
	char_to_bin('\0', pid);
}

void	received(int sig)
{
	static int	sent;

	if (sig == SIGUSR1)
	{
		ft_printf("%d signal sent successfully! \n", ++sent);
		exit(0);
	}
	if (sig == SIGUSR2)
		++sent;
}

int	main(int ac, char **av)
{
	int	server_pid;
	int	client_pid;

	client_pid = getpid();
	if (ac == 3)
	{
		ft_printf("client pid: %d\n", client_pid);
		signal(SIGUSR1, received);
		signal(SIGUSR2, received);
		server_pid = ft_atoi(av[1]);
		ft_printf("Text currently sending..\n");
		sent_text(av[2], server_pid);
	}
	else
		ft_printf("usage: ./client <server_pid> <text to send>\n");
	return (0);
}