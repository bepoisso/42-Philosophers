/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:23:58 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 14:57:37 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	mutex_error(int status, t_mutex_code code)
{
	if (status == false)
		return ;
	if (status == EINVAL && (code == lock || code == unlock))
		ft_perror("Error Mutex\nThe value specified by mutex is invalid.\n");
	else if (status == EINVAL && code == init)
		ft_perror("Error Mutex\nThe value specified by attr is invalid.\n");
	else if (status == EDEADLK || status ==  EDEADLOCK)
		ft_perror("Error Mutex\nA deadlock wold occur if the thread blocked waiting for mutex.\n");
	else if (status == EPERM)
		ft_perror ("Error Mutex\nThe current thread dose not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		ft_perror("Error Mutex\nThe process cannot allocate enough memoty to create another mutex.\n");
	else if (status == EBUSY)
		ft_perror("Error Mutex\nMutex is already locked.\n");
}

void	mutex(t_mutex *mutex, t_mutex_code code)
{
	if (code == init)
		mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == lock)
		mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == unlock)
		mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == destroy)
		mutex_error(pthread_mutex_destroy(mutex), code);
	else
		ft_perror("Erorr\nWrong mutex_code\n");
}
