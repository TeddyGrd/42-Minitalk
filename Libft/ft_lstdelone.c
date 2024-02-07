/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerran <tguerran@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:58:28 by tguerran          #+#    #+#             */
/*   Updated: 2023/11/03 14:58:28 by tguerran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}
/*
void my_del(void *content)
{
	free(content);
}

int main()
{
	t_list *list = ft_lstnew("Hello, World!");
	printf("liste avant la suppression : %s\n", (char *)list->content);
	ft_lstdelone(list, my_del);
	if (list)
		printf("suppression echoue. Contenu restant : %s\n", (char *)list->content);
	else
		printf("element supprime avec succes.\n");
	return 0;
}
*/