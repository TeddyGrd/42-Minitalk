/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:16:48 by tguerran          #+#    #+#             */
/*   Updated: 2024/02/07 16:19:57 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


static int  ft_isspace(const char c)
{
    return (c == ' ' || c == '\t' || c == '\v'
        || c == '\n' || c == '\r' || c == '\f');
}
 
void    encode(int pid, unsigned char *encode)
{
    static const int signals[] = {SIGUSR2, SIGUSR1};
    while (*encode)
    {
        unsigned int i = 1 << 7;
        while (i)
        {
            kill(pid, signals[*encode & i ? 1 : 0]);
            i >>= 1;
            usleep(200);
        }
        encode++;
    }
}
 
int     main(int ac, char **av)
{
    if (ac == 3)
        encode(ft_atoi(av[1]), (unsigned char *)av[2]);
    return (0);
}