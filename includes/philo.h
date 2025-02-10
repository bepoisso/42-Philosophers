/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:56:54 by bepoisso          #+#    #+#             */
/*   Updated: 2025/02/10 12:58:58 by bepoisso         ###   ########.fr       */
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
#include <errno.h>

# define RED "\x1b[31m"
# define GRE "\x1b[32m"
# define YEL "\x1b[33m"
# define BLU "\x1b[34m"
# define MAG "\x1b[35m"
# define RES "\x1b[0m" 

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
	t_mutex				meals;
	bool				full;
	long				last_meal_time;
	bool				even;
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
	int			nbr_meals;
	long long	start_time;
	bool		end;
	t_mutex		write;
	t_mutex		meals;
	t_mutex		finish;
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

// mutex_CODE
typedef	enum e_mutex_code
{
	init,
	destroy,
	lock,
	unlock,
}	t_mutex_code;

// THREAD CODE
typedef enum e_thread_code
{
	create,
	join,
	detach,
}	t_thread_code;

//	_______________________FUNCTIONS_______________________

// PHILO
void		philo(t_data *data);

// PARSER
void		parser(t_data *data, int ac, char **av);

// UTILES
unsigned long long	ft_atoll(const char *nptr);
void				ft_perror(char *s);
long long			ft_get_time(void);
int					is_not_correct(char *s);
void				ft_print(char *s, t_philo *philo);
void				ft_sleep(unsigned long long time);
int					is_ended(t_data *data);

// MANIPULATION
t_philo				*ft_lstnew(int content, t_data *data, t_fork *fork);
void				ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo				*ft_lstlast(t_philo *lst);
int					ft_lstsize(t_philo *lst);

// INTI
t_fork				*init_fork(t_data *data);
t_philo				*init_philo(t_data *data, t_fork *fork);
void				init_data(t_data *data);

// SIMULATION
void				*philo_routine(void *var);
void				simulation(t_data *data, t_philo *philo);

// MUTEX & THREAD HANDLE
void				mutex(t_mutex *mutex, t_mutex_code code);
void				thread(pthread_t *thread, void *(*func)(void *), void *data, t_thread_code code);

// CLEAN
void				clean_fork(t_fork *fork);
void				free_philo(t_philo **philo);
