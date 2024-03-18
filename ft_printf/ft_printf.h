/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:03:46 by tguerran          #+#    #+#             */
/*   Updated: 2024/03/18 14:19:41 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_putchar(const char c);
size_t	ft_putnbr(int nb);
size_t	ft_putstr(char *s);
size_t	ft_puthex_l(unsigned int nb);
size_t	ft_puthex_u(unsigned int nb);
size_t	ft_putunbr(unsigned int nb);
size_t	ft_putptr(void *nb);
int		ft_printf(const char *format, ...);

#endif