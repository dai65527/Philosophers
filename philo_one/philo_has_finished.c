/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_has_finished.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:47 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 11:30:20 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

int			philo_has_finished(long time_start, long time_to_do)
{
	long	time_now;

	if ((time_now = philo_gettime()) < 0)
		return (1);
	if (time_now - time_start >= time_to_do)
		return (1);
	return (0);
}
