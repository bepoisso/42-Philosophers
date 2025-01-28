/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:48 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/28 17:23:07 by bepoisso         ###   ########.fr       */
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

	fork = (t_fork *)malloc(sizeof(t_fork) * data->philo_nbr);
	if (!fork)
		return (NULL);
	i = 0;
	while (i < data->philo_nbr)
	{
		fork[i].id = i;
		if (pthread_mutex_init(&fork[i].fork, NULL) != 0) // Init mutex if ERROR ...
		{
			while (--i >= 0)
				pthread_mutex_destroy(&fork[i].fork);
			free(fork);
			ft_perror("Error\nInitialisation mutex");
		}
		i++;
	}
	return (fork);
}
