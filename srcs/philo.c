/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:57 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 13:15:48 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo(t_data *data)
{
	init_data(data);
	data->forks = init_fork(data);
	data->philos = init_philo(data, data->forks);
	if (data->philo_nbr == 1)
		alone(data);
	simulation(data, data->philos);
	clean_fork(data->forks);
	free_philo(&data->philos);
}
