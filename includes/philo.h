/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:54 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/23 19:14:03 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// _______________________INCLUDES_______________________
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

// _______________________STRUCT_______________________
typedef int	t_state;

typedef struct s_philo
{
	int		index;
	int		fork_index;
	t_state	state;
	s_philo	*next;
	s_philo	*prev;
}	t_philo;

enum e_state
{
	eat,
	sleep,
	think,
};

//	_______________________FUNCTIONS_______________________
