#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#define sizess 1000000
int group1[sizess];
int group2[sizess];
int group3[sizess];
int group4[sizess];
int bigArray[1000001];
int pos = 0;
// int sizeofArray = 10;
// int array1[sizeofArray];

void *mainThread(void *args)
{
  time_t t;
  srand((unsigned long)args);
  int *ptr_array = args;

  int i = 0;

  int upper = 500000, count = 1000000;

  // printf("\nThe random numbers are: ");
  while (i < count)
  {
    int num = ((1 + (rand() * rand()) % upper) * 2) - 1;
    // printf("%d. ",num);
    ptr_array[i] = num;
    i++;
  }

  printf("\n");
  return NULL;
}

void *comThread(void *arg)
{
  int pthread_mutex_lock(pthread_mutex_t * mainThread);
  int *incoming_array = arg; // points to array in question
  for (int i = 0; i < 1000001 - 1; i++)
  {
    if (incoming_array[i] == incoming_array[i + 1])
    {
      bigArray[pos] = incoming_array[i];
      pos++;
    }
  }
  int pthread_mutex_unlock(pthread_mutex_t * mainThread);
  return NULL;
}
/*void *comThread(void *args)
{
  int *ptr_array = args;
  for (int k = 0; k < 1000000; k++)
    if (ptr_array[k] == ptr_array[k + 1])
    {
      printf("%d ", ptr_array[k]);
      bigArray[k] = ptr_array[k];
    }
  return NULL;
}
*/
void *displayThread(void *args)
{

  for (int i = 0; i < 1000000; i++)
  {

    if (bigArray[i] != 0 && bigArray[i] > 0 && bigArray[i] < 1000001)
    {
      printf("%d ", bigArray[i]);
    }
  }

  return NULL;
}

int main()
{

  pthread_t threads_id_1;
  pthread_create(&threads_id_1, NULL, mainThread, (void *)group1);
  pthread_join(threads_id_1, NULL);

  pthread_t threads_id_2;
  pthread_create(&threads_id_2, NULL, mainThread, (void *)group2);
  pthread_join(threads_id_2, NULL);

  pthread_t threads_id_3;
  pthread_create(&threads_id_3, NULL, mainThread, (void *)group3);
  pthread_join(threads_id_3, NULL);

  pthread_t threads_id_4;
  pthread_create(&threads_id_4, NULL, mainThread, (void *)group4);
  pthread_join(threads_id_4, NULL);

  pthread_t threads_id_5;
  pthread_create(&threads_id_5, NULL, comThread, (void *)group1);
  pthread_join(threads_id_5, NULL);

  pthread_t threads_id_6;
  pthread_create(&threads_id_6, NULL, comThread, (void *)group2);
  pthread_join(threads_id_6, NULL);

  pthread_t threads_id_7;
  pthread_create(&threads_id_7, NULL, comThread, (void *)group3);
  pthread_join(threads_id_7, NULL);

  pthread_t threads_id_8;
  pthread_create(&threads_id_8, NULL, comThread, (void *)group4);
  pthread_join(threads_id_8, NULL);

  pthread_t threads_id_9;
  pthread_create(&threads_id_9, NULL, displayThread, (void *)bigArray);
  pthread_join(threads_id_9, NULL);

  // Test individual array
  /*
    printf("\n group1 is: ");
    for (int i = 0; i < 10; i++)
    {
      printf("%d ", group1[i]);
    }

    printf("\n group2 is: ");
    for (int i = 0; i < 10; i++)
    {
      printf("%d ", group2[i]);
    }

    printf("\n group3 is: ");
    for (int i = 0; i < 10; i++)
    {
      printf("%d ", group3[i]);
    }

    printf("\n group4 is: ");
    for (int i = 0; i < 100; i++)
    {
      printf("%d ", group4[i]);
    }

*/
  return 0;
}
