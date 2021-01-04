/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 12:50:21 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 23:40:40 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philo_three.h"

void		philo_activity(t_philo *philo)
{
	long	time_start_eating;
	long	time_start_thinking;

	if ((time_start_eating = philo_gettime()) < 0)
		exit(PHILO_EXIT_DIED);
	while (1)
	{
		time_start_eating = philo_eat(philo, time_start_eating);
		philo_sleep(philo, time_start_eating);
		if ((time_start_thinking = philo_gettime()) < 0)
			exit(PHILO_EXIT_DIED);
		philo_putstatus(philo->index, time_start_thinking, PHILO_S_THINKING);
	}
}
