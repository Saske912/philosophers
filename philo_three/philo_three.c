/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:32:10 by pfile             #+#    #+#             */
/*   Updated: 2021/01/29 13:41:08 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eat(t_p *phil)
{
	while (1)
	{
		if (phil->curr_phil % 2)
		{
			if (isolate(phil) == -1)
				return (-1);
			break ;
		}
		else
		{
			usleep(200);
			if (isolate(phil) == -1)
				return (-1);
			break ;
		}
	}
	if (sleep_and_think(phil) == -1)
		return (-1);
	return (0);
}

int		cycle_of_life(t_p *phil)
{
	int	k;
	int	n;

	if (pthread_create(&phil->die_check, NULL, death_check, (void *)phil))
		return (-1);
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
			exit(1);
	}
	phil->im_dead = 1;
	pthread_join(phil->die_check, NULL);
	exit(0);
	return (0);
}

int		engine(t_p *tmp, sem_t *sem)
{
	tmp->sem = sem;
	tmp->fo = fork();
	if (tmp->fo == -1)
		return (-1);
	else if (!tmp->fo)
		cycle_of_life(tmp);
	return (0);
}

int		create_philosophia(t_p *arg)
{
	int		k;
	t_p		*tmp;
	sem_t	*sem;

	k = 0;
	tmp = arg;
	sem_unlink(SEM_NAME);
	if ((sem = sem_open(SEM_NAME, O_CREAT, 0777, tmp->num_phil)) == SEM_FAILED)
		return (-1);
	while (k < tmp->num_phil)
	{
		engine(tmp, sem);
		k++;
		tmp = tmp->next;
	}
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
		return (free_memory(arg->num_phil, arg, 1));
	if (free_memory(arg->num_phil, arg, 0) == -1)
		return (-1);
	return (0);
}
