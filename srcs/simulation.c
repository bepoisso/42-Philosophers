/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:33:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/28 14:04:45 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_routine(t_philo *philo)
{
	philo_think(philo);
	philo_eat(philo);
	philo_sleep(philo);
	philo_dead(philo);
	
}

void	simulation(t_data *data, t_philo *philo, t_fork *fork)
{	
	data->start_time = ft_get_time();
	pthread_create(&philo->thread_id, NULL, philo_routine, philo)
}
