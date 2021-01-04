/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check_dead.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:40:03 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 23:42:07 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_three.h"

void		philo_check_dead(t_philo *philo, long time_start_eating)
{
	long	time_now;

	if (time_start_eating && ((time_now = philo_gettime()) < 0 ||
							time_now - time_start_eating >= philo->time_to_die))
	{
		philo_putstatus(philo->index, time_now, PHILO_S_DEAD);
		exit(PHILO_EXIT_DIED);
	}
}
