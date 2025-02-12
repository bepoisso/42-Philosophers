/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 14:26:12 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	died(t_philo *philo)
{
	mutex(&philo->meals, lock);
	if ((ft_get_time() - philo->data->start_time) - philo->last_meal_time
		>= philo->data->time_to_die)
	{
		philo_dead(philo);
		mutex(&philo->data->finish, lock);
		philo->data->end = true;
		mutex(&philo->data->finish, unlock);
		mutex(&philo->meals, unlock);
		return (1);
	}
	mutex(&philo->meals, unlock);
	return (0);
}

static int	max_meals(t_philo *philo)
{
	mutex(&philo->data->meals, lock);
	if (philo->data->nbr_meals >= philo->data->philo_nbr)
	{
		mutex(&philo->data->finish, lock);
		philo->data->end = true;
		mutex(&philo->data->finish, unlock);
		mutex(&philo->data->meals, unlock);
		return (1);
	}
	mutex(&philo->data->meals, unlock);
	return (0);
}

void	*monitoring(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (philo->data->end == false)
	{
		if (died(philo))
			break ;
		if (max_meals(philo))
			break ;
		philo = philo->next;
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philo)
{
	t_philo		*current;
	pthread_t	mon;

	current = philo;
	data->start_time = ft_get_time();
	thread(&mon, monitoring, (void *)philo, create);
	thread(&current->thread_id, philo_routine, (void *)current, create);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, philo_routine, (void *)current, create);
		current = current->next;
	}
	current = philo;
	thread(&mon, NULL, NULL, join);
	thread(&current->thread_id, NULL, NULL, join);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, NULL, NULL, join);
		current = current->next;
	}
}
