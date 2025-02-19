#ifndef PHILOSPHERS_H
 #define PHILOSOPHERS_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> // All the pthread functions: create, detach, join
					  // mutex_init, mutex_destroy, mutex_lock, mutex_unlock

typedef struct s_master
{
	int 			no_of_philos;
	struct s_philo	*philos;
}	t_master;

typedef struct s_philo
{
	int id;	
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;

}	t_philo;

int		philo_atoi(char *num);
int		check_input(int argc, char **argv);


#endif
