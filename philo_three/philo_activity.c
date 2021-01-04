/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 12:50:21 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:08:48 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "philo_three.h"

void		*philo_activity(t_philo *philo)
{
	long	time_start_eating;
	long	time_start_thinking;

	if ((time_start_eating = philo_gettime()) < 0)
		return (NULL);
	while (1)
	{
		if ((time_start_eating = philo_eat(philo, time_start_eating)) < 0)
			return (NULL);
		if (philo_sleep(philo, time_start_eating) < 0)
			kill(0, SIGINT);
		if ((time_start_thinking = philo_gettime()) < 0)
			kill(0, SIGINT);
		philo_putstatus(philo->index, time_start_thinking, PHILO_S_THINKING);
	}
	return (NULL);
}
