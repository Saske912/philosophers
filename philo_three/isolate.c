/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:46:31 by pfile             #+#    #+#             */
/*   Updated: 2021/01/28 21:41:40 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		isolate(t_p *phil)
{
	struct timeval	tv;

	sem_wait(phil->sem);
	if (gettimeofday(&tv, NULL))
		exit(1);
	printf("%lld %d has taken a fork\n", start_of_times(tv) - \
	phil->start_of_era, phil->curr_phil);
	sem_wait(phil->sem);
	eat_time(phil);
	return (0);
}

int		sleep_and_think(t_p *phil)
{
	struct timeval	tv2;
	struct timeval	tv3;
	long long		time2;
	long long		time3;

	gettimeofday(&tv2, NULL);
	time2 = start_of_times(tv2);
	printf("%lld %d is sleeping\n", time2 - \
	phil->start_of_era, phil->curr_phil);
	usleep(phil->time_sleep);
	gettimeofday(&tv3, NULL);
	time3 = start_of_times(tv3);
	printf("%lld %d is thinking\n", time3 - \
	phil->start_of_era, phil->curr_phil);
	if (phil->curr_phil == phil->num_phil && phil->curr_phil % 2)
		usleep(phil->time_eat / 2);
	return (0);
}

int		init_loop(int ac, char **av, t_int z, t_p *arg)
{
	t_p		*tmp;
	t_p		*prev;

	tmp = arg;
	z.i++;
	while (z.i < z.k)
	{
		if (z.i + 1 == z.k)
		{
			if (!(tmp->next = t_p_init(ac, av, z.i)))
				return (-1);
			init_circle(tmp, prev, arg);
		}
		else
		{
			if (!(tmp->next = t_p_init(ac, av, z.i)))
				return (-1);
			prev = tmp;
			tmp = tmp->next;
			tmp->prev = prev;
		}
		z.i++;
	}
	return (0);
}
