/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:12:14 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 02:30:50 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	
	pthread_mutex_lock(&state->mtx);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[L]]);
	state->forks[philo->forks[L]] = philo->idx;
	printf("%-5d %d has taken a fork\n", get_time(state->start_time), philo->idx);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[R]]);
	state->forks[philo->forks[R]] = philo->idx;
	printf("%-5d %d has taken a fork\n", get_time(state->start_time), philo->idx);
	pthread_mutex_unlock(&state->mtx);
	
	printf("%-5d %d is eating\n", get_time(state->start_time), philo->idx);
	usleep(state->eat * 1000);
	state->forks[philo->forks[L]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[L]]);
	state->forks[philo->forks[R]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[R]]);
}

static void	sleeping(t_philo *philo)
{
	printf("%-5d %d is sleeping\n", get_time(philo->state->start_time), philo->idx);
	usleep(philo->state->sleep * 1000);
}

static void thinking(t_philo *philo)
{
	printf("%-5d %d is thinking\n", get_time(philo->state->start_time), philo->idx);
}

void		*routine(void *arg)
{
	t_philo *philo;
	t_state *state;

	philo = (t_philo*)arg;
	state = philo->state;
	
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
