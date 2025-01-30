/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:57 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 13:44:19 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo(t_data *data)
{
	t_philo	*philo;
	t_fork	*fork;

	fork = init_fork(data);
	philo = init_philo(data, fork);
	inti_data(data, philo, fork);
	simulation(data, philo);
	free_philo(&philo);
	free_fork(fork, data->philo_nbr);
}
