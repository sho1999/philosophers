/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:06:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/08 09:29:50 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*thread_func(void *p)
{
	t_philo		*philo;
	size_t		num_philo;

	philo = (t_philo *)p;
	num_philo = philo->num_philo++;
	philo->last_eat_time[num_philo] = timestamp_ms();
	if (num_philo % 2 == 1)
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

void	make_thread(t_philo *philo)
{
	pthread_t		th;
	pthread_t		inspection;
	size_t			num_philo;

	num_philo = philo->num_philo;
	philo->num_philo = 0;
	while (num_philo-- > 0)
		if (pthread_create(&th, NULL, thread_func, (void *)philo) != 0)
			finalize(philo, END_ABNORMAL);
	if (pthread_create(&inspection, NULL, ft_ins, (void *)philo) != 0)
		finalize(philo, END_ABNORMAL);
	pthread_join(th, NULL);
	pthread_join(inspection, NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*p;

	if (!(5 <= argc && argc <= 6))
		philo_error(USAGE);
	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
		philo_error(MALLOC_ERR);
	init_philo(argc, argv, p);
	make_thread(p);
}
