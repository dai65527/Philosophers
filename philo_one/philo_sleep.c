/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:47:00 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 11:58:14 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo_one.h"

int			philo_sleep(t_philo *philo, long time_start_eating)
{
	long	time_start_sleeping;

	if ((time_start_sleeping = philo_gettime()) < 0)
		return (-1);
	philo_putstatus(philo->index, time_start_sleeping, PHILO_S_SLEEPING);
	while (!philo_has_finished(time_start_sleeping, philo->time_to_sleep))
	{
		if (philo_check_dead(philo, time_start_eating))
			return (-1);
		usleep(PHILO_WHILE_INTERVAL_USEC);
	}
	return (0);
}
