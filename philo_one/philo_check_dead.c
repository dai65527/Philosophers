/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_dead.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:40:03 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 22:33:19 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

int			philo_check_dead(t_philo *philo, long time_start_eating)
{
	long	time_now;

	pthread_mutex_lock(&g_mutex_flgend);
	if (g_flgend)
	{
		pthread_mutex_unlock(&g_mutex_flgend);
		return (1);
	}
	if ((time_now = philo_gettime()) < 0 ||
			time_now - time_start_eating > philo->time_to_die)
	{
		g_flgend = 1;
		pthread_mutex_unlock(&g_mutex_flgend);
		philo_putstatus(philo->index, time_now, PHILO_S_DEAD);
		return (1);
	}
	pthread_mutex_unlock(&g_mutex_flgend);
	return (0);
}
