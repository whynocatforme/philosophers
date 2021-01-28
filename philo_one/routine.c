/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:12:14 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 06:56:35 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating(t_philo *philo)
{
	t_state *state;

	state = philo->state;
	pthread_mutex_lock(&state->taking_forks);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[L]]);
	put_msg(get_time() - state->start, philo, F);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[R]]);
	put_msg(get_time() - state->start, philo, F);
	pthread_mutex_unlock(&state->taking_forks);
	pthread_mutex_lock(&state->eat_mtx);
	philo->last_meal = get_time();
	philo->eat_times++;
	pthread_mutex_unlock(&state->eat_mtx);
	put_msg(philo->last_meal - state->start, philo, E);
	ft_sleep(state->eat);
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[L]]);
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[R]]);
}

static void	sleeping(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, S);
	ft_sleep(philo->state->sleep);
}

static void	thinking(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, T);
}

void		*routine(void *arg)
{
	t_philo		*philo;
	t_state		*state;
	pthread_t	chk;

	philo = (t_philo*)arg;
	if (philo->idx % 2)
		ft_sleep(philo->state->die / 3);
	state = philo->state;
	philo->last_meal = get_time();
	pthread_mutex_lock(&state->dead_mtx);
	while (!state->dead)
	{
		pthread_mutex_unlock(&state->dead_mtx);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&state->dead_mtx);
	}
	pthread_mutex_unlock(&state->dead_mtx);
	return (NULL);
}
