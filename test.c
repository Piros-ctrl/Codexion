// #include <pthread.h>
// #include <stdio.h>
// #include <unistd.h>
// #include <sys/time.h>

// int counter = 0;
// pthread_mutex_t lock;

// void *ft_rotine(void *arg)
// {
//     int t = *(int *)arg;
//     int i = 0;
//     pthread_mutex_lock(&lock);
//     while (i < 10000000)
//     {
//         counter ++;
//         i++;
//         // printf("it is work thread %d\n",t);
//     }
//     pthread_mutex_unlock(&lock);
//     return NULL;
// }

// int main()
// {
//     struct timeval tv;
//     pthread_t thread_1;
//     int i_1 = 1;
//     pthread_t thread_2;
//     int i_2 = 2;
//     pthread_mutex_init(&lock,NULL);
//     pthread_create(&thread_1,NULL,ft_rotine,&i_1);
//     pthread_create(&thread_2,NULL,ft_rotine,&i_2);
//     gettimeofday(&tv, NULL);
//     printf("\n\n%ld\n", tv.tv_usec);
//     pthread_join(thread_1, NULL);
//     printf("counter %d\n",counter);
//     gettimeofday(&tv, NULL);
//     printf("\n\n%ld\n", tv.tv_usec);
// }