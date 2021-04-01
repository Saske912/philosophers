/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:46:58 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		init_zeros(t_p *doubl)
{
	doubl->next = 0;
	doubl->prev = 0;
	doubl->error = 0;
	if (doubl->curr_phil == doubl->num_phil)
		doubl->eat_status = 1;
	else
		doubl->eat_status = 0;
	doubl->im_dead = 0;
}

t_p			*t_p_init(int ac, char **av, int curr)
{
	t_p					*doubl;
	struct timeval		tv;

	if (!(doubl = (t_p *)malloc(sizeof(*doubl))))
		return (0);
	doubl->num_phil = ft_atoi(av[1]);
	doubl->time_die = ft_atoi(av[2]) * 1000;
	doubl->time_eat = ft_atoi(av[3]) * 1000;
	doubl->time_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		doubl->num_of_eats = ft_atoi(av[5]);
	doubl->curr_phil = curr + 1;
	if ((gettimeofday(&tv, NULL)))
		return (0);
	doubl->start_of_era = start_of_times(tv);
	doubl->last_eat = doubl->start_of_era;
	init_zeros(doubl);
	return (doubl);
}

long long	start_of_times(struct timeval tv)
{
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int			free_memory(char *av_one, t_p *arg, int mode)
{
	int		i;
	t_p		*tmp;

	i = ft_atoi(av_one);
	while (i--)
	{
		tmp = arg->next;
		free(arg);
		arg = tmp;
	}
	if (mode)
		return (-1);
	return (0);
}
