TODO
1. check the input
    - no of philos/forks (1), time to die (2), eat (3) and sleep (4)
2. create a thread out of each filos
3. let unpaired filos take a fork on right side (n+1) / let paired filos take a fork on left side (n-1)
4. Those who got fork let them have another fork

at least 1 philosopher

|1|2|3|4|5|
if n gets fork on right (n-1) and (n+1) won't be able to eat (lock mutex)
so they need to think
after n has eaten he goes to sleep and both forks are available (unlock mutex)
(n+1) takes the fork on left and starts waiting for fork on right
(n-1) takes the fork on right and starts waiting for fork on left

IMPORTANT
1. asymmetric order where every other gets fork on right and every other fork on left makes sure that at least one philo is eating
2. If a philo holds on to a fork to long it should drop it
3. [Add a condition that if philo has not eaten in long time he's the next waiting and does not drop the fork]

while eating there should be two forks on philos hand; one in both
when eating is done philo puts forks back on the table and starts to sleep
After sleeping philo starts to think

If a philosopher dies the program ends.

Rules
No global variables
libft forbidden

input: no_of_philos, time_to_die, time_to_eat, time_to_sleep [bonus: no_of_times_each_philo_needs_to_eat]

All the times are in milliseconds

philo(n) sits between philo(n-1) and philo(n+1)

State changes need to be formatted like this:
- timestamp_in_ms philo(n) has taken a fork
- timestamp_in_ms philo(n) is eating
- timestamp_in_ms philo(n) is sleeping
- timestamp_in_ms philo(n) is thinking
- timestamp_in_ms philo(n) died

Rejections:
- A displayed state message should not be mixed up with another message
- A message announcing a philospher died should not be displayed no more than 10 ms after the actual death of the philosopher
- The program should not have data races


