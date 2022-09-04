/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:06:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/04 18:17:02 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philo *p, size_t num_p)
{
	printf("%lld %zu %s", timestamp_ms() - p->first_time, num_p, P_DEAD);
	free_and_exit(p);
}

void	*thread_func(void *p)
{
	t_philo		*philo;
	size_t		num_philo;
	long long	first_time;

	philo = (t_philo *)p;
	num_philo = philo->num_philo++;
	if (philo->fork == 1)
		one_philo(philo, num_philo);
	if (num_philo % 2 == 0)
		usleep(200);
	while (1)
	{
		take_fork(num_philo, philo);
		eating(num_philo, philo);
		sleeping(num_philo, philo);
		thinking(num_philo, philo);
	}
	return (NULL);
}

void *ft_ins(void *p)
{
	t_philo *philo;
	size_t	i;

	philo = (t_philo *)p;
	while (1)
	{
		i = 0;
		while (i < philo->fork)
		{
			/* code */
		}
		
		usleep(cnv_ms(5));
	}
	
}

void	make_thread(t_philo *philo)
{
	pthread_t		th;
	pthread_t		inspection;
	struct timeval	tv;
	size_t			num_philo;

	num_philo = philo->num_philo;
	philo->num_philo = 0;
	philo->first_time = timestamp_ms();
	while (num_philo-- > 0)
	{
		if (pthread_create(&th, NULL, thread_func, (void *)philo) != 0)
			free_and_exit(philo);
	}
	if (pthread_create(&inspection, NULL, ft_ins, (void *)philo) != 0)
		free_and_exit(philo);
	pthread_join(th, NULL);
	pthread_join(inspection, NULL);
}

void	finalize(t_philo *p)
{
	size_t i;

	i = 0;
	while (i < p->num_philo)
		pthread_mutex_destroy(&(p->mutex[i++]));
	pthread_mutex_destroy(&(p->writing));
	free(p);
}


int	main(int argc, char **argv)
{
	t_philo	*p;

	if (!(5 <= argc && argc <= 6))
		exit(1);
	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
		exit(1);
	init_philo(argc, argv, p);
	make_thread(p);
	finalize(p);
}
