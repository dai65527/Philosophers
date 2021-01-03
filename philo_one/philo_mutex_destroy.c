/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:10:53 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 11:12:49 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_one.h"

void		philo_mutex_destroy(void)
{
	pthread_mutex_destroy(&g_mutex_fork);
	pthread_mutex_destroy(&g_mutex_flgend);
	pthread_mutex_destroy(&g_mutex_n_finished);
	pthread_mutex_destroy(&g_mutex_write);
}
