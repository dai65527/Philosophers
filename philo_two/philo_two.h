/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:05:10 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 11:51:04 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include "philo_utils.h"
# include <semaphore.h>

# define SEM_FORK			"philo_two_fork"
# define SEM_FORK_ACCS		"philo_two_fork_accs"
# define SEM_FLG_GETFORK	"philo_two_flg_getfork"
# define SEM_FLGEND			"philo_two_flgend"
# define SEM_N_FINISHED		"philo_two_n_finished"
# define SEM_WRITE			"philo_two_write"

typedef struct	s_timerinfo
{
	t_philo		*philo;
	long		time_start_eating;
}				t_timerinfo;

sem_t			*g_sem_fork;
sem_t			*g_sem_fork_accs;
sem_t			*g_sem_flg_getfork;
int				g_flg_getfork;
sem_t			*g_sem_flgend;
int				g_flgend;
sem_t			*g_sem_n_finished;
int				g_n_finished;
sem_t			*g_sem_write;

int				philo_init(pthread_t **philo_pthread, long n_philo);
void			philo_sem_unlink(void);
void			philo_sem_close(void);
int				philo_sem_open(long n_philo);
void			*philo_activity(void *philo_arg);
long			philo_eat(t_philo *philo, long time_start_eating);
int				philo_sleep(t_philo *philo, long time_start_eating);
int				philo_check_dead(t_philo *philo, long time_start_eating);
int				philo_free_ret(t_philo *philo, pthread_t *philo_pthread,
																	int ret);

#endif
