/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:23:10 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/07 21:15:35 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo2(t_philo *p)
{	
	size_t i;
	
	i = 0;
	while (i < p->num_philo)
	{
		p->philo_personal[i].id = i;
		i++;
	}	
	p->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p->num_philo);
	if (!p->mutex)
		exit(1);//free処理
	
	i = 0;
	while (i < p->num_philo)
	{
		pthread_mutex_init(&p->mutex[i], NULL);
		i++;
	}

	// p->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * p->num_philo);
	// if (!p->mutex)
	// 	free_and_exit(p);
	// while (i < p->num_philo)
	// 	pthread_mutex_init(&p->mutex[i++], NULL);
	// pthread_mutex_init(&p->writing, NULL);
	// p->last_eat_time = (long long *)malloc(sizeof(long long) * p->num_philo);
	// if (!p->last_eat_time)
	// 	finalize(p);
	// p->ideal_time = (long long *)malloc(sizeof(long long) * p->num_philo + 1);//free処理
	// if (!p->ideal_time)
	// {
	// 	free(p->last_eat_time);
	// 	finalize(p);
	// }
	// p->first_time = (long long *)malloc(sizeof(long long) * p->num_philo + 1);//free処理
	// if (!p->ideal_time)
	// {
	// 	free(p->ideal_time);
	// 	free(p->last_eat_time);
	// 	finalize(p);
	// }
}

void	init_philo(int argc, char **argv, t_philo *p)
{
	size_t	i;

	if (p->num_philo > 200)
		free_and_exit(p);
	if (argc == 6)
		p->num_must_eat = ft_atoi(argv[5]);
	p->num_philo = ft_atoi(argv[1]);
	p->fork = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	p->total_num_eat = 0;
	init_philo2(p);
}
