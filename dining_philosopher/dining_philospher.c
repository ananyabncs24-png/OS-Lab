#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

int n;
int state[MAX]; // 0 = THINKING, 1 = HUNGRY, 2 = EATING

pthread_mutex_t mutex;
pthread_cond_t cond[MAX];

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int LEFT(int i) { return (i + n - 1) % n; }
int RIGHT(int i) { return (i + 1) % n; }

void test(int i) {
    if (state[i] == HUNGRY &&
        state[LEFT(i)] != EATING &&
        state[RIGHT(i)] != EATING) {

        state[i] = EATING;
        printf("Philosopher %d is EATING\n", i);
        pthread_cond_signal(&cond[i]);
    }
}

void take_fork(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);

    test(i);

    while (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);

    pthread_mutex_unlock(&mutex);
}

void put_fork(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = THINKING;
    printf("Philosopher %d is THINKING\n", i);

    test(LEFT(i));
    test(RIGHT(i));

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is THINKING\n", id);
        sleep(1);

        take_fork(id);
        sleep(2);

        put_fork(id);
    }
}

int main() {
    pthread_t p[MAX];
    int ids[MAX];

    printf("Enter number of philosophers: ");
    scanf("%d", &n);

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < n; i++) {
        pthread_cond_init(&cond[i], NULL);
        state[i] = THINKING;
    }

    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&p[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < n; i++)
        pthread_join(p[i], NULL);

    return 0;
}
