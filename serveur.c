/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:45 by tguerran          #+#    #+#             */
/*   Updated: 2024/02/07 15:54:31 by tguerran         ###   ########.fr       */
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
 
void    tst(int signalnum)
{
    static const unsigned int   pow[] = {1, 2, 4, 8, 16, 32, 64, 128};
    static int nsig = 7;
    static unsigned char c = 0;
    if (signalnum > 0)
    {
        if (signalnum == SIGUSR1)
            c += pow[nsig];
        nsig--;
    }
    if (nsig == -1)
    {
        ft_putchar(c);
        c = 0;
        nsig = 7;
    }
    usleep(100);
}
 
 
int main(int ac, char **av)
{
    ft_putnbr(getpid());
    signal(SIGUSR1, tst);
    signal(SIGUSR2, tst);
    while (42)
        ;
    return (0);
}