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
	
	//pthread_mutex_lock(&state->mtx);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[L]]);
	//state->forks[philo->forks[L]] = philo->idx;
	put_msg(get_time() - state->start, philo, F);
	pthread_mutex_lock(&state->forks_mtx[philo->forks[R]]);
	//state->forks[philo->forks[R]] = philo->idx;
	put_msg(get_time() - state->start, philo, F);
	//pthread_mutex_unlock(&state->mtx);
	
	philo->last_meal = get_time();
	put_msg(philo->last_meal - state->start, philo, E);
	ft_sleep(state->eat);
	//state->forks[philo->forks[L]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[L]]);
	//state->forks[philo->forks[R]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[R]]);
}

static void	sleeping(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, S);
	ft_sleep(philo->state->sleep);
}

static void thinking(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, T);
}

void		*routine(void *arg)
{
	t_philo *philo;
	t_state *state;
	pthread_t chk;

	philo = (t_philo*)arg;
	if (philo->idx % 2)
		ft_sleep(100);
	state = philo->state;
	philo->last_meal = get_time();
	pthread_mutex_lock(&state->dead_mtx);
	while (!state->dead)
	{
		pthread_mutex_unlock(&state->dead_mtx);
		/*pthread_mutex_lock(&state->mtx);
		if (state->forks[philo->forks[L]] != -1 || state->forks[philo->forks[R]] != -1) {
			pthread_mutex_unlock(&state->mtx);
			continue ;
		}
		pthread_mutex_unlock(&state->mtx);*/
		eating(philo);
		pthread_mutex_lock(&state->eat_mtx);
		philo->eat_times++;
		pthread_mutex_unlock(&state->eat_mtx);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&state->dead_mtx);
	}
	pthread_mutex_unlock(&state->dead_mtx);
	return (NULL);
}
