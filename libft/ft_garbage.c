/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:58:59 by hulescur          #+#    #+#             */
/*   Updated: 2026/08/06 00:10:26 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_newnode(t_list **head, int size)
{
	t_list	*new;
	t_list	*temp;
	void	*ptr;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(size);
	if (!new->content)
		return(free(new), NULL);
	ptr = new->content;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (ptr);
}

void	*ft_malloc(int size)
{
	static t_list	*head = NULL;
	void			*ptr;
	
	if (size == -1)
		return (&head);
	ptr = ft_newnode(&head, size);
	if (!ptr)
		return (ft_putendl_fd("malloc error", 2), NULL);
	return (ptr);
}

void	ft_free(void)
{
	t_list	**lsthead;
	t_list	*head;
	t_list	*temp;
	

	lsthead = ft_malloc(-1);
	head = *lsthead;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
	*lsthead = NULL;
}