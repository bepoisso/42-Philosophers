/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 13:27:42 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


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

void	take_a_fork(t_philo *philo, t_mutex *fork)
{
	mutex(fork, lock);
	ft_print(GRE"has taken a fork"RES, philo);
}

void	upgrade_time(t_philo *philo)
{
	mutex(&philo->meals, lock);
	philo->last_meal_time = ft_get_time();
	mutex(&philo->meals, unlock);
}

void	philo_eat(t_philo *philo)
{
	take_a_fork(philo, &philo->left_fork->fork);
	take_a_fork(philo, &philo->right_fork->fork);
	ft_print(YEL"is eating"RES, philo);
	// upgrade_time(philo);
	ft_sleep(philo->data->time_to_eat);
	upgrade_time(philo);
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

void	philo_dead(t_philo *philo)
{
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

void	*monitoring(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	while (philo->data->end == false)
	{
		mutex(&philo->meals, lock);
		if ((ft_get_time() - philo->data->start_time) - philo->last_meal_time >= philo->data->time_to_die)
		{
			philo_dead(philo);
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
			mutex(&philo->meals, unlock);
			break ;
		}
		mutex(&philo->meals, unlock);
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
	// TESTER
	current = philo;
	printf("Philo : %d eat : %d time\n", current->id, current->meal_count);
	current = current->next;
	while (current != philo)
	{
		printf("Philo : %d eat : %d time\n", current->id, current->meal_count);
		current = current->next;
	}
	// TESTER
}