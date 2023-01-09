/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: burakkozluca <burakkozluca@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:36:51 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/09 16:56:13 by burakkozluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int	nbr;
	int	i;
	int	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nbr = (nbr * 10) + (str[i++] - '0');
	return (nbr * sign);
}

int	is_arg_zero(char c)
{
	if (c == '0')
	{
		printf("Arg must be greater than 0");
		return (1);
	}
	return (0);
}

int	arg_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (is_arg_zero(argv[i][j]))
			return (0);
		while (argv[i][j] != '\0')
		{
			if ((argv[i][j] >= '0' && argv[i][j] <= '9'))
				j++;
			else if (j == 0 && argv[i][j] == '+' && argv[i][j + 1] > 32)
				j++;
			else
				return (0);
		}
		j = 0;
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	print(t_philo *philo, char *state)
{
	long	current_time;

	current_time = get_time() - philo->data_of_philo->start_time;
	pthread_mutex_lock(&philo->data_of_philo->print_lock);
	if(!philo->data_of_philo->is_dead)
		printf("%ld %d %s\n", current_time, philo->philo_id, state);
	pthread_mutex_unlock(&philo->data_of_philo->print_lock);
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data_of_philo->must_eat > 0)
	{
		while (i < philo->data_of_philo->n_philo)
		{
			if(philo[i].ate >= philo->data_of_philo->must_eat)
				philo->data_of_philo->sum_meal++;
			i++;
		}
		if (philo->data_of_philo->sum_meal >= philo->data_of_philo->n_philo)
		{
			philo->data_of_philo->is_dead = 1;
			return (1);
		}
	}
	return (0);
}
