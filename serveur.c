/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/03/26 16:36:58 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void extended_action(char *c, int *received, int *client_pid, int *bit)
{
	static char *phrase = NULL;
    static int phrase_len = 0;
    static int phrase_capacity = 0;
	if (phrase == NULL)
	{
        phrase_capacity = 10; 
        phrase = (char*)malloc(phrase_capacity * sizeof(char));
        if (phrase == NULL)
    		exit (1);
        phrase_len = 0;
    }
    if (phrase_len + 1 >= phrase_capacity)
	{
        int new_capacity = phrase_capacity * 2;
        char *new_phrase = (char*)malloc(new_capacity * sizeof(char));
        if (new_phrase == NULL)
            exit (1);

	int i;
	i = 0;
        while (i < phrase_len)
		{
            new_phrase[i] = phrase[i];
			i++;
        }
        free(phrase);
        phrase = new_phrase;
        phrase_capacity = new_capacity;
	}
	phrase[phrase_len++] = *c;
	// ft_printf("%c",*c);
	if(*c == '\0')
	{
		ft_printf("%s \n",phrase);
		free(phrase);
        phrase = NULL;
        phrase_len = 0;
		ft_printf(" %d signal received from client PID; %d \n",*received, *client_pid);
		*received = 0;
		*c = 0;
		if (kill(*client_pid,SIGUSR1) == -1)
			signal_error();
		return;
	}
	*bit = 0;
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static int client_pid;
	static int	bit;
	static char	c;
	static int	received;
	static	int	current_pid;

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
	c <<=1;
	usleep(100);
	kill(client_pid,SIGUSR2);
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
