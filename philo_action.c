/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:39:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/04 15:47:42 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(size_t num_p, t_philo *p)
{
	pthread_mutex_lock(&p->mutex[num_p]);
	printf("%lld %zu %s", timestamp_ms() - p->first_time, num_p, P_FORK);
	if (num_p == p->fork)
		pthread_mutex_lock(&p->mutex[0]);
	else
		pthread_mutex_lock(&p->mutex[num_p + 1]);
	printf("%lld %zu %s", timestamp_ms() - p->first_time, num_p, P_FORK);
}

long long	eating(size_t num_p, t_philo *p)
{
	long long	last_time;

	printf("%lld %zu %s", timestamp_ms() - p->first_time, num_p, P_EAT);
	last_time = timestamp_ms();
	pthread_mutex_lock(&p->writing);
	p->total_num_eat++;
	pthread_mutex_unlock(&p->writing);
	if (p->total_num_eat == p->num_must_eat * p->num_philo2)
		free_and_exit(p);
  usleep(cnv_ms(p->time_eat) - 3);
	pthread_mutex_unlock(&p->mutex[num_p]);
	if (num_p == p->fork)
		pthread_mutex_unlock(&p->mutex[0]);
	else
		pthread_mutex_unlock(&p->mutex[num_p + 1]);
	return (last_time);
}

void	sleeping(size_t num_p, t_philo *p)
{
	usleep(100);
	printf("%lld %zu %s", timestamp_ms() - p->first_time - 6, num_p, P_SLEEP);
	usleep(cnv_ms(p->time_sleep));
}

void	thinking(size_t num_p, t_philo *p)
{
	printf("%lld %zu %s", timestamp_ms() - p->first_time - 11, num_p, P_THINK);
}

int	check_die(size_t num_p, t_philo *p, long long last_t)
{
	if (timestamp_ms() - last_t >= p->time_die || timestamp_ms() - p->first_time >p->time_die)
	{
		pthread_mutex_lock(&p->writing);
		printf("%lld %zu %s", timestamp_ms() - p->first_time, num_p, P_DEAD);
		free_and_exit(p);
		pthread_mutex_unlock(&p->writing);
	}
	return (1);
}
