/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:44:51 by pfile             #+#    #+#             */
/*   Updated: 2021/01/29 13:41:10 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	death_loop(long long time, t_p **death)
{
	printf("%lld %d died\n", time - (*death)->start_of_era, \
	(*death)->curr_phil);
	free_memory((*death)->num_phil, *death, 1);
	(*death)->im_dead = 1;
	exit(1);
}

void	*death_check(void *tmp)
{
	t_p				*death;
	struct timeval	tv;
	long long		time;

	death = (t_p *)tmp;
	while (1)
	{
		if (death->im_dead)
			return (NULL);
		if (gettimeofday(&tv, NULL))
		{
			death->error = 1;
			return (NULL);
		}
		time = start_of_times(tv);
		if (time - death->last_eat > death->time_die / 1000)
		{
			death_loop(time, &death);
			return (NULL);
		}
		usleep(5555);
	}
}

int		run_forks(t_p **tmp, sem_t *sem)
{
	(*tmp)->sem = sem;
	(*tmp)->fo = fork();
	if ((*tmp)->fo == -1)
		return (-1);
	else if (!(*tmp)->fo)
	{
		if (cycle_of_life(*tmp) == -1)
			return (-1);
	}
	*tmp = (*tmp)->next;
	return ((*tmp)->curr_phil);
}
