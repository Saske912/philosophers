/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 00:47:01 by pfile             #+#    #+#             */
/*   Updated: 2021/03/22 14:23:57 by pfile            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>

typedef struct			s_philo_one
{
	int					num_phil;
	long long			time_die;
	long long			time_eat;
	long long			time_sleep;
	int					num_of_eats;
	int					eat_status;
	int					curr_phil;
	long long			start_of_era;
	long long			last_eat;
	pthread_t			phil;
	pthread_t			die_check;
	struct s_philo_one	*next;
	struct s_philo_one	*prev;
	struct s_mutex		*right_fork;
	struct s_mutex		*left_fork;
	int					im_dead;
	int					error;
}						t_p;

typedef struct			s_mutex
{
	pthread_mutex_t		mutex;
	float				val;
	struct s_mutex		*next;
}						t_mutex;

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
t_mutex					*t_mutex_init(int num, int total);
long long				start_of_times(struct timeval tv);
int						isolate(t_p *phil, pthread_mutex_t *one, \
pthread_mutex_t *two);
int						sleep_and_think(t_p *phil);
int						free_memory(char *av_one, t_mutex *mt, t_p *arg, \
int mode);
int						init_loop(int ac, char **av, t_int z, t_p *arg);
int						mutex_loop(t_mutex *mt, t_p *arg);
int						eat_time(t_p *phil, struct timeval tv);
int						init_circle(t_p *tmp, t_p *prev, t_p *arg);
void					join_it(t_p *tmp);
int						init_errors(int ac, char **av);
void					*death_check(void *tmp);

#endif
