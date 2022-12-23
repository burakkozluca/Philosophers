/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkozluca <bkozluca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:05:10 by bkozluca          #+#    #+#             */
/*   Updated: 2022/12/23 14:18:03 by bkozluca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;

	if(argc == 5 || argc == 6)
	{
		if(!arg_check(argc, argv))
		{
			printf("Error: Incorrect argument.\n");
			return (0);
		}

	}
}
