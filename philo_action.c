/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:39:04 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/01 22:16:34 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_fork(size_t num_philo, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	printf("%lld %zu has taken a fork\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
	printf("%lld %zu has taken a fork\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
}

int eating(size_t num_philo, t_philo *philo)
{
	printf("%lld %zu is eating\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
	philo->last_eat_time = timestamp_ms();
	usleep(300);
  usleep(cnv_ms(philo->time_eat - 6));
	pthread_mutex_unlock(&philo->mutex);
	return (1);
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

void check_die(size_t num_philo, t_philo *philo)
{
	if (timestamp_ms() - philo->last_eat_time >= philo->time_die)
	{
		printf("%lld %zu died\n", timestamp_ms() - philo->first_time, num_philo);fflush(stdout);
		exit(0);//philoのfree処理
	}
}
