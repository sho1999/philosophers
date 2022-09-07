/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smuramat <smuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:06:42 by smuramat          #+#    #+#             */
/*   Updated: 2022/09/07 21:11:29 by smuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

// void	*thread_func(void *p)
// {
// 	t_philo		*philo;
// 	size_t		num_philo;

// 	philo = (t_philo *)p;
// 	num_philo = philo->num_philo++;
// 	philo->last_eat_time[num_philo] = timestamp_ms();
// 	if (num_philo % 2 == 1)
// 		usleep(200);
// 	while (1)
// 	{
// 		take_fork(num_philo, philo);
// 		eating(num_philo, philo);
// 		sleeping(num_philo, philo);
// 		thinking(num_philo, philo);
// 	}
// 	return (NULL);
// }

void	*thread_func(void *p)
{
	t_p_philo		*philo_p;

	philo_p = (t_p_philo *)p;
	
	philo_p->last_eat_time = timestamp_ms();
	if (philo_p->id % 2 == 1)
		usleep(200);
	// printf("-%zu ", philo_p->id);//少し順番違うけど大丈夫そ？
	while (1)
	{
		take_fork(philo_p);
		eating(philo_p);
		sleeping(philo_p);
		thinking(philo_p);
	}
	return (NULL);
}

void	make_thread(t_philo *philo)
{
	pthread_t		inspection;
	size_t			i;
	t_p_philo *personal;

	personal = philo->philo_personal;
	// philo->first_time = timestamp_ms();
	i = 0;
	while (i < philo->num_philo)
	{
		if (pthread_create(&personal[i].th, NULL, thread_func, &personal[i]) != 0)
			free_and_exit(philo);
		i++;
		
	}
	// if (pthread_create(&inspection, NULL, ft_ins, (void *)philo) != 0)
	// 	free_and_exit(philo);
	pthread_join(philo->philo_personal[0].th, NULL);
	pthread_join(philo->philo_personal[1].th, NULL);
	pthread_join(philo->philo_personal[2].th, NULL);
	pthread_join(philo->philo_personal[3].th, NULL);
	pthread_join(philo->philo_personal[4].th, NULL);

	// pthread_join(inspection, NULL);
}

// void	make_thread(t_philo *philo)
// {
// 	pthread_t		th;
// 	pthread_t		inspection;
// 	size_t			num_philo;

// 	num_philo = philo->num_philo;
// 	philo->num_philo = 0;
// 	// philo->first_time = timestamp_ms();
// 	while (num_philo-- > 0)
// 		if (pthread_create(&th, NULL, thread_func, (void *)philo) != 0)
// 			free_and_exit(philo);
// 	if (pthread_create(&inspection, NULL, ft_ins, (void *)philo) != 0)
// 		free_and_exit(philo);
// 	pthread_join(th, NULL);
// 	pthread_join(inspection, NULL);
// }

void	finalize(t_philo *p)
{
	size_t i;

	i = 0;
	while (i < p->num_philo)
		pthread_mutex_destroy(&(p->mutex[i++]));
	pthread_mutex_destroy(&(p->writing));
	free(p);
	exit(0);
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
	finalize(p);
}
