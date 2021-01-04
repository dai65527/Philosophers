/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_gettime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:12:50 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 12:04:29 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

long		philo_gettime(void)
{
	long			time_ms;
	struct timeval	time_tv;

	if (gettimeofday(&time_tv, NULL))
		return (-1);
	time_ms = time_tv.tv_sec * 1000;
	time_ms += time_tv.tv_usec / 1000;
	return (time_ms);
}
