/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:09:46 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 14:15:52 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print(char *s, t_philo *philo)
{
	mutex(&philo->data->finish, lock);
	if (philo->data->end)
		return (mutex(&philo->data->finish, unlock));
	mutex(&philo->data->finish, unlock);
	mutex(&philo->data->write, lock);
	printf("%lld %d  %s\n", (ft_get_time() - philo->data->start_time),
		philo->id + 1, s);
	mutex(&philo->data->write, unlock);
}

void	alone(t_data *data)
{
	data->end = true;
	printf("0 1 "GRE"as taken a fork\n");
	usleep(data->time_to_die);
	printf(RES"%lld 1"RED" died\n"RES, data->time_to_die);
}

void	ft_sleep(unsigned long long time)
{
	unsigned long long	now;

	now = ft_get_time();
	while (ft_get_time() - now < time)
	{
		usleep(50);
	}
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
