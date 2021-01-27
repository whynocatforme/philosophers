/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:12:14 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 05:42:01 by yapark           ###   ########.fr       */
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
	usleep(state->eat * 1000);
	//state->forks[philo->forks[L]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[L]]);
	//state->forks[philo->forks[R]] = -1;
	pthread_mutex_unlock(&state->forks_mtx[philo->forks[R]]);
}

static void	sleeping(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, S);
	usleep(philo->state->sleep * 1000);
}

static void thinking(t_philo *philo)
{
	put_msg(get_time() - philo->state->start, philo, T);
}

void		*check(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	pthread_mutex_lock(&philo->state->dead_mtx);
	while (!philo->state->dead)
	{
		pthread_mutex_unlock(&philo->state->dead_mtx);
		if (get_time() - philo->last_meal > philo->state->die)
		{
			pthread_mutex_lock(&philo->state->dead_mtx);
			write(1, "here\n", 5);
			put_msg(get_time() - philo->state->start, philo, D);
			philo->state->dead++;
			pthread_mutex_unlock(&philo->state->dead_mtx);
			return NULL;
		}
		pthread_mutex_lock(&philo->state->dead_mtx);
	}
	pthread_mutex_unlock(&philo->state->dead_mtx);
	return NULL;
}

void		*routine(void *arg)
{
	t_philo *philo;
	t_state *state;
	pthread_t chk;

	philo = (t_philo*)arg;
	if (philo->idx % 2)
		usleep(100);
	state = philo->state;
	philo->last_meal = get_time();
	//pthread_create(&chk, NULL, check, philo);
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
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&state->dead_mtx);
	}
	pthread_mutex_unlock(&state->dead_mtx);
	//pthread_detach(chk);
	return (NULL);
}
