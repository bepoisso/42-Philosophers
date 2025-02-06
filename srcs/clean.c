/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:18 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/06 07:48:35 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_fork(t_fork *fork)
{
	int	i;

	i = 0;
	while (fork[i].id != -1)
	{
		mutex(&fork[i].fork, destroy);
		i++;
	}
	free(fork);
}

void	free_philo(t_philo **philo)
{
	t_philo	*temp;

	if (!philo || !*philo)
		return ;
	(*philo)->prev->next = NULL;
	while (*philo)
	{
		temp = (*philo)->next;
		free(*philo);
		*philo = temp;
	}
	*philo = NULL;
}
