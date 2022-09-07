/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:39:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/07 21:16:24 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_p_philo *p)
{
	printf("%zu\n", p->id);fflush(stdout);
	
	pthread_mutex_lock(&p->pub->mutex[p->id]);
	printf("%lld %zu %s", timestamp_ms(), p->id, P_FORK);
	if (p->id == p->pub->num_philo - 1)
		pthread_mutex_lock(&p->pub->mutex[0]);
	else
		pthread_mutex_lock(&p->pub->mutex[p->id + 1]);
	printf("%lld %zu %s", timestamp_ms(), p->id, P_FORK);
}

void	eating(t_p_philo *p)
{
	p->first_time = timestamp_ms();
	printf("%lld %zu %s", timestamp_ms(), p->id, P_EAT);
	p->last_eat_time = timestamp_ms();
	pthread_mutex_lock(&p->pub->writing);
	p->pub->total_num_eat++;
	if (p->pub->total_num_eat == p->pub->num_must_eat * p->pub->num_philo)
		finalize(p->pub);
	pthread_mutex_unlock(&p->pub->writing);
  usleep(cnv_ms(p->pub->time_eat));
	pthread_mutex_unlock(&p->pub->mutex[p->id]);
	if (p->id == p->pub->num_philo - 1)
		pthread_mutex_unlock(&p->pub->mutex[0]);
	else
		pthread_mutex_unlock(&p->pub->mutex[p->id + 1]);
}

void	sleeping(t_p_philo *p)
{
	p->ideal_time = timestamp_ms() - (p->first_time + p->pub->time_eat);
	pthread_mutex_lock(&p->pub->writing);
	printf("%lld %zu %s", timestamp_ms() - p->ideal_time, p->id, P_SLEEP);
	pthread_mutex_unlock(&p->pub->writing);
	usleep(cnv_ms(p->pub->time_sleep));
}

void	thinking(t_p_philo *p)
{
	p->ideal_time = timestamp_ms() - (p->first_time + p->pub->time_eat + p->pub->time_sleep);
	pthread_mutex_lock(&p->pub->writing);
	printf("%lld %zu %s", timestamp_ms() - p->ideal_time, p->id, P_THINK);
	pthread_mutex_unlock(&p->pub->writing);
}

void	check_die(t_p_philo *p)
{
	pthread_mutex_lock(&p->pub->writing);
	if (timestamp_ms() - p->last_eat_time > p->pub->time_die + p->ideal_time)
	{
		printf("%lld %zu %s", timestamp_ms(), p->id, P_DEAD);
		free_and_exit(p->pub);
	}
	pthread_mutex_unlock(&p->pub->writing);
}
