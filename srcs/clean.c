/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:50:18 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 14:49:47 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_fork(t_fork *fork)
{
	int	i;

	i = 0;
	while (fork[i].id != -1)
	{
		mutex(&fork[i].fork, destroy);
		i++;
	}
	free(fork);
}
