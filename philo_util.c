/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:17:10 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/03 21:11:45 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ps_error(void)
{
	ft_putstr_fd("Error\n", STDERR);
	return (1);
}

long long	timestamp_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

size_t	cnv_ms(size_t ms)
{
	size_t	micro;

	micro = ms * 1000;
	micro += 600;
	return (micro);
}

void	free_and_exit(t_philo *p)
{
	free(p);
	exit(0);
}
