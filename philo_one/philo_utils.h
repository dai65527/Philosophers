/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:23:47 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/22 19:16:37 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	philo_utils.h
**
**	Utility types and functions which are commonly used in philo_one, philo_two
**	and philo_three.
*/

#ifndef PHILO_UTILS_H
# define PHILO_UTILS_H

# include <sys/types.h>

/*
**	Struct to store information of philosophers.
*/

typedef struct	s_philo
{
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		n_to_eat;
}				t_philo;

/*
**	Functions.
*/

int				philo_store_argv(int argc, char **argv, t_philo **philo,
															long *n_philo);
int				philo_puterr_and_return(const char *str, int ret);

/*
**	Functions from libft.
*/

int				ft_isspace(int c);
int				ft_isdigit(int c);

int				ft_atol(const char *str);

size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif
