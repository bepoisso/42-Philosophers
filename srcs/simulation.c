/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/04 17:25:46 by bepoisso         ###   ########.fr       */
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
	if (philo->data->end == true)
		return ;
	ft_print(GRE"has taken a fork"RES, philo);
	if (philo->data->end == true)
		return ;
	mutex(&philo->left_fork->fork, lock);
	if (philo->data->end == true)
		return ;
	ft_print(GRE"has taken a fork"RES, philo);
	ft_print(YEL"is eating"RES, philo);
	philo->last_meal_time = ft_get_time() - philo->data->start_time;
	philo->state = eating;
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal_time = ft_get_time() - philo->data->start_time;
	philo->meal_count++;
	mutex(&philo->right_fork->fork, unlock);
	mutex(&philo->left_fork->fork, unlock);
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
		usleep(philo->data->time_to_eat * 1000);
	}
	while (philo->state != dead && philo->data->end == false)
	{
		if (philo->data->end == false)
			philo_think(philo);
		if (philo->data->end == false)
			philo_eat(philo);
		if (philo->data->end == false)
			philo_sleep(philo);
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
			printf("DEAD PHILO\n");
			mutex(&philo->data->finish, lock);
			philo->data->end = true;
			mutex(&philo->data->finish, unlock);
			philo_dead(philo);
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}

void	*meals_monitoring(void *var)
{
	t_philo	*philo;
	t_philo	*current;
	bool	check;
	check = false;
	philo = (t_philo *)var;
	while (check == false)
	{
		current = philo->next;
		while (current != philo) // a check si le premier est bien tester
		{
			if (philo->meal_count < philo->data->max_meals)
			{
				check = false;
				break ;
			}
			else if (philo->meal_count >= philo->data->max_meals)
				check = true;
			current = current->next;
		}
		current = current->next;
	}
	if (check == true)
	{
		mutex(&philo->data->finish, lock);
		philo->data->end = true;
		mutex(&philo->data->finish, unlock);
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philo)
{
	t_philo		*current;
	pthread_t	dead;
	pthread_t	meals;

	current = philo;
	thread(&dead, dead_monitoring, (void *)philo, create);
	if (data->max_meals != -1)
		thread(&meals, meals_monitoring, (void *)philo, create);
	data->start_time = ft_get_time();
	thread(&current->thread_id, philo_routine, (void *)current, create);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, philo_routine, (void *)current, create);
		current = current->next;
	}
	current = philo;
	thread(&current->thread_id, NULL, NULL, join);
	current = current->next;
	while (current != philo)
	{
		thread(&current->thread_id, NULL, NULL, join);
		current = current->next;
	}
}
