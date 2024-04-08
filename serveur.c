/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/04/04 01:45:26 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <string.h>

void	allocate_memory(char **str, int *str_capacity)
{
	if (*str == NULL)
	{
		*str_capacity = 10;
		*str = (char *)malloc(*str_capacity * sizeof(char));
		if (!(*str))
			exit(1);
	}
}

void	reallocate_memory(char **str, int *str_len, int *str_capacity)
{
	int		new_capacity;
	int		i;
	char	*new_str;

	i = 0;
	if (!(*str) || *str_len == 0 || *str_capacity == 0)
		return ;
	new_capacity = *str_capacity * 2;
	new_str = (char *)malloc(new_capacity * sizeof(char));
	if (!new_str)
		exit(1);
	while (i < *str_len)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	free(*str);
	*str = new_str;
	*str_capacity = new_capacity;
}

void	extended_action(char *c, int *received, int *client_pid, int *bit)
{
	static char		*str = NULL;
	static int		str_len = 0;
	static int		str_capacity = 0;

	allocate_memory(&str, &str_capacity);
	if (str_len + 1 >= str_capacity)
		reallocate_memory(&str, &str_len, &str_capacity);
	str[str_len++] = *c;
	if (*c == '\0')
	{
		ft_printf("%s \n", str);
		free(str);
		str = NULL;
		str_len = 0;
		ft_printf("%d signal received from PID; %d \n", *received, *client_pid);
		*received = 0;
		*c = 0;
		return ;
	}
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
