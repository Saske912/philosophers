/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:42:34 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		eat_time(t_p *phil, struct timeval tv)
{
	if (phil->im_dead)
	{
		pthread_mutex_unlock(&phil->right_fork->mutex);
		pthread_mutex_unlock(&phil->left_fork->mutex);
		return (-1);
	}
	phil->last_eat = start_of_times(tv);
	printf("%lld %d has taken a fork\n", start_of_times(tv) - \
	phil->start_of_era, phil->curr_phil);
	phil->eat_status = 1;
	printf("%lld %d is eating\n", phil->last_eat - \
	phil->start_of_era, phil->curr_phil);
	usleep(phil->time_eat);
	pthread_mutex_unlock(&phil->right_fork->mutex);
	pthread_mutex_unlock(&phil->left_fork->mutex);
	phil->eat_status = 0;
	return (0);
}

int		init_circle(t_p *tmp, t_p *prev, t_p *arg)
{
	prev = tmp;
	tmp = tmp->next;
	tmp->prev = prev;
	tmp->next = arg;
	arg->prev = tmp;
	return (0);
}

void	join_it(t_p *arg)
{
	int		i;
	int		k;
	t_p		*tmp;

	i = arg->curr_phil;
	k = 0;
	tmp = arg;
	pthread_join(tmp->die_check, NULL);
	while (k != i)
	{
		pthread_join(tmp->phil, NULL);
		tmp = tmp->next;
		k = tmp->curr_phil;
	}
}

int		init_errors(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Please enter 4-5 args\n1 - num of phil\n2 - time to die\n\
3 - time to eat\n4 - time to sleep\n\
5 - (optional)num of each phil must eat.\n");
		return (-1);
	}
	else if (ft_atoi(av[1]) == 1)
	{
		ft_putstr("He died stand alone...\n");
		return (-1);
	}
	return (0);
}
