/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 16:28:42 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_philo *philo)
{
	if (!(philo->state == eating))
		return ;
	printf("\033[34m%lld %d  is sleeping\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = sleeping;
	usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	printf("\033[36m%lld %d  is thinking\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = thinking;
}

void	philo_eat(t_philo *philo)
{
	mutex(&philo->right_fork->fork, lock);
	printf("\033[33m%lld %d  has taken a fork\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	mutex(&philo->left_fork->fork, lock);
	printf("\033[33m%lld %d  has taken a fork\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	printf("\033[32m%lld %d  is eating\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = eating;
	usleep(philo->data->time_to_eat);
	philo->last_meal_time = ft_get_time() - philo->data->start_time;
	philo->meal_count++;
	mutex(&philo->right_fork->fork, unlock);
	mutex(&philo->left_fork->fork, unlock);
}

void	philo_dead(t_philo *philo)
{
	if (!((philo->last_meal_time - philo->data->start_time) >= philo->data->time_to_die))
		return ;
	printf("\033[31m%lld %d  died\033[0m\n", (ft_get_time() - philo->data->start_time), philo->id);
	philo->state = dead;
}


void	*philo_routine(void *var)
{
	t_philo	*philo;
	
	philo = (t_philo *)var;
	while (philo->meal_count != philo->data->max_meals && philo->state != dead && philo->data->end != true)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_dead(philo);
	}
	return (NULL);
}

void	*dead_monitoring(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (philo->data->end == false)
	{
		if ((ft_get_time() - philo->data->start_time) - philo->last_meal_time >= philo->data->time_to_die)
		{
			printf("MONITORING ** philo %d is dead %lld > %lld !!\n", philo->id, ((ft_get_time() - philo->data->start_time) - philo->last_meal_time), philo->data->time_to_die);
			philo->data->end = true;
		}
		philo = philo->next;
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philo)
{
	t_philo		*current;
	pthread_t	monitoring;

	current = philo;
	data->start_time = ft_get_time();
	thread(&current->thread_id, philo_routine, (void *)current, create);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, philo_routine, (void *)current, create);
		current = current->next;
	}
	current = philo;
	thread(&monitoring, dead_monitoring, (void *)philo, create);
	thread(&monitoring, NULL, NULL, join);
	thread(&current->thread_id, NULL, NULL, join);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, NULL, NULL, join);
		current = current->next;
	}
}
