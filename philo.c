/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkozluca <burakkozluca@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:05:10 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/09 17:01:49 by burakkozluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_data *data, int ac)
{
	(void)ac;
	if (data->n_philo < 1 || data->n_philo > 200 || data->t_die < 0 || \
		data->t_eat < 0 || data->t_sleep < 0)
	{
		printf("Error: Incorrect arguments.\n");
		return (1);
	}
	return (0);
}

t_philo *init_philo(t_data *data)
{
	t_philo *philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n_philo);
	while (i < data->n_philo)
	{
		philo[i].philo_id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		philo[i].last_meal = get_time();
		philo[i].ate = 0;
		philo[i].data_of_philo = data;
		pthread_mutex_init(&data->fork_lock[i], NULL);
		i++;
	}
	i--;
	philo[i].right_fork = 0;
	return (philo);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	if(data->n_philo == 1)
	{
		printf("0 1 is died.\n");
		return (1);
	}
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->must_eat = 0;
	if(argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->is_dead = 0;
	data->sum_meal = 0;
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	pthread_mutex_init(&data->print_lock, NULL);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if(argc == 5 || argc == 6)
	{
		if(!arg_check(argc, argv))
		{
			printf("Error: Incorrect argument.\n");
			return (0);
		}
		if(init_data(&data, argc, argv) == 1)
			return (1);
		if(check_args(&data, argc) == 1)
			return (1);
		philo = init_philo(&data);
		if(start_life(philo) == 1)
		{
			printf("Failed to create thread");
			return (1);
		}
		free_philo(philo, &data);
	}
	else
		printf("Error: Incorrect count of argument.\n");
	return (0);
}
