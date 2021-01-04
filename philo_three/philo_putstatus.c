/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_putstatus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:18:54 by dnakano           #+#    #+#             */
/*   Updated: 2021/01/04 21:10:08 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <philo_three.h>

static int	get_digit(long num)
{
	int		digit;

	digit = (num < 0) ? 2 : 1;
	while (num >= 10L)
	{
		num /= 10L;
		digit++;
	}
	return (digit);
}

static void	cat_number(char *buf, long num)
{
	int		digit;

	while (*buf)
		buf++;
	digit = get_digit(num);
	buf[digit] = '\0';
	while (digit > 0)
	{
		buf[digit - 1] = (char)(num % 10L) + '0';
		num /= 10;
		digit--;
	}
}

void		philo_putstatus(long philo_index, long time_ms, int philo_status)
{
	char		buf[256];

	buf[0] = '\0';
	cat_number(buf, time_ms);
	ft_strlcat(buf, " ", sizeof(buf));
	cat_number(buf, philo_index + 1);
	if (philo_status == PHILO_S_TAKENFORK)
		ft_strlcat(buf, " has taken a fork\n", sizeof(buf));
	else if (philo_status == PHILO_S_EATING)
		ft_strlcat(buf, " is eating\n", sizeof(buf));
	else if (philo_status == PHILO_S_SLEEPING)
		ft_strlcat(buf, " is sleeping\n", sizeof(buf));
	else if (philo_status == PHILO_S_THINKING)
		ft_strlcat(buf, " is thinking\n", sizeof(buf));
	else if (philo_status == PHILO_S_DEAD)
		ft_strlcat(buf, " died\n", sizeof(buf));
	else
		ft_strlcat(buf, " is in undefined status\n", sizeof(buf));
	sem_wait(g_sem_write);
	write(1, buf, ft_strlen(buf));
	sem_post(g_sem_write);
}
