/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:57 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/24 19:20:57 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo(t_data **data)
{
	t_philo	*philo;
	t_fork	*fork;

	philo = memset(philo, 0, sizeof(t_philo));
	fork = memset(fork, 0, sizeof(t_fork));
	init_all(data, &philo, &fork);
}
