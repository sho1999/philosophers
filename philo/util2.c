/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:25:49 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/08 09:51:16 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	init_philo2(t_philo *p)
{	
	size_t	i;

	i = 0;
	while (i < p->num_philo)
		pthread_mutex_init(&p->mutex[i++], NULL);
	pthread_mutex_init(&p->writing, NULL);
	p->last_eat_time = (size_t *)malloc(sizeof(size_t) * p->num_philo);
	if (!p->last_eat_time)
		finalize(p, END_ABNORMAL);
	p->ideal_time = (size_t *)malloc(sizeof(size_t) * p->num_philo + 1);
	if (!p->ideal_time)
		finalize(p, END_ABNORMAL);
	p->start_time = (size_t *)malloc(sizeof(size_t) * p->num_philo + 1);
	if (!p->ideal_time)
		finalize(p, END_ABNORMAL);
}

void	init_philo(int argc, char **argv, t_philo *p)
{
	if (p->num_philo > 200)
	{
		free(p);
		philo_error(PHILO_OVER);
	}
	if (argc == 6)
		p->num_must_eat = philo_atoi(argv[5]);
	p->num_philo = philo_atoi(argv[1]);
	p->fork = philo_atoi(argv[1]);
	p->time_die = philo_atoi(argv[2]);
	p->time_eat = philo_atoi(argv[3]);
	p->time_sleep = philo_atoi(argv[4]);
	p->total_num_eat = 0;
	init_philo2(p);
}

void	finalize(t_philo *p, size_t flag)
{
	size_t	i;

	i = 0;
	while (i < p->num_philo)
		pthread_mutex_destroy(&(p->mutex[i++]));
	pthread_mutex_destroy(&(p->writing));
	i = 0;
	free(p->start_time);
	free(p->ideal_time);
	free(p->last_eat_time);
	free(p);
	if (flag == 1)
		exit(1);
	else
		exit(0);
}

static int	ft_isdigit(int c)
{
	return (47 < c && c < 58);
}

int	philo_atoi(char *str)
{
	long	num;
	long	m;

	if (str[0] == '-')
		philo_error(NOTE_NUM);
	if (*str == '+' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\r' || *str == '\f')
		str++;
	m = 0;
	while (ft_isdigit(*str))
	{
		num = (*str++ - '0');
		m = m * 10 + num;
		if (m > INT_MAX)
			philo_error(NOTE_NUM);
	}
	if (*str)
		exit(1);
	return (m);
}
