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
    // double res[4] = {0.0, 0.0, 0.0, 0.0};
    int len = (n < m ? n : m);
    for(int i = 0; i < len; i ++){
        // res[i % 4] += matrix[i * m + i];
        ans += matrix[i * m + i];
    }

    // for(int i = 0; i < 4; i ++){
    //     printf("%lf\n", res[i]);
    // }

    return ans;
}

double trace_arm(double * matrix, int n, int m)
{
    double res1 = 0, res2 = 0, res3 = 0, res4 = 0;
    long long len = (n < m ? n : m);
    // len--;
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

        "mov x10, xzr\n"        //initialize i = 0
        "add x11, x10, %4, lsl#0x3\n"
        "add x12, x11, %4, lsl#0x3\n"
        "add x13, x12, %4, lsl#0x3\n"
        //   "mov %1, x9\n"        //cout <<i;

        "fmov d5, xzr\n"           //res = 0.0
        "fmov d6, xzr\n"
        "fmov d7, xzr\n"
        "fmov d8, xzr\n"


        "mov x4, #0x4\n"
        "sdiv x1, %2, x4\n"
        "mul x1, x1, x4\n"
        "sub x2, %2, x1\n"
        // "mov %1, x1\n"

        "begin:\n"                // for loop begin
        // "mov x3, x9, lsl#0x3\n"            //LSL 逻辑左移 ASL 算术左移 double 是8个byte
        // "mov %1, x3\n"
        // "add %1, %1, x3\n"     
        // "fmov d0,#1.0\n"

        "ldr d0, [%3, x10]\n"  //x4 = matrix[i]
        "ldr d1, [%3, x11]\n"  
        "ldr d2, [%3, x12]\n"  
        "ldr d3, [%3, x13]\n" 
        "add x10, x10, %4, lsl#0x5\n"     //i = i + step;
        "add x11, x11, %4, lsl#0x5\n"   
        "add x12, x12, %4, lsl#0x5\n"    
        "add x13, x13, %4, lsl#0x5\n" 
        "fadd d5, d5, d0\n"     //res = res + matrix[i]
        "fadd d6, d6, d1\n"   
        "fadd d7, d7, d2\n"    
        "fadd d8, d8, d3\n"     
        "sub x1, x1, #0x4\n"        
        // "fmov %0, d1\n"  
        // "mov %0, %2\n"    //cout << res;

        // "mov %1, x4\n"             //cout << x4;
        // "add %1, %1, #0x1\n"
        "cbnz x1, begin\n"          //if(len != 0) jump to begin
        "cbz x2, end\n"



        "res:\n"
        "ldr d0, [%3, x10]\n"  //x4 = matrix[i]
        "sub x2, x2, #0x1\n"
        "fadd d5, d5, d0\n"     //res = res + matrix[i]
        "add x10, x10, %4, lsl#0x3\n"     //i = i + step;
        "cbnz x2, res\n"

        "end:\n"

        // "fmov %5, d5\n"
        // "fmov %6, d6\n"
        // "fmov %7, d7\n"
        // "fmov %8, d8\n"


        "fadd d5, d5, d6\n"
        "fadd d7, d7, d8\n"
        "fadd d5, d5, d7\n"
        "fmov %0, d5\n"
        
        : "+r"(x),   //%0
          "+r"(y),   //%1
          "+r"(len),   //2
          "+r"(matrix),  //3 point to matrix; address for matrix[0]
          "+r"(step),   //4
          "+r"(res1),   //5
          "+r"(res2),   //6
          "+r"(res3),   //7
          "+r"(res4)   //8

        :

        : "cc", "memory", //
          "d0",
          "d1",           //
          "d2",
          "d3",
          "d4",
          "d5",
          "d6",
          "d7",
          "d8",
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
    //   printf("%lf\n%lf\n%lf\n%lf\n", res1, res2, res3, res4);
     // printf("%lf\n^^^%lld\n", x, y);
    //   printf("%lf\n", x);
      return x;
}
//https://developer.arm.com/documentation/100069/0607/Overview-of-AArch64-state
//D0-D31 Advanced SIMD registers holding a 64-bit scalar, floating-point double-precision registers.

int main()
{
    int n, m;
    n = 32, m = 32;
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
    for(int i = 0; i < 200000; i ++)
        trace_c(matrix, n, m);

    clock_gettime(CLOCK_REALTIME, &time_end1);
    printf("结束时间 %lus,%lu ns\n", time_end1.tv_sec, time_end1.tv_nsec);

    printf("程序运行时间:%lldns\n", 
          1ll * (time_end1.tv_sec - time_start1.tv_sec) * (long long)(1e9) +  time_end1.tv_nsec - time_start1.tv_nsec);
    printf("C program result : %lf\n", ans_c);

    printf("\n\n");

    
    struct timespec time_start2 = {0, 0}, time_end2 = {0, 0};
   
    clock_gettime(CLOCK_REALTIME, &time_start2);
    printf("开始时间 %lus,%lu ns\n", time_start2.tv_sec, time_start2.tv_nsec);
    
    double ans_arm = trace_arm(matrix, n, m);
    for(int i = 0; i < 200000; i ++)
        trace_arm(matrix, n, m);

    clock_gettime(CLOCK_REALTIME, &time_end2);
    printf("结束时间 %lus,%lu ns\n", time_end2.tv_sec, time_end2.tv_nsec);

    printf("程序运行时间:%lldns\n",
           1LL * (time_end2.tv_sec - time_start2.tv_sec) *(long long)(1e9) + time_end2.tv_nsec - time_start2.tv_nsec);

    printf("arm program result : %lf\n", ans_arm);
    free(matrix); 

}
