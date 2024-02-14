#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// Constants
#define NUM_PHILOSOPHERS  5

// Philosophers structure
typedef struct {
    int				id;
    char			*state;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
} Philosopher;

// Function prototypes
void*	philosopher_behavior(void* arg);
void	initialize_philosophers();
void	cleanup_resources();

// Global resources
pthread_mutex_t	forks[NUM_PHILOSOPHERS];
Philosopher		philosophers[NUM_PHILOSOPHERS];

void* philosopher_behavior(void* arg) {
	Philosopher* philosopher = (Philosopher*)arg;

	while (1) {
		// Simulate thinking
		usleep(rand() %  1000000);

		// Try to pick up forks
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->right_fork);

		// Simulate eating
		philosopher->state = "eating";
		usleep(rand() %  1000000);

		// Put down forks
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);

		// Simulate thinking
		philosopher->state = "thinking";
	}

	return NULL;
}

void initialize_philosophers() {
	// Initialize forks
	for (int i =  0; i < NUM_PHILOSOPHERS; ++i) {
		pthread_mutex_init(&forks[i], NULL);
	}

	// Initialize philosophers
	for (int i =  0; i < NUM_PHILOSOPHERS; ++i) {
		philosophers[i].id = i;
		philosophers[i].state = "thinking";
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i +  1) % NUM_PHILOSOPHERS];
	}
}

void cleanup_resources() {
	// Destroy mutexes
	for (int i =  0; i < NUM_PHILOSOPHERS; ++i) {
		pthread_mutex_destroy(&forks[i]);
	}

	// Free allocated memory for philosophers
	// free(philosophers);
}

// Main function
int main() {
	// Seed the random number generator
	srand(time(NULL));

	// Initialize philosophers and resources
	initialize_philosophers();

	// Create philosopher threads
	pthread_t philosophers_threads[NUM_PHILOSOPHERS];
	for (int i =  0; i < NUM_PHILOSOPHERS; ++i) {
		pthread_create(&philosophers_threads[i], NULL, philosopher_behavior, &philosophers[i]);
		pthread_detach(philosophers_threads[i]);
	}

	// for (int i =  0; i < NUM_PHILOSOPHERS; ++i) {
	// 	pthread_join(philosophers_threads[i], NULL);
	// }
	// Wait for philosophers to finish eating
	sleep(60); // Adjust this value based on how long you want the philosophers to eat

	// Cleanup resources
	cleanup_resources();

	return 0;
}