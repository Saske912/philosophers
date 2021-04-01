/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:32:10 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		eat(t_p *phil)
{
	while (1)
	{
		if (phil->im_dead)
			return (-1);
		if (phil->prev->eat_status && !sem_wait(phil->sem))
		{
			if (isolate(phil) == -1)
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
	if (phil->num_of_eats)
		k = phil->num_of_eats;
	else
		k = 1;
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
	int		k;
	int		i;
	t_p		*tmp;
	sem_t	*sem;

	i = arg->curr_phil;
	k = 0;
	tmp = arg;
	sem_unlink(SEM_NAME);
	if ((sem = sem_open(SEM_NAME, O_CREAT, 0777, tmp->num_phil)) == SEM_FAILED)
		return (-1);
	if (pthread_create(&tmp->die_check, NULL, death_check, (void *)tmp))
		return (-1);
	while (k != i)
		if ((k = run_threads(&tmp, sem)) == -1)
			return (-1);
	join_it(tmp);
	sem_close(sem);
	if (sem_unlink(SEM_NAME) == -1)
		return (-1);
	return (0);
}

int		main(int ac, char **av)
{
	t_p		*arg;
	t_int	z;

	if (init_errors(ac, av) == -1)
		return (-1);
	z.i = 0;
	z.k = ft_atoi(av[1]);
	if (!(arg = t_p_init(ac, av, z.i)))
		return (-1);
	if (init_loop(ac, av, z, arg) == -1)
		return (-1);
	if (create_philosophia(arg) == -1)
		return (free_memory(av[1], arg, 1));
	if (free_memory(av[1], arg, 0) == -1)
		return (-1);
	return (0);
}
