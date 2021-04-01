/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:46:31 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		isolate(t_p *phil)
{
	struct timeval	tv;

	if (phil->im_dead)
	{
		sem_post(phil->sem);
		return (-1);
	}
	if (gettimeofday(&tv, NULL))
	{
		phil->error = 1;
		return (-1);
	}
	printf("%lld %d has taken a fork\n", start_of_times(tv) - \
	phil->start_of_era, phil->curr_phil);
	sem_wait(phil->sem);
	if (eat_time(phil) == -1)
		return (-1);
	return (0);
}

int		sleep_and_think(t_p *phil)
{
	struct timeval	tv2;
	struct timeval	tv3;
	long long		time2;
	long long		time3;

	if (phil->im_dead)
		return (-1);
	gettimeofday(&tv2, NULL);
	time2 = start_of_times(tv2);
	printf("%lld %d is sleeping\n", time2 - \
	phil->start_of_era, phil->curr_phil);
	usleep(phil->time_sleep);
	if (phil->im_dead)
		return (-1);
	gettimeofday(&tv3, NULL);
	time3 = start_of_times(tv3);
	printf("%lld %d is thinking\n", time3 - \
	phil->start_of_era, phil->curr_phil);
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
