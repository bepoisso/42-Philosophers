/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepoisso <bepoisso@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:25:19 by bepoisso          #+#    #+#             */
/*   Updated: 2025/01/30 14:58:40 by bepoisso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	thread_error(int status, t_thread_code code)
{
	if (status == false)
		return ;
	if (status == EAGAIN)
		ft_perror("Error Thread\nNo recources to create another thread.\n");
	else if (status == EPERM)
		ft_perror ("Error Thread\nThe caller does not have apropriate permission.\n");
	else if (status == EINVAL && (code == join || code == detach))
		ft_perror("Error Thread\nThe value specified by thread is invalid.\n");
	else if (status == EINVAL && code == create)
		ft_perror("Error Thread\nThe value specified by attr is invalid.\n");
	else if (status == EDEADLK || status ==  EDEADLOCK)
		ft_perror("Error Thread\nA deadlock was detected or the value of thread specifies the calling thread.\n");
	else if (status == ESRCH)
		ft_perror("Error Thread\nNo thread could be found corresponding to that specified by the given tread ID, thread.\n");
}

void	thread(pthread_t *thread, void *(*func)(void *), void *data, t_thread_code code)
{
	if (code == create)
		thread_error(pthread_create(thread, NULL, func, data), code);
	else if (code == join)
		thread_error(pthread_join(*thread, NULL), code);
	else if (code == detach)
		thread_error(pthread_detach(*thread), code);
	else
		ft_perror("Erorr Thread\nWrong thread_code\n");
}
