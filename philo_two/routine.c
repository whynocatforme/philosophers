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
	sem_wait(state->taking_sem);
	sem_wait(state->forks_sem);
	put_msg(get_time() - state->start, philo, F);
	sem_wait(state->forks_sem);
	put_msg(get_time() - state->start, philo, F);
	sem_post(state->taking_sem);
	sem_wait(state->eat_sem);
	philo->last_meal = get_time();
	philo->eat_times++;
	sem_post(state->eat_sem);
	put_msg(philo->last_meal - state->start, philo, E);
	ft_sleep(state->eat);
	sem_post(state->forks_sem);
	sem_post(state->forks_sem);
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
	sem_wait(state->dead_sem);
	while (!state->dead)
	{
		sem_post(state->dead_sem);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		sem_wait(state->dead_sem);
	}
	sem_post(state->dead_sem);
	return (NULL);
}
