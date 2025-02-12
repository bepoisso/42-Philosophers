/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:41:22 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/12 13:23:12 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long	ft_atoll(const char *nptr)
{
	unsigned long long	result;
	int					i;

	result = 0;
	i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result);
}

void	ft_perror(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
	exit (1);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
}

int is_not_correct(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		i++;
	}
	if (ft_atoll(s) > INT_MAX || ft_atoll(s) == 0)
	{
		return (1);
	}
	return (0);
}

void	ft_print(char *s, t_philo *philo)
{
	mutex(&philo->data->finish, lock);
	if (philo->data->end)
		return (mutex(&philo->data->finish, unlock));
	mutex(&philo->data->finish, unlock);
	mutex(&philo->data->write, lock);
	printf("%lld %d  %s\n", (ft_get_time() - philo->data->start_time), philo->id + 1, s);
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
	unsigned long long now;

	now = ft_get_time();
	while (ft_get_time() - now < time)
	{
		usleep(50);
	}
}