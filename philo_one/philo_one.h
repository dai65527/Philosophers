/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:05:10 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/03 10:36:53 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include "philo_utils.h"

int				*g_fork;
pthread_mutex_t	g_mutex_fork;
int				g_flgend;
pthread_mutex_t	g_mutex_flgend;
int				g_n_finished;
pthread_mutex_t	g_mutex_n_finished;
pthread_mutex_t	g_mutex_write;

int				philo_init(pthread_t **philo_pthread, long n_philo);
void			*philo_activity(void *philo_arg);
int				philo_eat(t_philo *philo);
int				philo_sleep(t_philo *philo);
int				philo_free_ret(t_philo *philo, pthread_t *philo_pthread,
																	int ret);

#endif
