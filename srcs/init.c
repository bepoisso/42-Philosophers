/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:48 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/24 19:22:37 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philo(t_philo **philo, t_data **data)
{
	
}

static void	init_fork(t_fork **fork, t_data **data)
{
	
}

void	init_all(t_data **data, t_philo **philo, t_fork **fork)
{
	init_philo(philo, data);
	init_fork(fork, data);
}
