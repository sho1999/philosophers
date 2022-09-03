/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:39:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/02 18:24:28 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t take_fork(size_t num_philo, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %zu has taken a fork\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
	printf("%lld %zu has taken a fork\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
	return (1);
}

long long eating(size_t num_philo, t_philo *philo)
{
	long long  last_time;

	printf("%lld %zu is eating\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
	philo->total_num_eat++;
	if (philo->total_num_eat == philo->num_must_eat * philo->num_philo2)
		free_and_exit(philo);
	last_time = timestamp_ms();
  usleep(cnv_ms(philo->time_eat - 6));
	pthread_mutex_unlock(&philo->mutex);
	return (last_time);
}

void sleeping(size_t num_philo, t_philo *philo)
{
	printf("%lld %zu is sleeping\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
  usleep(cnv_ms(philo->time_sleep - 7));
}

void thinking(size_t num_philo, t_philo *philo)
{
	printf("%lld %zu is thinking\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
}

void check_die(size_t num_philo, t_philo *philo, long long last_time)
{
	if (timestamp_ms() - last_time >= philo->time_die)
	{
		printf("%lld %zu died\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
		free_and_exit(philo);
	}
}
