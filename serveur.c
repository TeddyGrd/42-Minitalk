/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/04/02 19:17:37 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	extended_action(char *c, int *received, int *client_pid, int *bit)
{
	static char		str[MAX_BUFFER];
	static int		str_len = 0;

	if (*c == '\0')
	{
		str[str_len] = '\0';
		ft_printf("%s\n", str);
		ft_printf(" %d signal received from PID; %d\n", *received, *client_pid);
		*received = 0;
		*c = 0;
		if (kill(*client_pid, SIGUSR1) == -1)
			signal_error();
		str_len = 0;
		return ;
	}
	str[str_len++] = *c;
	*bit = 0;
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static int		client_pid;
	static int		bit;
	static char		c;
	static int		received;
	static int		current_pid;

	(void)context;
	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		client_pid = current_pid;
		bit = 0;
		c = 0;
		received = 0;
	}
	c |= (sig == SIGUSR2);
	received++;
	bit++;
	if (bit == 8)
		extended_action(&c, &received, &client_pid, &bit);
	c <<= 1 ;
	usleep(100);
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;

	pid = getpid();
	ft_printf("PID du serveur : %d \n", pid);
	s_sigaction.sa_sigaction = action;
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
	}
	return (0);
}
