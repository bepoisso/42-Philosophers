/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/10 17:01:47 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	philo_sleep(t_philo *philo)
{
	ft_print(BLU"is sleeping"RES, philo);
	philo->state = sleeping;
	ft_sleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	ft_print(MAG"is thinking"RES, philo);
	philo->state = thinking;
}

void	take_a_fork(t_philo *philo, t_fork *fork)
{
	mutex(&fork->fork, lock);
	ft_print(GRE"has taken a fork"RES, philo);
	mutex(&fork->fork, unlock);
}

void	philo_eat(t_philo *philo)
{
	take_a_fork(philo, philo->left_fork);
	take_a_fork(philo, philo->right_fork);
	mutex(&philo->meals, lock);
	philo->last_meal_time = ft_get_time();
	mutex(&philo->meals, unlock);
	ft_print(YEL"is eating"RES, philo);
	philo->state = eating;
	ft_sleep(philo->data->time_to_eat * 1000);
	mutex(&philo->meals, lock);
	philo->meal_count++;
	philo->last_meal_time = ft_get_time();
	mutex(&philo->data->meals, lock);
	if (philo->meal_count == philo->data->max_meals)
		philo->data->nbr_meals++;
	mutex(&philo->meals, unlock);
	mutex(&philo->data->meals, unlock);
}

void	philo_dead(t_philo *philo)
{
	ft_print(RED"died"RES, philo);
	philo->state = dead;
}

int	check_dead(t_philo *philo)
{
	if (ft_get_time() - philo->last_meal_time >= philo->data->time_to_die)
		return (1);
	return (0);
}

int	check_meals(t_philo *philo)
{
	if (philo->data->nbr_meals >= philo->data->max_meals)
		return (1);
	return (0);
}


void	*philo_routine(void *var)
{
	t_philo	*philo;
	
	philo = (t_philo *)var;
	if (philo->even)
	{
		philo_think(philo);
		ft_sleep(philo->data->time_to_eat * 1000);
	}
	while (1)
	{
		if (is_ended(philo->data))
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

void	*monitoring(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	philo->prev->next = philo;
	while (1)
	{
		if (is_ended(philo->data))
			return (NULL);
		if (check_dead(philo))
		{
			philo_dead(philo);
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
		}
		if (philo->data->max_meals != -1 && check_meals(philo))
		{
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
		}
		philo = philo->next;
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philo)
{
	t_philo		*current;
	pthread_t	mon;

	philo->prev->next = NULL;
	current = philo;
	data->start_time = ft_get_time();
	thread(&mon, monitoring, philo, create);
	while (current)
	{
		thread(&current->thread_id, philo_routine, current, create);
		current = current->next;
	}
	current = philo;
	philo->prev->next = NULL;
	thread(&mon, NULL, NULL, join);
	while (current)
	{
		thread(&current->thread_id, NULL, NULL, join);
		current = current->next;
	}
}
