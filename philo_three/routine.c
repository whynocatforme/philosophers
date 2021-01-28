/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 22:12:14 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 10:03:51 by yapark           ###   ########.fr       */
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

static void	*write_full(void *arg)
{
	t_philo *p;

	p = (t_philo*)arg;
	sem_wait(p->state->eat_sem);
	while (p->eat_times < p->state->times)
	{
		sem_post(p->state->eat_sem);
		sem_wait(p->state->eat_sem);
	}
	sem_post(p->state->eat_sem);
	sem_post(p->state->full_sem);
	return (NULL);
}

static void	*listen_dead(void *arg)
{
	t_philo *p;

	p = (t_philo*)arg;
	sem_wait(p->state->dead_sem);
	sem_post(p->state->full_sem);
	exit(1);
	return (NULL);
}

static void	*write_dead(void *arg)
{
	t_philo *p;

	p = (t_philo*)arg;
	sem_wait(p->state->eat_sem);
	while (get_time() - p->last_meal < p->state->die)
	{
		sem_post(p->state->eat_sem);
		sem_wait(p->state->eat_sem);
	}
	sem_post(p->state->eat_sem);
	sem_post(p->state->dead_sem);
	put_msg(get_time() - p->state->start, p, D);
	p->state->dead++;
	sem_post(p->state->full_sem);
	exit(1);
	return (NULL);
}

void		*routine(void *arg)
{
	t_philo		*philo;
	t_state		*state;
	pthread_t	dead_listen_pid;
	pthread_t	dead_write_pid;
	pthread_t	full_write_pid;

	philo = (t_philo*)arg;
	if (philo->idx % 2)
		ft_sleep(20);
	state = philo->state;
	philo->last_meal = get_time();
	pthread_create(&dead_listen_pid, NULL, &listen_dead, philo);
	pthread_create(&dead_write_pid, NULL, &write_dead, philo);
	pthread_create(&full_write_pid, NULL, &write_full, philo);
	while (1)
	{
		eating(philo);
		put_msg(get_time() - philo->state->start, philo, S);
		ft_sleep(philo->state->sleep);
		put_msg(get_time() - philo->state->start, philo, T);
	}
	pthread_detach(dead_listen_pid);
	pthread_detach(dead_write_pid);
	pthread_detach(full_write_pid);
	return (NULL);
}
