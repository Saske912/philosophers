/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:46:58 by pfile             #+#    #+#             */
/*   Updated: 2021/01/28 22:44:48 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void		wait_other(t_p *arg)
{
	int		stat;
	t_p		*del;

	waitpid(arg->fo, &stat, 0);
	if (stat == 256)
	{
		del = arg;
		while (del->next->curr_phil != arg->curr_phil)
		{
			del = del->next;
			if (del->fo)
				kill(del->fo, SIGKILL);
		}
	}
}

int			free_memory(int num, t_p *arg, int mode)
{
	int		i;
	t_p		*tmp;

	i = num;
	while (i--)
	{
		tmp = arg->next;
		if (!mode)
			wait_other(arg);
		free(arg);
		arg = tmp;
	}
	if (mode)
		return (-1);
	return (0);
}
