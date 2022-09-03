/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:06:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/03 19:28:15 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_func(void *p)
{
	t_philo		*philo;
	size_t		num_philo;
	long long	last_time;

	philo = (t_philo *)p;
	num_philo = philo->num_philo++;
	philo->first_time[num_philo] = timestamp_ms();
	if (num_philo % 2 == 0)
		usleep(200);
	last_time = timestamp_ms();
	while (check_die(num_philo, philo, last_time))
	{
		take_fork(num_philo, philo);
		last_time = eating(num_philo, philo);
		sleeping(num_philo, philo);
		thinking(num_philo, philo);
	}
	return (NULL);
}

void	make_thread(t_philo *philo)
{
	pthread_t		th;
	struct timeval	tv;
	size_t			num_philo;

	num_philo = philo->num_philo;
	philo->num_philo = 1;
	while (num_philo-- > 0)
		if (pthread_create(&th, NULL, thread_func, (void *)philo) != 0)
			free_and_exit(philo);
	pthread_join(th, NULL);
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
	free(p);
}
