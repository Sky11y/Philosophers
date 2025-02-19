#include "philosophers.h"

static void	init_philos(t_master *data, char **argv)
{
	int		i;

	i = 0;
	while (i < data->no_of_philos)
	{
		printf("address of philo %d: %p\n", i + 1, &(data->philos[i]));
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = philo_atoi(argv[2]);
		data->philos[i].time_to_eat = philo_atoi(argv[3]);
		data->philos[i].time_to_sleep = philo_atoi(argv[4]);
		i++;
	}
}

void	*function(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	printf("I'm philosopher %d\n", philo->id);
	return ((void *)0);
}

static int	create_threads(t_master *data)
{
	pthread_t	*philosopher;
	int			i;
	int			ret;

	i = 0;
	philosopher = malloc(sizeof(pthread_t) * data->no_of_philos);
	if (!philosopher)
		return (4);
	while (i < data->no_of_philos)
	{
		if (pthread_create(&philosopher[i], NULL, &function,
					(void *)(&data->philos[i])))
			return (5);
		i++;
	}
	i = 0;
	while (i < data->no_of_philos)
	{
		ret = pthread_join(philosopher[i], NULL);
		if (ret)
			return (6);
		i++;
	}
	free(philosopher);
	return (ret);
}

int main(int argc, char **argv)
{
	int			exit_status;
	t_master	master;

	if (argc != 5)
		return (1);
	if (check_input(argc, argv))
		return (2);
	master.no_of_philos = philo_atoi(argv[1]);
	printf("number of filos: %d\n", master.no_of_philos);
	master.philos = malloc(sizeof(t_philo *) * master.no_of_philos);
	if (!master.philos)
		return (3);
	printf("address of philo pointer in master: %p\n", master.philos);
	init_philos(&master, argv);
	exit_status = create_threads(&master);
	free(master.philos);
	return (exit_status);
}
