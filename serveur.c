/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/04/11 13:59:56 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char		*g_str = NULL;

void	sigint_handler(int signum)
{
	if (g_str != NULL)
		free(g_str);
	exit(signum);
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

void	extended_action(char *c, int *client_pid, int *bit)
{
	static int		str_len = 0;
	static int		str_capacity = 0;

	if (g_str == NULL)
	{
		str_capacity = 10;
		g_str = (char *)malloc(str_capacity * sizeof(char));
		if (!(g_str))
			exit(1);
	}
	if (str_len + 1 >= str_capacity)
		reallocate_memory(&g_str, &str_len, &str_capacity);
	g_str[str_len++] = *c;
	if (*c == '\0')
	{
		ft_printf("%s \n", g_str);
		free(g_str);
		g_str = NULL;
		str_len = 0;
		ft_printf("signal received from PID; %d \n", *client_pid);
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
	}
	c |= (sig == SIGUSR2);
	bit++;
	if (bit == 8)
		extended_action(&c, &client_pid, &bit);
	c <<= 1 ;
	usleep(100);
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_sigaction;
	struct sigaction	sigint_action;

	pid = getpid();
	ft_printf("PID du serveur : %d \n", pid);
	s_sigaction.sa_sigaction = action;
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_flags = SA_SIGINFO;
	sigint_action.sa_handler = sigint_handler;
	sigemptyset(&sigint_action.sa_mask);
	sigint_action.sa_flags = 0;
	sigaction(SIGINT, &sigint_action, NULL);
	while (1)
	{
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
	}
	return (0);
}
