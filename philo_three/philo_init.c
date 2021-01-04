/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:01:47 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 09:12:52 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo_two.h"

/*
**	Function: philo_init
**
**	Initialize g_fork array and allocate memory for philo_pthread array.
*/

int			philo_init(pthread_t **philo_pthread, long n_philo)
{
	*philo_pthread = (pthread_t *)malloc(sizeof(pthread_t) * n_philo);
	if (!(*philo_pthread))
		return (-1);
	g_flgend = 0;
	g_n_finished = 0;
	if (philo_sem_open(n_philo) < 0)
		return (-1);
	return (0);
}
