/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:41:22 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/25 16:14:43 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	neg;
	int	i;

	neg = 0;
	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	if (neg)
		return (-result);
	return (result);
}

void	ft_perror(char *s)
{
	write(1, s, sizeof(s));
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

void	free_fork(t_fork *fork, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		pthread_mutex_destroy(&fork[i].fork);
	free(fork);
}
