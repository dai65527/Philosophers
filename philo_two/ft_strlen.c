/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:33:28 by dnakano           #+#    #+#             */
/*   Updated: 2020/12/22 18:28:11 by dnakano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_utils.h"

size_t		ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (*(s++))
		count++;
	return (count);
}
