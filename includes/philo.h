/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:54 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/24 19:10:48 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// _______________________INCLUDES_______________________
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>

// _______________________STRUCT & VARIABLE_______________________

// TYPEDEF
typedef int	t_state;
typedef pthread_mutex_t	t_mutex;
typedef struct s_data	t_data;

// FORK
typedef struct s_fork
{
	int		id;
	t_mutex	fork;
}	t_fork;

// PHILO
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	t_state				state;
	int					meal_count;
	bool				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	struct s_philo		*next;
	struct s_philo		*prev;
	t_data				*data;
}	t_philo;

// DATA
struct s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meals;
	long	start_time;
	bool	end;
	t_fork	*forks;
	t_philo	*philos;
};

// STATE
enum e_state
{
	dead,
	eat,
	is_sleep,
	think,
};

//	_______________________FUNCTIONS_______________________

// PARSER
void	parser(t_data **data, int ac, char **av);

// UTILES
int		ft_atoi(const char *nptr);
void	ft_perror(char *s);
