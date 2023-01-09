/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkozluca <burakkozluca@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:05:07 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/09 16:56:27 by burakkozluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				sum_meal;
	long			start_time;
	int				is_dead;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork_lock;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	long		last_meal;
	int			ate;
	int			philo_id;
	int			left_fork;
	int			right_fork;
	t_data		*data_of_philo;
}	t_philo;

//ARG
int		ft_atoi(char *str);
int		is_arg_zero(char c);
int		arg_check(int argc, char **argv);
void	print(t_philo *philo, char *state);
long	get_time(void);
int		check_meals(t_philo *philo);

//PHILO
int		init_data(t_data *data, int argc, char **argv);
t_philo	*init_philo(t_data *data);

//LOOP
int		start_life(t_philo *philo);
void	eat_func(t_philo *philo);
void	*loop(void *ptr);
void	*check_life(void *ptr);
void	free_philo(t_philo *philo, t_data *data);

#endif
