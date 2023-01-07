/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkozluca <bkozluca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:54:52 by bkozluca          #+#    #+#             */
/*   Updated: 2023/01/07 15:03:47 by bkozluca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

}
