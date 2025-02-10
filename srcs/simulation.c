/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/10 18:05:49 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void	philo_sleep(t_philo *philo)
{
	if (!(philo->state == eating))
		return ;
	ft_print(BLU"is sleeping"RES, philo);
	philo->state = sleeping;
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	ft_print(MAG"is thinking"RES, philo);
	philo->state = thinking;
}

void	philo_eat(t_philo *philo)
{
	mutex(&philo->right_fork->fork, lock);
	ft_print(GRE"has taken a fork"RES, philo);
	mutex(&philo->left_fork->fork, lock);
	ft_print(GRE"has taken a fork"RES, philo);
	ft_print(YEL"is eating"RES, philo);
	philo->last_meal_time = ft_get_time() - philo->data->start_time;
	philo->state = eating;
	usleep(philo->data->time_to_eat * 1000);
	mutex(&philo->meals, lock);
	philo->last_meal_time = ft_get_time() - philo->data->start_time;
	mutex(&philo->meals, unlock);
	mutex(&philo->right_fork->fork, unlock);
	mutex(&philo->left_fork->fork, unlock);
	philo->meal_count++;
	if (philo->meal_count == philo->data->max_meals)
	{
		mutex(&philo->data->meals, lock);
		philo->data->nbr_meals++;
		mutex(&philo->data->meals, unlock);
	}
}

void	philo_dead(t_philo *philo)
{
	if (!((ft_get_time() - philo->data->start_time) - philo->last_meal_time >= philo->data->time_to_die))
		return ;
	ft_print(RED"died"RES, philo);
	philo->state = dead;
}


void	*philo_routine(void *var)
{
	t_philo	*philo;
	
	philo = (t_philo *)var;
	if (philo->even)
	{
		philo_think(philo);
		usleep(philo->data->time_to_eat);
	}
	while (philo->state != dead && philo->data->end == false)
	{
		if (philo->data->end == false)
			philo_eat(philo);
		if (philo)
		if (philo->data->end == false)
			philo_sleep(philo);
		if (philo->data->end == false)
			philo_think(philo);
	}
	return (NULL);
}

void	*monitoring(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (philo->data->end == false)
	{
		if ((ft_get_time() - philo->data->start_time) - philo->last_meal_time > philo->data->time_to_die)
		{
			philo_dead(philo);
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
			break ;
		}
		mutex(&philo->data->meals, lock);
		if (philo->data->nbr_meals >= philo->data->philo_nbr)
		{
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
			mutex(&philo->data->meals, unlock);
			break ;
		}
		mutex(&philo->data->meals, unlock);
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