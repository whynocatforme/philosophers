/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yapark <yapark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:47:45 by yapark            #+#    #+#             */
/*   Updated: 2021/01/28 02:22:35 by yapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define F " has taken a fork\n"
# define E " is eating\n"
# define S " is sleeping\n"
# define T " is thinking\n"
# define D " died\n"
# define L 0
# define R 1

struct s_state;

typedef struct		s_philo
{
	struct s_state	*state;
	int				idx;
	int				forks[2];
	int				doing;
	int				eat_times;
	pthread_t		pid;
	pthread_t		chk_pid;
	long			last_meal;
}					t_philo;

typedef struct		s_state
{
	t_philo			**philos;
	int				*forks;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	mtx; //???
	pthread_mutex_t dead_mtx;
	pthread_mutex_t eat_mtx;
	pthread_mutex_t	write_mtx;
	int				dead;
	int				num;
	int				die;
	int				eat;
	int				finished;
	int				sleep;
	int				times;
	long			start;
}					t_state;

void				*routine(void *arg);
int					ft_strlen(const char *str);
int					ft_exit(t_state *s, const char *msg);
int					ft_atoi(char *str);
long				get_time(void);
void				put_msg(long time, t_philo *philo, const char *act);
void				ft_sleep(long time);

#endif
