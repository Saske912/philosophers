/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:32:10 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		eat(t_p *phil)
{
	if (phil->im_dead)
		return (-1);
	while (1)
	{
		if ((phil->curr_phil % 2) && !phil->prev->eat_status && \
		!pthread_mutex_lock(&phil->right_fork->mutex))
		{
			if (isolate(phil, &phil->right_fork->mutex, \
			&phil->left_fork->mutex) == -1)
				return (-1);
			break ;
		}
		else if (!(phil->curr_phil % 2) && !phil->next->eat_status && \
		!pthread_mutex_lock(&phil->left_fork->mutex))
		{
			if (isolate(phil, &phil->left_fork->mutex, \
			&phil->right_fork->mutex) == -1)
				return (-1);
			break ;
		}
	}
	if (sleep_and_think(phil) == -1)
		return (-1);
	return (0);
}

void	*cycle_of_life(void *arg)
{
	t_p	*phil;
	int	k;
	int	n;

	phil = (t_p*)arg;
	k = 1;
	if (phil->num_of_eats)
		k = phil->num_of_eats;
	while (k)
	{
		if (phil->num_of_eats)
			k--;
		n = eat(phil);
		if (n == -1)
			return (arg);
	}
	phil->im_dead = 1;
	return (arg);
}

int		create_philosophia(t_p *arg)
{
	int	k;
	int	i;
	t_p	*tmp;

	i = arg->curr_phil;
	k = 0;
	tmp = arg;
	if (pthread_create(&tmp->die_check, NULL, death_check, (void *)tmp))
		return (-1);
	while (k != i)
	{
		if (pthread_create(&tmp->phil, NULL, cycle_of_life, (void *)tmp))
			return (-1);
		if (tmp->error)
			return (-1);
		tmp = tmp->next;
		k = tmp->curr_phil;
	}
	join_it(arg);
	return (0);
}

int		main(int ac, char **av)
{
	t_p		*arg;
	t_mutex	*mt;
	t_int	z;

	if (init_errors(ac, av) == -1)
		return (-1);
	z.i = 0;
	z.k = ft_atoi(av[1]);
	if (!(arg = t_p_init(ac, av, z.i)))
		return (-1);
	if (init_loop(ac, av, z, arg) == -1)
		return (-1);
	if (!(mt = t_mutex_init(arg->curr_phil, arg->num_phil)))
		return (-1);
	if (mutex_loop(mt, arg) == -1)
		return (-1);
	if (create_philosophia(arg) == -1)
		return (free_memory(av[1], mt, arg, 1));
	if (free_memory(av[1], mt, arg, 0) == -1)
		return (-1);
	return (0);
}
