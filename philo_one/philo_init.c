/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:01:47 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 10:37:16 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo_one.h"

/*
**	Function: philo_init
**
**	Initialize g_fork array and allocate memory for philo_pthread array.
*/

int			philo_init(pthread_t **philo_pthread, long n_philo)
{
	int		i;

	*philo_pthread = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*philo_pthread))
		return (-1);
	g_flgend = 0;
	g_n_finished = 0;
	if (!(g_fork = (int *)malloc(sizeof(int) * n_philo)))
		return (-1);
	i = 0;
	while (i < n_philo)
	{
		g_fork[i] = 0;
		i++;
	}
	if (pthread_mutex_init(&g_mutex_fork, NULL))
		return (philo_free_ret(NULL, NULL, -1));
	if (pthread_mutex_init(&g_mutex_flgend, NULL))
		return (philo_free_ret(NULL, NULL, -1));
	if (pthread_mutex_init(&g_mutex_n_finished, NULL))
		return (philo_free_ret(NULL, NULL, -1));
	if (pthread_mutex_init(&g_mutex_write, NULL))
		return (philo_free_ret(NULL, NULL, -1));
	return (0);
}
