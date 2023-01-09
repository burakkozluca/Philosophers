/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkozluca <burakkozluca@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:54:52 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/09 16:30:43 by burakkozluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->fork_lock);
	free(philo);
}

void	*loop(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if(philo->philo_id % 2 == 0)
	{
		printf(philo, "is thinking");
		usleep(1600); //1600 olma sebebi
	}
	while (philo->data_of_philo->is_dead != 1)
	{
		eat_func(philo);
		print(philo, "is sleeping");
		usleep(philo->data_of_philo->t_sleep * 1000);
		print(philo, "is thinking");
		philo->ate++;
	}
	return (NULL);
}

void	eat_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->left_fork]);
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->right_fork]);
	print(philo, "has taken fork");
	print(philo, "has taken fork");
	print(philo, "is eating");
	usleep(philo->data_of_philo->t_eat * 1000);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->right_fork]);
}

void	*check_life(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	while (!check_meals(philo))
	{
		i = 0;
		while (i < philo->data_of_philo->n_philo)
		{
			if (get_time() - philo[i].last_meal > philo->data_of_philo->t_die)
			{
				print(&philo[i], "died");
				philo->data_of_philo->is_dead = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_life(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	philo->data_of_philo->start_time = get_time();
	while (++i < philo->data_of_philo->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &loop, &philo[i]) != 0)
			return (1);
	}
	pthread_create(&monitor, NULL, &check_life, philo);
	i = -1;
	while(++i < philo->data_of_philo->n_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (1);
	}
	pthread_join(monitor, NULL);
	return (0);
}
