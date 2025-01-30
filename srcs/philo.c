/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:57 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 14:54:32 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo(t_data *data)
{
	init_data(data);
	data->forks = init_fork(data);
	data->philos = init_philo(data, data->forks);
	simulation(data, data->philos);
	// free_philo(&data->philos);
	// clean_fork(fork);
}
