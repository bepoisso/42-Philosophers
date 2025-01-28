/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/28 17:10:15 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philo *philo)
{
	if (!(philo->state == eating))
		return ;
	printf("%lld %d  is sleeping\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = sleeping;
	usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	if (philo->state == thinking)
		return ;
	printf("%lld %d  is thinking\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = thinking;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	printf("%lld %d  has taken a fork\n", (ft_get_time() - philo->data->start_time), philo->id);
	pthread_mutex_lock(&philo->left_fork->fork);
	printf("%lld %d  has taken a fork\n", (ft_get_time() - philo->data->start_time), philo->id);
	printf("%lld %d  is eating\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = eating;
	usleep(philo->data->time_to_eat);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	philo_dead(t_philo *philo)
{
	if (!((ft_get_time() - philo->data->start_time) >= philo->data->time_to_die))
		return ;
	printf("%lld %d  died\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->data->end = 1;
	philo->state = dead;
}


void	*philo_routine(void *var)
{
	t_philo	*philo;
	
	philo = (t_philo *)var;
	while ((philo->meal_count != philo->data->max_meals || philo->state != dead) && philo->data->end != 1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_dead(philo);
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philo)
{
	t_philo	*current;

	current = philo;
	data->start_time = ft_get_time();
	pthread_create(&current->thread_id, NULL, philo_routine, (void *)philo);
	current = current->next;
	while (current != philo)
	{
		pthread_create(&current->thread_id, NULL, philo_routine, (void *)philo);
		current = current->next;
	}
	pthread_join(current->thread_id, NULL);
	current = current->next;
	while (current != philo)
	{
		pthread_join(current->thread_id, NULL);
		current = current->next;
	}
}
