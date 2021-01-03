/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free_ret.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 13:20:46 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 15:08:23 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "philo_one.h"

/*
**	Function: philo_free_ret
**
**	Free allocatated memory for philo, philo_thread and g_fork and return value
**	of ret.
*/

int			philo_free_ret(t_philo *philo, pthread_t *philo_pthread, int ret)
{
	free(philo);
	free(philo_pthread);
	free(g_fork);
	free(g_mutex_fork);
	return (ret);
}
