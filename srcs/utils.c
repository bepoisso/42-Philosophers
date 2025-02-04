/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:41:22 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/04 14:42:20 by bepoisso         ###   ########.fr       */
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

void	free_philo(t_philo **philo)
{
	t_philo	*temp;

	if (!philo || !*philo)
		return ;
	(*philo)->prev->next = NULL;
	while (*philo)
	{
		temp = (*philo)->next;
		free(*philo);
		*philo = temp;
	}
	*philo = NULL;
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
	mutex(&philo->data->write, lock);
	printf("%lld %d  %s\n", (ft_get_time() - philo->data->start_time), philo->id, s);
	mutex(&philo->data->write, unlock);
}
