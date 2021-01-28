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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# define F " has taken a fork\n"
# define E " is eating\n"
# define S " is sleeping\n"
# define T " is thinking\n"
# define D " died\n"

struct s_state;

typedef struct		s_philo
{
	struct s_state	*state;
	int				idx;
	int				eat_times;
	pthread_t		pid;
	long			last_meal;
}					t_philo;

typedef struct		s_state
{
	t_philo			**philos;
	sem_t			*forks_sem;
	sem_t			*write_sem;
	sem_t			*dead_sem;
	sem_t			*taking_sem;
	sem_t			*eat_sem;
	int				full;
	int				dead;
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				times;
	long			start;
}					t_state;

t_state				*init_state(int argc, char **argv);
void				*routine(void *arg);
int					ft_strlen(const char *str);
int					ft_exit(t_state *s, const char *msg);
int					ft_atoi(char *str);
long				get_time(void);
void				put_msg(long time, t_philo *philo, const char *act);
void				ft_sleep(long time);

#endif
