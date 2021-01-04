/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 12:50:21 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 09:39:25 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "philo_two.h"

void		*philo_activity(void *philo_arg)
{
	t_philo	*philo;
	long	time_start_eating;
	long	time_start_thinking;

	philo = (t_philo *)philo_arg;
	if ((time_start_eating = philo_gettime()) < 0)
		return (NULL);
	while (1)
	{
		if ((time_start_eating = philo_eat(philo, time_start_eating)) < 0)
			return (NULL);
		if (philo_sleep(philo, time_start_eating) < 0)
			return (NULL);
		if ((time_start_thinking = philo_gettime()) < 0)
			return (NULL);
		philo_putstatus(philo->index, time_start_thinking, PHILO_S_THINKING);
	}
	return (NULL);
}
