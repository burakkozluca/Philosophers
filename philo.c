/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkozluca <bkozluca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:05:10 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/07 14:08:36 by bkozluca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if(arg_check(&data, argc) == 1)
			return (1);

	}
}
