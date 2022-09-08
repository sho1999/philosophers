/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:17:10 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/08 09:49:31 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	philo_error(char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i])
			write(STDERR, &s[i++], 1);
	exit(1);
}

size_t	timestamp_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

size_t	cnv_ms(size_t ms)
{
	size_t	micro;

	micro = ms * 1000;
	return (micro);
}

void	free_and_exit(t_philo *p)
{
	free(p);
	exit(1);
}

void	*ft_ins(void *p)
{
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *)p;
	while (1)
	{
		usleep(cnv_ms(8));
		i = 0;
		while (i < philo->fork)
			check_die(i++, philo);
	}
}