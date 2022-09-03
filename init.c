/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:23:10 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/03 20:58:53 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(int argc, char **argv, t_philo *p)
{
	size_t	i;

	i = 1;
	p->num_philo = ft_atoi(argv[1]);
	if (p->num_philo > 9)
		free_and_exit(p);
	p->num_philo2 = ft_atoi(argv[1]);
	p->fork = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->num_must_eat = ft_atoi(argv[5]);
	while (i <= p->num_philo)
		pthread_mutex_init(&p->mutex[i++], NULL);
	p->total_num_eat = 0;
}
