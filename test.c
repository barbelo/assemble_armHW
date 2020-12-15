#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//double matrix[1010][1010];

double * init(int a, int b)
{
    double *matrix = (double *) malloc(sizeof(double ) * a * b);
    srand((unsigned)time(NULL));
//	int (*a)[2]=(int(*)[2])malloc(sizeof(int)*3*2);
//	
    int i, j;
    for(i = 0; i < a * b; i ++){
            matrix[i] = (1.0 * rand() * rand() + rand()) / (rand() + 1);
            // matrix[i] = (double)(i + 1) * 0.25;
//        printf("%d\n", j);
    }
    return matrix;
}

/*
try_matrix
0.250000 0.500000 0.750000 
1.000000 1.250000 1.500000 
1.750000 2.000000 2.250000
*/

double trace_c(double * matrix, int n, int m)
{
    double ans = 0.0;
    int len = (n < m ? n : m);
    for(int i = 0; i < len; i ++){
        ans += matrix[i * m + i];
    }
    return ans;
}

double trace_arm(double * matrix, int n, int m)
{
    double res = 0;
    long long len = (n < m ? n : m);
    // len = 3;
    long long step = (m + 1);
    double x = 0.0; long long y = 0;
    

    /*
    for(int i = 0, len = (n < m ? n : m); len > 0; i += step, len --)
    {
        res += matrix[i];
    }
    */
      __asm__ __volatile__(

        "mov x9, #0\n"        //initialize i = 0
        //   "mov %1, x9\n"        //cout <<i;
        "fmov d1, %0\n"           //res = 0.0
        "begin:\n"                // for loop begin
        "mov x3, x9, lsl#0x3\n"            //LSL 逻辑左移 ASL 算术左移 double 是8个byte
        // "mov %1, x3\n"
        // "add %1, %1, x3\n"    
        // "fmov d0,#1.0\n"

        "ldr d0, [%3, x3]\n"  //x4 = matrix[i]
        "add x9, x9, %4\n"     //i = i + step;
        "sub %2, %2, #0x1\n"        //len --;
        "fadd d1, d1, d0\n"     //res = res + matrix[i]
        // "fmov %0, d1\n"  
        // "mov %0, %2\n"    //cout << res;

        // "mov %1, x4\n"             //cout << x4;
        // "add %1, %1, #0x1\n"
        "cbnz %2, begin\n"          //if(len != 0) jump to begin
        "fmov %0, d1\n"
          
        : "+r"(x),   //%0
          "+r"(y),   //%1
          "+r"(len),   //2
          "+r"(matrix),  //3 point to matrix; address for matrix[0]
          "+r"(step)   //4

        :

        : "cc", "memory", //
          "d0",
          "d1",           //
          "x0",           //
          "x1",           //
          "x2",           //
          "x3",           //
          "x4",           //
          "x5",           //
          "x10",          //
          "x11",          //
          "x12",          //
          "x13"          //

      );
      //printf("%lf %lld\n", x, y);
    //   printf("%lf\n", x);
      return x;
}
//https://developer.arm.com/documentation/100069/0607/Overview-of-AArch64-state
//D0-D31 Advanced SIMD registers holding a 64-bit scalar, floating-point double-precision registers.

int main()
{
    int n, m;
    n = 1000, m = 1000;
    double * matrix = init(n, m);


	// for(int i = 0; i < n; i ++){
	// 	for(int j = 0; j < m; j ++){
	// 		printf("%lf ", matrix[i * m + j]);
	// 	}
	// 	printf("\n");
	// }

    printf("C program.\n");
   struct timespec time_start1 = {0, 0}, time_end1 = {0, 0};
   
   clock_gettime(CLOCK_REALTIME, &time_start1);
   printf("开始时间 %lus,%lu ns\n", time_start1.tv_sec, time_start1.tv_nsec);
   
    double ans_c = trace_c(matrix, n, m);
    for(int i = 0; i < 100000; i ++)
        trace_c(matrix, n, m);

    clock_gettime(CLOCK_REALTIME, &time_end1);
    printf("结束时间 %lus,%lu ns\n", time_end1.tv_sec, time_end1.tv_nsec);

    printf("程序运行时间:%lds %lldns\n", time_end1.tv_sec - time_start1.tv_sec,
          1ll * (time_end1.tv_sec - time_start1.tv_sec) * (long long)(1e9) +  time_end1.tv_nsec - time_start1.tv_nsec);
    printf("C program result : %lf\n", ans_c);

    printf("\n\n");


    
    

    
    struct timespec time_start2 = {0, 0}, time_end2 = {0, 0};
   
    clock_gettime(CLOCK_REALTIME, &time_start2);
    printf("开始时间 %lus,%lu ns\n", time_start2.tv_sec, time_start2.tv_nsec);
    
    double ans_arm = trace_arm(matrix, n, m);
    for(int i = 0; i < 100000; i ++)
        trace_arm(matrix, n, m);

    clock_gettime(CLOCK_REALTIME, &time_end2);
    printf("结束时间 %lus,%lu ns\n", time_end2.tv_sec, time_end2.tv_nsec);

    printf("程序运行时间:%lds %lldns\n", time_end2.tv_sec - time_start2.tv_sec,
           1LL * (time_end2.tv_sec - time_start2.tv_sec) *(long long)(1e9) + time_end2.tv_nsec - time_start2.tv_nsec);

    printf("arm program result : %lf\n", ans_arm);
    free(matrix); 

}
