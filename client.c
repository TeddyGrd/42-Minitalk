/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:48 by tguerran          #+#    #+#             */
/*   Updated: 2024/03/13 16:17:51 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
 
void	signal_error(void)
{
	printf("client: unexpected error.");
	exit(EXIT_FAILURE);
}

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

void	recieved(int sig)
{
	static int	sent;

	if (sig == SIGUSR1)
	{
		printf("%d signal sent successfully! \n", ++sent);
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
		printf("client pid: %d\n", client_pid);
		signal(SIGUSR1, recieved);
		signal(SIGUSR2, recieved);
		server_pid = ft_atoi(av[1]);
		printf("Text currently sending..\n");
		sent_text(av[2], server_pid);
	}
	else
		printf("usage: ./client <server_pid> <text to send>\n");
	return (0);
}