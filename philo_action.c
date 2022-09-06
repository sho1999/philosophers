/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:39:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/06 22:13:55 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(size_t num_p, t_philo *p)
{
	pthread_mutex_lock(&p->mutex[num_p]);
	printf("%lld %zu %s", timestamp_ms(), num_p, P_FORK);
	if (num_p == p->fork - 1)
		pthread_mutex_lock(&p->mutex[0]);
	else
		pthread_mutex_lock(&p->mutex[num_p + 1]);
	printf("%lld %zu %s", timestamp_ms(), num_p, P_FORK);
}

void	eating(size_t num_p, t_philo *p)
{
	p->first_time[num_p] = timestamp_ms();
	printf("%lld %zu %s", timestamp_ms(), num_p, P_EAT);
	p->last_eat_time[num_p] = timestamp_ms();
	pthread_mutex_lock(&p->writing);
	p->total_num_eat++;
	if (p->total_num_eat == p->num_must_eat * p->fork)
	{
		free(p->first_time);
		free(p->ideal_time);
		free(p->last_eat_time);
		finalize(p);
	}
	pthread_mutex_unlock(&p->writing);
  usleep(cnv_ms(p->time_eat));
	pthread_mutex_unlock(&p->mutex[num_p]);
	if (num_p == p->fork - 1)
		pthread_mutex_unlock(&p->mutex[0]);
	else
		pthread_mutex_unlock(&p->mutex[num_p + 1]);
}

void	sleeping(size_t num_p, t_philo *p)
{
	p->ideal_time[num_p] = timestamp_ms() - (p->first_time[num_p] + p->time_eat);
	pthread_mutex_lock(&p->writing);
	printf("%lld %zu %s", timestamp_ms() - p->ideal_time[num_p], num_p, P_SLEEP);
	pthread_mutex_unlock(&p->writing);
	usleep(cnv_ms(p->time_sleep));
}

void	thinking(size_t num_p, t_philo *p)
{
	p->ideal_time[num_p] = timestamp_ms() - (p->first_time[num_p] + p->time_eat + p->time_sleep);
	pthread_mutex_lock(&p->writing);
	printf("%lld %zu %s", timestamp_ms() - p->ideal_time[num_p], num_p, P_THINK);
	pthread_mutex_unlock(&p->writing);

}

void	check_die(size_t num_p, t_philo *p)
{
	pthread_mutex_lock(&p->writing);
	if (timestamp_ms() - p->last_eat_time[num_p] > p->time_die + p->ideal_time[num_p])
	{
		printf("%lld %zu %s", timestamp_ms(), num_p, P_DEAD);
		free(p->first_time);
		free(p->ideal_time);
		free(p->last_eat_time);
		free_and_exit(p);
		//何処かleakしてる
	}
	pthread_mutex_unlock(&p->writing);
}
