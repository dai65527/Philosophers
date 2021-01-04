/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 09:01:47 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:05:40 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philo_three.h"

/*
**	Function: philo_init
**
**	Initialize g_fork array and allocate memory for philo_pthread array.
*/

int			philo_init(pid_t **pid, long n_philo)
{
	*pid = (pid_t *)malloc(sizeof(pid_t) * n_philo);
	if (!(*pid))
		return (-1);
	if (philo_sem_open(n_philo) < 0)
		return (-1);
	return (0);
}
