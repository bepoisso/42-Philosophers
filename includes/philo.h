/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:54 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 13:45:07 by bepoisso         ###   ########.fr       */
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
	long long	philo_nbr;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	max_meals;
	long long	start_time;
	bool		end;
	t_fork		*forks;
	t_philo		*philos;
};

// STATE
enum e_state
{
	thinking,
	eating,
	sleeping,
	dead,
};

//	_______________________FUNCTIONS_______________________

// PHILO
void		philo(t_data *data);

// PARSER
void		parser(t_data *data, int ac, char **av);

// UTILES
unsigned long long	ft_atoll(const char *nptr);
void				ft_perror(char *s);
void				free_philo(t_philo **philo);
void				free_fork(t_fork *fork, int nbr);
long long			ft_get_time(void);
int					is_not_correct(char *s);

// MANIPULATION
t_philo				*ft_lstnew(int content, t_data *data, t_fork *fork);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo				*ft_lstlast(t_philo *lst);
int					ft_lstsize(t_philo *lst);

// INTI
t_fork				*init_fork(t_data *data);
t_philo				*init_philo(t_data *data, t_fork *fork);
void				init_data(t_data *data, t_philo *philo, t_fork *fork);

// SIMULATION
void				*philo_routine(void *var);
void				simulation(t_data *data, t_philo *philo);
