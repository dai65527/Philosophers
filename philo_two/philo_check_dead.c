/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_dead.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:40:03 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 11:00:59 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include "philo_two.h"

int			philo_check_dead(t_philo *philo, long time_start_eating)
{
	long	time_now;

	sem_wait(g_sem_flgend);
	if (g_flgend)
	{
		sem_post(g_sem_flgend);
		return (1);
	}
	if (time_start_eating && ((time_now = philo_gettime()) < 0 ||
							time_now - time_start_eating >= philo->time_to_die))
	{
		g_flgend = 1;
		philo_putstatus(philo->index, time_now, PHILO_S_DEAD);
		sem_post(g_sem_flgend);
		return (1);
	}
	sem_post(g_sem_flgend);
	return (0);
}
