/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:26:13 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/06 07:34:43 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_lstnew(int content, t_data *data, t_fork *fork)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->id = content;
	new->state = thinking;
	new->next = NULL;
	new->data = data;
	new->right_fork = &fork[(content - 1 + data->philo_nbr) % data->philo_nbr];
	new->left_fork = &fork[content];
	new->even = content % 2;
	return (new);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

t_philo	*ft_lstlast(t_philo *lst)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lstsize(lst);
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

int	ft_lstsize(t_philo *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
