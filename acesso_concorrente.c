#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define ARRAY_SIZE 5
#define NUM_WRITERS 2
#define NUM_READERS 14

int array[ARRAY_SIZE] = {-1, -1, -1, -1, -1};
pthread_rwlock_t rwlock;
pthread_mutex_t writer_mutex = PTHREAD_MUTEX_INITIALIZER;
int num_writers_finished = 0;

int is_array_full(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == -1)
        {
            return 0;
        }
    }

    return 1;
}

void *writer(void *thread_id)
{
    int id = *(int *)thread_id;

    while (1)
    {
        pthread_rwlock_wrlock(&rwlock);

        if (is_array_full(array, ARRAY_SIZE))
        {
            pthread_rwlock_unlock(&rwlock);
            break;
        }

        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            if (array[i] == -1)
            {
                array[i] = rand() % 100;
                printf("[Thread Writer #%d] Writing number: %d\n", id, array[i]);
                break;
            }
        }

        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }

    pthread_mutex_lock(&writer_mutex);
    num_writers_finished++;
    pthread_mutex_unlock(&writer_mutex);

    pthread_exit(NULL);
}

void *reader(void *thread_id)
{
    int id = *(int *)thread_id;

    while (num_writers_finished < NUM_WRITERS)
    {
        pthread_rwlock_rdlock(&rwlock);

        printf("[Thread Reader #%d] Array values: ", id);

        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            if (array[i] == -1)
            {
                printf("- ");
            }
            else
            {
                printf("%d ", array[i]);
            }
        }

        printf("\n");

        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }

    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));

    pthread_t writers[NUM_WRITERS];
    pthread_t readers[NUM_READERS];

    pthread_rwlock_init(&rwlock, NULL);

    int writer_ids[NUM_WRITERS];
    int reader_ids[NUM_READERS];

    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
