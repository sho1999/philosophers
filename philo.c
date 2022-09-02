/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:06:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/01 22:18:42 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *odd_thread_func(void *p)
{
	t_philo *philo;
	size_t	num_philo;
	size_t	num_eat;

	philo = (t_philo *)p;
	num_philo = philo->num_philo++;
	usleep(cnv_ms(600));
	philo->last_eat_time = timestamp_ms();
	num_eat = 0;
	while (1)
	{
		take_fork(num_philo, philo);
		check_die(num_philo, philo);
		num_eat += eating(num_philo, philo);
		if (num_eat == philo->num_must_eat)
			break ;
		sleeping(num_philo, philo);
		thinking(num_philo, philo);
	}
	return NULL;
}

void *thread_func(void *p)
{
	t_philo *philo;
	size_t	num_philo;
	size_t	num_eat;

	philo = (t_philo *)p;
	num_philo = philo->num_philo++;
	philo->last_eat_time = timestamp_ms();
	num_eat = 0;
	while (1)
	{
		take_fork(num_philo, philo);
		check_die(num_philo, philo);
		num_eat += eating(num_philo, philo);
		if (num_eat == philo->num_must_eat)
			break ;
		sleeping(num_philo, philo);
		thinking(num_philo, philo);
	}
	return NULL;
}

void make_thread(t_philo *philo)
{
	pthread_t th;
	struct timeval tv;
	size_t i;
	size_t	num_philo;

	num_philo = philo->num_philo;
	philo->num_philo = 1;
	i = 1;
	philo->first_time = timestamp_ms();
	while (i <= num_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&th, NULL, odd_thread_func, (void *)philo) != 0) //free処理
				exit(1);
		}
		else
		{
			if (pthread_create(&th, NULL, thread_func, (void *)philo) != 0)
				exit(1);
		}
		i++;
	}
	pthread_join(th, NULL);//join失敗時の処理
}

int main(int argc, char **argv)
{
	t_philo	*p;

	if (!(5 <= argc && argc <= 6))
		exit(1);
	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
		exit(1);
	init_philo(argc, argv, p);
	make_thread(p);
	free(p);
}
