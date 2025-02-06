/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/10 18:01:14 by bepoisso         ###   ########.fr       */
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
	else
		philo_think(philo);
	while (1)
	{
		if (philo->data->end == false)
			philo_eat(philo);
		if (philo)
		if (philo->data->end == false)
			philo_sleep(philo);
		if (philo->data->end == false)
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

	int i = 0;
	// philo->prev->next = NULL;
	current = philo;
	data->start_time = ft_get_time();
	thread(&mon, monitoring, (void *)philo, create);
	thread(&current->thread_id, philo_routine, (void *)current, create);
	current = current->next;
	while (current != philo)
	{
		//printf("%d\n", current->id);
		thread(&current->thread_id, philo_routine, current, create);
		current = current->next;
		i++;
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
