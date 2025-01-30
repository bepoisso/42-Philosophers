/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:48 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 14:40:37 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(t_data *data, t_fork *fork)
{
	t_philo	*philo;
	t_philo	*temp;
	int		i;

	i = 0;
	philo = NULL;
	temp = NULL;
	while (i < data->philo_nbr)
	{
		temp = ft_lstnew(i, data, fork);
		ft_lstadd_back(&philo, temp);
		i++;
	}
	temp = ft_lstlast(philo);
	temp->next = philo;
	philo->prev = temp;
	return (philo);
}

t_fork	*init_fork(t_data *data)
{
	t_fork	*fork;
	int		i;

	fork = (t_fork *)malloc(sizeof(t_fork) * (data->philo_nbr + 1));
	if (!fork)
		return (NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		fork[i].id = i;
		mutex(&fork[i].fork, init);
		i++;
	}
	fork[i].id = -1;
	return (fork);
}

void	init_data(t_data *data, t_philo *philo, t_fork *fork)
{
	data->end = false;
	data->philos = philo;
	data->forks = fork;
}
