/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:44:51 by pfile             #+#    #+#             */
/*   Updated: 2021/01/29 13:43:01 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	death_loop(long long time, t_p *death)
{
	printf("%lld %d died\n", time - death->start_of_era, \
	death->curr_phil);
	death->im_dead = 1;
	while (!death->next->im_dead)
	{
		death = death->next;
		death->im_dead = 1;
	}
}

void	*death_check(void *tmp)
{
	t_p				*death;
	struct timeval	tv;
	long long		time;

	death = (t_p *)tmp;
	while (death && !death->im_dead)
	{
		if (gettimeofday(&tv, NULL))
		{
			death->error = 1;
			return (NULL);
		}
		time = start_of_times(tv);
		if (time - death->last_eat > death->time_die / 1000)
		{
			death_loop(time, death);
			return (NULL);
		}
		death = death->next;
	}
	return (tmp);
}

int		run_threads(t_p **tmp, sem_t *sem)
{
	(*tmp)->sem = sem;
	if (pthread_create(&(*tmp)->phil, NULL, cycle_of_life, (void *)*tmp))
		return (-1);
	if ((*tmp)->error)
		return (-1);
	*tmp = (*tmp)->next;
	return ((*tmp)->curr_phil);
}
