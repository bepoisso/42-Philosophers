/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:41:20 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 16:10:50 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// ./philo 5 800 200 200 [5]
// ./philo nbr_philo time_to_die time_to_eat time_to_sleep [max_meals]
void	parser(t_data *data, int ac, char **av)
{
	if (is_not_correct(av[1]))
		ft_perror("Error\nNbr of philosophers is not correct\n");
	data->philo_nbr = ft_atoll(av[1]);
	if (is_not_correct(av[2]))
		ft_perror("Error\nTime_to_die is not correct\n");
	data->time_to_die = ft_atoll(av[2]);
	if (is_not_correct(av[3]))
		ft_perror("Error\nTime_to_eat is not correct\n");
	data->time_to_eat = ft_atoll(av[3]);
	if (is_not_correct(av[4]))
		ft_perror("Error\nTime_to_sleep is not correct\n");
	data->time_to_sleep = ft_atoll(av[4]);
	if (data->time_to_die < 60
		|| data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		ft_perror("Error\nPlease use timestamp major than 60ms\n");
	if (ac == 6)
	{
		if (is_not_correct(av[5]))
			ft_perror("Error\nMax_meals is not correct\n");
		data->max_meals = ft_atoll(av[5]);
	}
	else
		data->max_meals = -1;
}
