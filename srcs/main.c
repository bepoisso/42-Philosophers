/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:38:31 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/24 19:20:17 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int ac, char **av)
{
	t_data	*data;

	data = memset(data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
		// Error nbr args
	parser(&data, ac, av);
	philo(&data);
	return 0;
}
