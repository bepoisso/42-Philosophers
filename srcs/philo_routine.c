/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:16:23 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 14:18:46 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_dead(t_philo *philo)
{
	ft_print(RED"died"RES, philo);
	philo->state = dead;
}

void	philo_sleep(t_philo *philo)
{
	ft_print(BLU"is sleeping"RES, philo);
	philo->state = sleeping;
	ft_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	ft_print(MAG"is thinking"RES, philo);
	philo->state = thinking;
}

void	philo_eat(t_philo *philo)
{
	take_a_fork(philo, &philo->left_fork->fork);
	take_a_fork(philo, &philo->right_fork->fork);
	ft_print(YEL"is eating"RES, philo);
	upgrade_time(philo);
	ft_sleep(philo->data->time_to_eat);
	mutex(&philo->left_fork->fork, unlock);
	mutex(&philo->right_fork->fork, unlock);
	mutex(&philo->meals, lock);
	philo->meal_count++;
	mutex(&philo->data->meals, lock);
	if (philo->meal_count == philo->data->max_meals)
		philo->data->nbr_meals++;
	mutex(&philo->meals, unlock);
	mutex(&philo->data->meals, unlock);
}

void	*philo_routine(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->even)
	{
		philo_think(philo);
		ft_sleep(philo->data->time_to_eat);
	}
	mutex(&philo->data->finish, lock);
	while (philo->data->end == false)
	{
		mutex(&philo->data->finish, unlock);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		mutex(&philo->data->finish, lock);
	}
	mutex(&philo->data->finish, unlock);
	return (NULL);
}
