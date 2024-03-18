# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 14:10:38 by tguerran          #+#    #+#              #
#    Updated: 2024/03/18 15:28:05 by tguerran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minitalk

CFLAGS = -Wall -Werror -Wextra 

SRC = serveur.c \
		minitalk_utils.c \
		client.c \
		error.c

SERVER_OFILES = serveur.o minitalk_utils.o error.o
CLIENT_OFILES = client.o minitalk_utils.o error.o

all: $(NAME) client.out

$(NAME): $(SERVER_OFILES)
	@make -C ft_printf
	cc $(CFLAGS) -o serveur.out $(SERVER_OFILES) ft_printf/libftprintf.a

client.out: $(CLIENT_OFILES)
	cc $(CFLAGS) -o client.out $(CLIENT_OFILES) ft_printf/libftprintf.a

clean:
	rm -f $(SERVER_OFILES) $(CLIENT_OFILES)
	@make clean -C ft_printf

fclean: clean 
	rm -f $(NAME) serveur.out client.out

re: fclean $(NAME) client.out