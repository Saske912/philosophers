/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:47:01 by pfile             #+#    #+#             */
/*   Updated: 2021/01/28 22:13:07 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>
# define SEM_NAME "/semaphor"

typedef struct			s_philo_two
{
	int					num_phil;
	long long			time_die;
	long long			time_eat;
	long long			time_sleep;
	int					num_of_eats;
	int					eat_status;
	int					curr_phil;
	long long			start_of_era;
	pthread_t			die_check;
	struct s_philo_two	*next;
	struct s_philo_two	*prev;
	long long			last_eat;
	sem_t				*sem;
	int					im_dead;
	int					error;
	pid_t				fo;
}						t_p;

typedef struct			s_int
{
	int					i;
	int					k;
}						t_int;

typedef struct			s_args
{
	int					ac;
	char				**av;
}						t_args;

int						ft_atoi(const char *str);
void					*ft_calloc(size_t count, size_t size);
void					ft_putchar(char c);
void					ft_putstr(char *str);
int						ft_isdigit(int c);
t_p						*t_p_init(int ac, char **av, int curr);
long long				start_of_times(struct timeval tv);
int						isolate(t_p *phil);
int						sleep_and_think(t_p *phil);
int						free_memory(int num, t_p *arg, \
int mode);
int						init_loop(int ac, char **av, t_int z, t_p *arg);
int						eat_time(t_p *phil);
int						init_circle(t_p *tmp, t_p *prev, t_p *arg);
int						init_errors(int ac, char **av);
void					join_it(t_p *arg);
void					*death_check(void *tmp);
int						run_forks(t_p **tmp, sem_t *sem);
int						cycle_of_life(t_p *arg);

#endif
