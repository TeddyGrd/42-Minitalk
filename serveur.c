/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/03/13 15:46:59 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *s)
{
    while (*s)
        ft_putchar(*s++);
}

void    ft_putnbr(int n)
{
    unsigned int    nb;
 
    nb = n;
    if (n < 0)
    {
        nb = n * -1;
        ft_putchar('-');
    }
    if (nb >= 10)
        ft_putnbr(nb / 10);
    ft_putchar(nb % 10 + '0');
}

void	signal_error(void)
{
	printf("server; unexpected error");
	exit(EXIT_FAILURE);
}

void extended_action(char *c, int *received, int *client_pid, int *bit)
{
	putchar(*c);
	if(*c == '\0')
	{
		printf("%d signal received from client PID; %d \n",*received, *client_pid);
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
	printf("PID du serveur : %d \n", pid);
	s_sigaction.sa_sigaction = action;
	sigemptyset(&s_sigaction.sa_mask);
	s_sigaction.sa_flags = SA_SIGINFO;
	while (1)
	{
		sigaction(SIGUSR1, &s_sigaction, 0);
		sigaction(SIGUSR2, &s_sigaction, 0);
		pause();
	}
	return (0);
}

// void    tst(int signalnum)
// {
//     static const unsigned int   pow[] = {1, 2, 4, 8, 16, 32, 64, 128};
//     static int nsig = 7;
//     static unsigned char c = 0;
//     if (signalnum > 0)
//     {
//         if (signalnum == SIGUSR1)
//             c += pow[nsig];
//         nsig--;
//     }
//     if (nsig == -1)
//     {
//         ft_putchar(c);
//         c = 0;
//         nsig = 7;
//     }
//     usleep(500);
// }
 
// void signal_handler(int signum) {
//     static char str[100];
//     static int  index;
//     index = 0;
//     if (signum == SIGUSR2) 
//     {
//         str[index] = '\0';
//         printf("Chaine recu %s \n", str);
//         index = 0;
//     }
//     else
//     {
//         str[index++] = signum - SIGUSR1;
//     }
// }

 
// int main(int ac, char **av)
// {
//     struct sigaction sa;
//     sa.sa_handler = signal_handler;
//     sa.sa_flags = 0;
//     ft_putstr("mon pid : ");
//     ft_putnbr(getpid());
//     ft_putchar('\n');
//     sigaction(SIGUSR1, &sa, NULL);
//     sigaction(SIGUSR2, &sa, NULL);
//     while (1)
//         sleep(1);
//     return (0);
// }