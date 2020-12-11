#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double ** init(int a, int b)
{
    double ** matrix = (double **) malloc(a * b * sizeof(double));
    srand((unsigned)time(NULL));
    for(int i = 0; i < a; i ++){
        for(int j = 0; j < b; j ++){
        printf("%d\n", j);
            // matrix[i][j] = 1.0 * rand() * rand();
        }
    }
}

double trace_c(double ** matrix, int n, int m)
{
    double ans = 0.0;
    int len = (n < m ? n : m);
    for(int i = 0; i < len; i ++){
        ans += matrix[i][i];
    }
    return ans;
}

int main()
{
    int n, m;
    n = 1000, m = 1000;
    double ** matrix = init(n, m);

    printf("asd\n");
    struct timespec time_start1 = {0, 0}, time_end1 = {0, 0};
    
    clock_gettime(CLOCK_REALTIME, &time_start1);
    printf("开始时间 %lus,%lu ns\n", time_start1.tv_sec, time_start1.tv_nsec);
    
    trace_c(matrix, n, m);

    clock_gettime(CLOCK_REALTIME, &time_end1);
    printf("结束时间 %lus,%lu ns\n", time_end1.tv_sec, time_end1.tv_nsec);

    printf("程序运行时间:%lds %ldns\n", time_end1.tv_sec - time_start1.tv_sec,
           time_end1.tv_nsec - time_start1.tv_nsec);

    
    // struct timespec time_start2 = {0, 0}, time_end2 = {0, 0};
   
    // clock_gettime(CLOCK_REALTIME, &time_start2);
    // printf("开始时间 %lus,%lu ns\n", time_start2.tv_sec, time_start2.tv_nsec);
    
    // perspectiveTransform(src, des, m, MAXX * MAXY);

    // clock_gettime(CLOCK_REALTIME, &time_end2);
    // printf("结束时间 %lus,%lu ns\n", time_end2.tv_sec, time_end2.tv_nsec);

    // printf("程序运行时间:%lds %ldns\n", time_end2.tv_sec - time_start2.tv_sec,
    //        time_end2.tv_nsec - time_start2.tv_nsec);

}