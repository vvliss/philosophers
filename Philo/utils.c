/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:56:12 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/18 23:53:36 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;
	long long		ms;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	ms = (long long)tv.tv_sec * 1000LL + (long long)tv.tv_usec / 1000LL;
	return (ms);
}

void	sleep_check(long long duration_ms, t_table *table)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < duration_ms)
	{
		pthread_mutex_lock(&table->sim_mutex);
		if (!table->simulation_running)
		{
			pthread_mutex_unlock(&table->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->sim_mutex);
		usleep(500);
	}
}
