/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:42:34 by pfile             #+#    #+#             */
/*   Updated: 2021/01/28 22:44:30 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eat_time(t_p *phil)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit(1);
	printf("%lld %d has taken a fork\n", start_of_times(tv) - \
	phil->start_of_era, phil->curr_phil);
	printf("%lld %d is eating\n", start_of_times(tv) - \
	phil->start_of_era, phil->curr_phil);
	phil->last_eat = start_of_times(tv);
	usleep(phil->time_eat);
	sem_post(phil->sem);
	sem_post(phil->sem);
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

int		init_errors(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_putstr("Please enter 4-5 args\n1 - num of phil\n\
		2 - time to die\n3 - time to eat\n4 - time to sleep\n\
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
