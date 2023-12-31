#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 5

int n1, m1, n2, m2;
int B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE], A[MAX_SIZE][MAX_SIZE];
int T[MAX_SIZE];

sem_t empty, full, mutex;

void *producer(void *arg) {
    int line = *((int *)arg);

    for (int j = 0; j < m2; j++) {
        int result = 0;
        for (int k = 0; k < m1; k++) {
            result += B[line][k] * C[k][j];
        }

        // make the results in the buffer
        sem_wait(&empty);
        sem_wait(&mutex);
        T[line * m2 + j] = result;  // Use a single-dimensional index for the buffer
        sem_post(&mutex);
        sem_post(&full);
    }

    free(arg);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int column = *((int *)arg);

    for (int i = 0; i < n1; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        A[i][column] = T[i * m2 + column]; // Use a single-dimensional index for the buffer
        sem_post(&mutex);
        sem_post(&empty);
    }

    free(arg);
    pthread_exit(NULL);
}


int main() {
    sem_init(&empty, 0, MAX_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    printf("insert matrix b dimensions (n1 m1, limited at %d) : ", MAX_SIZE);
    scanf("%d %d", &n1, &m1);

    printf("insert matrix C dimensions (n2 m2, limited at %d) : ", MAX_SIZE);
    scanf("%d %d", &n2, &m2);

    if (m1 != n2) {
        fprintf(stderr, " matrix dimensions aren't relevant to make a multiplication");
        return EXIT_FAILURE;
    }

    if (n1 > MAX_SIZE || m1 > MAX_SIZE || n2 > MAX_SIZE || m2 > MAX_SIZE) {
        fprintf(stderr, "matrix dimension is above the permitted size ");
        return EXIT_FAILURE;
    }

    printf("insert matrix b elements  :\n");
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1; j++)
            scanf("%d", &B[i][j]);

    printf("insert matrix c elements:\n ");
    for (int i = 0; i < n2; i++)
        for (int j = 0; j < m2; j++)
            scanf("%d", &C[i][j]);

    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
            A[i][j] = 0;

    // create producer threads
    pthread_t threadsProducers[n1];
    for (int i = 0; i < n1; i++) {
        int *line = malloc(sizeof(int));
        *line = i;
        pthread_create(&threadsProducers[i], NULL, producer, (void *)line);
    }

    // create consumer threads
    pthread_t threadsConsumers[m2];
    for (int j = 0; j < m2; j++) {
        int *column = malloc(sizeof(int));
        *column = j;
        pthread_create(&threadsConsumers[j], NULL, consumer, (void *)column);
    }

    for (int i = 0; i < n1; i++)
        pthread_join(threadsProducers[i], NULL);

    for (int j = 0; j < m2; j++)
        pthread_join(threadsConsumers[j], NULL);

    printf("final matrix  A :\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}