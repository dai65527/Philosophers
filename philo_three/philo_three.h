/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:05:10 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:52:27 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "philo_utils.h"
# include <semaphore.h>

# define SEM_FORK			"philo_two_fork"
# define SEM_FORK_ACCS		"philo_two_fork_accs"
# define SEM_FLG_GETFORK	"philo_two_flg_getfork"
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
sem_t			*g_sem_write;

int				philo_init(pid_t **pid, long n_philo);
void			philo_sem_unlink(void);
void			philo_sem_close(void);
int				philo_sem_open(long n_philo);
void			*philo_activity(t_philo *philo);
long			philo_eat(t_philo *philo, long time_start_eating);
int				philo_sleep(t_philo *philo, long time_start_eating);
int				philo_check_dead(t_philo *philo, long time_start_eating);
int				philo_free_ret(t_philo *philo, pid_t *pid, int ret);

#endif
