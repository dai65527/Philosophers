/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:01:47 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 11:09:51 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo_one.h"

/*
**	Sub function: mutex_init
*/

static int	mutex_init(void)
{
	if (pthread_mutex_init(&g_mutex_fork, NULL))
		return (-1);
	if (pthread_mutex_init(&g_mutex_flgend, NULL))
	{
		pthread_mutex_destroy(&g_mutex_fork);
		return (-1);
	}
	if (pthread_mutex_init(&g_mutex_n_finished, NULL))
	{
		pthread_mutex_destroy(&g_mutex_fork);
		pthread_mutex_destroy(&g_mutex_flgend);
		return (-1);
	}
	if (pthread_mutex_init(&g_mutex_write, NULL))
	{
		pthread_mutex_destroy(&g_mutex_fork);
		pthread_mutex_destroy(&g_mutex_flgend);
		pthread_mutex_destroy(&g_mutex_n_finished);
		return (-1);
	}
	return (0);
}

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
	if (mutex_init() < 0)
		return (philo_free_ret(NULL, NULL, -1));
	return (0);
}
