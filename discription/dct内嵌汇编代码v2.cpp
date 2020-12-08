
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _MSC_VER
#	include <intrin.h>
#	include <emmintrin.h>
#	include <io.h>

#	define CACHE_ALIGN __declspec(align(64))
#	define SIMD_ALIGN __declspec(align(16))
typedef unsigned __int64 uint64_t;
#else
#	include <stdint.h>
#	include <unistd.h>
#	define CACHE_ALIGN __attribute__ ((aligned(64)))
#	define SIMD_ALIGN __attribute__ ((aligned(16)))
#endif




//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void matrix_mul_asm(short **aa,short **bb,short **cc, short d, short e)
{
	short *a=(short *)aa;
	short *b=(short *)bb;
	short *c=(short *)cc;
/*
for (i = 0; i < 8; i++)
	{
		for(j=0; j<8; j++)
		{
			sum[j] = 0;
			for (k = 0; k < 8; k++) 
				sum[j] = sum[j] + cola[i*8+k] * pixels[j][k];
			irows2[j][i] = sum[j];	
			rows2[j][i] = (short)(sum[j] >> sh14[i]);
		}
	}
*/
__asm__ __volatile__ (
		"add x1, %0, #64                            \n\t"
        	"add x2, %1, #64                            \n\t"
        	"add x3, %2, #64                            \n\t"
		"mov x4, %3                            \n\t"
		"mov x5, %4                            \n\t"

		"ld1 {v0.8h, v1.8h, v2.8h, v3.8h}, [%0]     \n\t"
        	"ld1 {v4.8h, v5.8h, v6.8h, v7.8h}, [x1]   \n\t"
	
        	"ld1 {v8.8h, v9.8h, v10.8h, v11.8h}, [%1]     \n\t"
        	"ld1 {v12.8h, v13.8h, v14.8h, v15.8h}, [x2] \n\t"
//0,0
        	"smull v24.4s, v0.4h, v8.4h \n\t"
		"smull2 v25.4s, v0.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[0], w6 \n\t"
//0,1
		"smull v24.4s, v0.4h, v9.4h \n\t"
		"smull2 v25.4s, v0.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[1], w6 \n\t"
//0,2
		"smull v24.4s, v0.4h, v10.4h \n\t"
		"smull2 v25.4s, v0.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[2], w6 \n\t"

//0,3
		"smull v24.4s, v0.4h, v11.4h \n\t"
		"smull2 v25.4s, v0.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[3], w6 \n\t"

//0,4
		"smull v24.4s, v0.4h, v12.4h \n\t"
		"smull2 v25.4s, v0.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[4], w6 \n\t"

//0,5
		"smull v24.4s, v0.4h, v13.4h \n\t"
		"smull2 v25.4s, v0.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[5], w6 \n\t"

//0,6
		"smull v24.4s, v0.4h, v14.4h \n\t"
		"smull2 v25.4s, v0.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[6], w6 \n\t"

//0,7
		"smull v24.4s, v0.4h, v15.4h \n\t"
		"smull2 v25.4s, v0.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[7], w6 \n\t"

//1,0
        	"smull v24.4s, v1.4h, v8.4h \n\t"
		"smull2 v25.4s, v1.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[0], w6 \n\t"
//1,1
		"smull v24.4s, v1.4h, v9.4h \n\t"
		"smull2 v25.4s, v1.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[1], w6 \n\t"
//1,2
		"smull v24.4s, v1.4h, v10.4h \n\t"
		"smull2 v25.4s, v1.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[2], w6 \n\t"

//1,3
		"smull v24.4s, v1.4h, v11.4h \n\t"
		"smull2 v25.4s, v1.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[3], w6 \n\t"

//1,4
		"smull v24.4s, v1.4h, v12.4h \n\t"
		"smull2 v25.4s, v1.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[4], w6 \n\t"

//1,5
		"smull v24.4s, v1.4h, v13.4h \n\t"
		"smull2 v25.4s, v1.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[5], w6 \n\t"

//1,6
		"smull v24.4s, v1.4h, v14.4h \n\t"
		"smull2 v25.4s, v1.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[6], w6 \n\t"

//1,7
		"smull v24.4s, v1.4h, v15.4h \n\t"
		"smull2 v25.4s, v1.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[7], w6 \n\t"

//2,0
        	"smull v24.4s, v2.4h, v8.4h \n\t"
		"smull2 v25.4s, v2.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[0], w6 \n\t"
//2,1
		"smull v24.4s, v2.4h, v9.4h \n\t"
		"smull2 v25.4s, v2.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[1], w6 \n\t"
//2,2
		"smull v24.4s, v2.4h, v10.4h \n\t"
		"smull2 v25.4s, v2.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[2], w6 \n\t"

//2,3
		"smull v24.4s, v2.4h, v11.4h \n\t"
		"smull2 v25.4s, v2.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[3], w6 \n\t"

//2,4
		"smull v24.4s, v2.4h, v12.4h \n\t"
		"smull2 v25.4s, v2.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[4], w6 \n\t"

//2,5
		"smull v24.4s, v2.4h, v13.4h \n\t"
		"smull2 v25.4s, v2.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[5], w6 \n\t"

//2,6
		"smull v24.4s, v2.4h, v14.4h \n\t"
		"smull2 v25.4s, v2.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[6], w6 \n\t"

//2,7
		"smull v24.4s, v2.4h, v15.4h \n\t"
		"smull2 v25.4s, v2.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[7], w6 \n\t"

//3,0
        	"smull v24.4s, v3.4h, v8.4h \n\t"
		"smull2 v25.4s, v3.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[0], w6 \n\t"
//3,1
		"smull v24.4s, v3.4h, v9.4h \n\t"
		"smull2 v25.4s, v3.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[1], w6 \n\t"
//3,2
		"smull v24.4s, v3.4h, v10.4h \n\t"
		"smull2 v25.4s, v3.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[2], w6 \n\t"

//3,3
		"smull v24.4s, v3.4h, v11.4h \n\t"
		"smull2 v25.4s, v3.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[3], w6 \n\t"

//3,4
		"smull v24.4s, v3.4h, v12.4h \n\t"
		"smull2 v25.4s, v3.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[4], w6 \n\t"

//3,5
		"smull v24.4s, v3.4h, v13.4h \n\t"
		"smull2 v25.4s, v3.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[5], w6 \n\t"

//3,6
		"smull v24.4s, v3.4h, v14.4h \n\t"
		"smull2 v25.4s, v3.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[6], w6 \n\t"

//3,7
		"smull v24.4s, v3.4h, v15.4h \n\t"
		"smull2 v25.4s, v3.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[7], w6 \n\t"

//4,0
        	"smull v24.4s, v4.4h, v8.4h \n\t"
		"smull2 v25.4s, v4.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[0], w6 \n\t"
//4,1
		"smull v24.4s, v4.4h, v9.4h \n\t"
		"smull2 v25.4s, v4.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[1], w6 \n\t"
//4,2
		"smull v24.4s, v4.4h, v10.4h \n\t"
		"smull2 v25.4s, v4.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[2], w6 \n\t"

//4,3
		"smull v24.4s, v4.4h, v11.4h \n\t"
		"smull2 v25.4s, v4.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[3], w6 \n\t"

//4,4
		"smull v24.4s, v4.4h, v12.4h \n\t"
		"smull2 v25.4s, v4.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[4], w6 \n\t"

//4,5
		"smull v24.4s, v4.4h, v13.4h \n\t"
		"smull2 v25.4s, v4.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[5], w6 \n\t"

//4,6
		"smull v24.4s, v4.4h, v14.4h \n\t"
		"smull2 v25.4s, v4.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[6], w6 \n\t"

//4,7
		"smull v24.4s, v4.4h, v15.4h \n\t"
		"smull2 v25.4s, v4.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[7], w6 \n\t"

//5,0
        	"smull v24.4s, v5.4h, v8.4h \n\t"
		"smull2 v25.4s, v5.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[0], w6 \n\t"
//5,1
		"smull v24.4s, v5.4h, v9.4h \n\t"
		"smull2 v25.4s, v5.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[1], w6 \n\t"
//5,2
		"smull v24.4s, v5.4h, v10.4h \n\t"
		"smull2 v25.4s, v5.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[2], w6 \n\t"

//5,3
		"smull v24.4s, v5.4h, v11.4h \n\t"
		"smull2 v25.4s, v5.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[3], w6 \n\t"

//5,4
		"smull v24.4s, v5.4h, v12.4h \n\t"
		"smull2 v25.4s, v5.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[4], w6 \n\t"

//5,5
		"smull v24.4s, v5.4h, v13.4h \n\t"
		"smull2 v25.4s, v5.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[5], w6 \n\t"

//5,6
		"smull v24.4s, v5.4h, v14.4h \n\t"
		"smull2 v25.4s, v5.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[6], w6 \n\t"

//5,7
		"smull v24.4s, v5.4h, v15.4h \n\t"
		"smull2 v25.4s, v5.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[7], w6 \n\t"

//6,0
        	"smull v24.4s, v6.4h, v8.4h \n\t"
		"smull2 v25.4s, v6.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[0], w6 \n\t"
//6,1
		"smull v24.4s, v6.4h, v9.4h \n\t"
		"smull2 v25.4s, v6.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[1], w6 \n\t"
//6,2
		"smull v24.4s, v6.4h, v10.4h \n\t"
		"smull2 v25.4s, v6.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[2], w6 \n\t"

//6,3
		"smull v24.4s, v6.4h, v11.4h \n\t"
		"smull2 v25.4s, v6.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[3], w6 \n\t"

//6,4
		"smull v24.4s, v6.4h, v12.4h \n\t"
		"smull2 v25.4s, v6.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[4], w6 \n\t"

//6,5
		"smull v24.4s, v6.4h, v13.4h \n\t"
		"smull2 v25.4s, v6.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[5], w6 \n\t"

//6,6
		"smull v24.4s, v6.4h, v14.4h \n\t"
		"smull2 v25.4s, v6.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[6], w6 \n\t"

//6,7
		"smull v24.4s, v6.4h, v15.4h \n\t"
		"smull2 v25.4s, v6.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[7], w6 \n\t"

//7,0
        	"smull v24.4s, v7.4h, v8.4h \n\t"
		"smull2 v25.4s, v7.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[0], w6 \n\t"
//7,1
		"smull v24.4s, v7.4h, v9.4h \n\t"
		"smull2 v25.4s, v7.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[1], w6 \n\t"
//7,2
		"smull v24.4s, v7.4h, v10.4h \n\t"
		"smull2 v25.4s, v7.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[2], w6 \n\t"

//7,3
		"smull v24.4s, v7.4h, v11.4h \n\t"
		"smull2 v25.4s, v7.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[3], w6 \n\t"

//7,4
		"smull v24.4s, v7.4h, v12.4h \n\t"
		"smull2 v25.4s, v7.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[4], w6 \n\t"

//7,5
		"smull v24.4s, v7.4h, v13.4h \n\t"
		"smull2 v25.4s, v7.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[5], w6 \n\t"

//7,6
		"smull v24.4s, v7.4h, v14.4h \n\t"
		"smull2 v25.4s, v7.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[6], w6 \n\t"

//7,7
		"smull v24.4s, v7.4h, v15.4h \n\t"
		"smull2 v25.4s, v7.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[7], w6 \n\t"
//*

		"mov w4, w5 \n\t"
		"mov v8.16b, v16.16b \n\t"
		"mov v9.16b, v17.16b \n\t"
		"mov v10.16b, v18.16b \n\t"
		"mov v11.16b, v19.16b \n\t"
		"mov v12.16b, v20.16b \n\t"
		"mov v13.16b, v21.16b \n\t"
		"mov v14.16b, v22.16b \n\t"
		"mov v15.16b, v23.16b \n\t"
		//"mov v8.h[0],w5 \n\t"

//*

//data:0,0
        	"smull v24.4s, v0.4h, v8.4h \n\t"
		"smull2 v25.4s, v0.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[0], w6 \n\t"

//data:1,0
		"smull v24.4s, v0.4h, v9.4h \n\t"
		"smull2 v25.4s, v0.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[0], w6 \n\t"
//data:2,0
		"smull v24.4s, v0.4h, v10.4h \n\t"
		"smull2 v25.4s, v0.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[0], w6 \n\t"

//data:3,0
		"smull v24.4s, v0.4h, v11.4h \n\t"
		"smull2 v25.4s, v0.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[0], w6 \n\t"

//data:4,0
		"smull v24.4s, v0.4h, v12.4h \n\t"
		"smull2 v25.4s, v0.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[0], w6 \n\t"

//data:5,0
		"smull v24.4s, v0.4h, v13.4h \n\t"
		"smull2 v25.4s, v0.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[0], w6 \n\t"

//data:6,0
		"smull v24.4s, v0.4h, v14.4h \n\t"
		"smull2 v25.4s, v0.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[0], w6 \n\t"

//data:7,0
		"smull v24.4s, v0.4h, v15.4h \n\t"
		"smull2 v25.4s, v0.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[0], w6 \n\t"

//data:0,1
        	"smull v24.4s, v1.4h, v8.4h \n\t"
		"smull2 v25.4s, v1.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[1], w6 \n\t"
//data:1,1
		"smull v24.4s, v1.4h, v9.4h \n\t"
		"smull2 v25.4s, v1.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[1], w6 \n\t"
//data:2,1
		"smull v24.4s, v1.4h, v10.4h \n\t"
		"smull2 v25.4s, v1.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[1], w6 \n\t"

//data:3,1
		"smull v24.4s, v1.4h, v11.4h \n\t"
		"smull2 v25.4s, v1.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[1], w6 \n\t"

//data:4,1
		"smull v24.4s, v1.4h, v12.4h \n\t"
		"smull2 v25.4s, v1.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[1], w6 \n\t"

//data:5,1
		"smull v24.4s, v1.4h, v13.4h \n\t"
		"smull2 v25.4s, v1.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[1], w6 \n\t"

//data:6,1
		"smull v24.4s, v1.4h, v14.4h \n\t"
		"smull2 v25.4s, v1.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[1], w6 \n\t"

//data:7,1
		"smull v24.4s, v1.4h, v15.4h \n\t"
		"smull2 v25.4s, v1.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[1], w6 \n\t"

//data:0,2
        	"smull v24.4s, v2.4h, v8.4h \n\t"
		"smull2 v25.4s, v2.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[2], w6 \n\t"
//data:1,2
		"smull v24.4s, v2.4h, v9.4h \n\t"
		"smull2 v25.4s, v2.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[2], w6 \n\t"
//data:2,2
		"smull v24.4s, v2.4h, v10.4h \n\t"
		"smull2 v25.4s, v2.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[2], w6 \n\t"

//data:3,2
		"smull v24.4s, v2.4h, v11.4h \n\t"
		"smull2 v25.4s, v2.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[2], w6 \n\t"

//data:4,2
		"smull v24.4s, v2.4h, v12.4h \n\t"
		"smull2 v25.4s, v2.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[2], w6 \n\t"

//data:5,2
		"smull v24.4s, v2.4h, v13.4h \n\t"
		"smull2 v25.4s, v2.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[2], w6 \n\t"

//data:6,2
		"smull v24.4s, v2.4h, v14.4h \n\t"
		"smull2 v25.4s, v2.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[2], w6 \n\t"

//data:7,2
		"smull v24.4s, v2.4h, v15.4h \n\t"
		"smull2 v25.4s, v2.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[2], w6 \n\t"

//data:0,3
        	"smull v24.4s, v3.4h, v8.4h \n\t"
		"smull2 v25.4s, v3.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[3], w6 \n\t"
//data:1,3
		"smull v24.4s, v3.4h, v9.4h \n\t"
		"smull2 v25.4s, v3.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[3], w6 \n\t"
//data:2,3
		"smull v24.4s, v3.4h, v10.4h \n\t"
		"smull2 v25.4s, v3.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[3], w6 \n\t"

//data:3,3
		"smull v24.4s, v3.4h, v11.4h \n\t"
		"smull2 v25.4s, v3.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[3], w6 \n\t"

//data:4,3
		"smull v24.4s, v3.4h, v12.4h \n\t"
		"smull2 v25.4s, v3.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[3], w6 \n\t"

//data:5,3
		"smull v24.4s, v3.4h, v13.4h \n\t"
		"smull2 v25.4s, v3.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[3], w6 \n\t"

//data:6,3
		"smull v24.4s, v3.4h, v14.4h \n\t"
		"smull2 v25.4s, v3.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[3], w6 \n\t"

//data:7,3
		"smull v24.4s, v3.4h, v15.4h \n\t"
		"smull2 v25.4s, v3.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[3], w6 \n\t"

//data:0,4
        	"smull v24.4s, v4.4h, v8.4h \n\t"
		"smull2 v25.4s, v4.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[4], w6 \n\t"
//data:1,4
		"smull v24.4s, v4.4h, v9.4h \n\t"
		"smull2 v25.4s, v4.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[4], w6 \n\t"
//data:2,4
		"smull v24.4s, v4.4h, v10.4h \n\t"
		"smull2 v25.4s, v4.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[4], w6 \n\t"

//data:3,4
		"smull v24.4s, v4.4h, v11.4h \n\t"
		"smull2 v25.4s, v4.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[4], w6 \n\t"

//data:4,4
		"smull v24.4s, v4.4h, v12.4h \n\t"
		"smull2 v25.4s, v4.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[4], w6 \n\t"

//data:5,4
		"smull v24.4s, v4.4h, v13.4h \n\t"
		"smull2 v25.4s, v4.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[4], w6 \n\t"

//data:6,4
		"smull v24.4s, v4.4h, v14.4h \n\t"
		"smull2 v25.4s, v4.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[4], w6 \n\t"

//data:7,4
		"smull v24.4s, v4.4h, v15.4h \n\t"
		"smull2 v25.4s, v4.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[4], w6 \n\t"

//data:0,5
        	"smull v24.4s, v5.4h, v8.4h \n\t"
		"smull2 v25.4s, v5.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[5], w6 \n\t"
//data:1,5
		"smull v24.4s, v5.4h, v9.4h \n\t"
		"smull2 v25.4s, v5.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[5], w6 \n\t"
//data:2,5
		"smull v24.4s, v5.4h, v10.4h \n\t"
		"smull2 v25.4s, v5.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[5], w6 \n\t"

//data:3,5
		"smull v24.4s, v5.4h, v11.4h \n\t"
		"smull2 v25.4s, v5.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[5], w6 \n\t"

//data:4,5
		"smull v24.4s, v5.4h, v12.4h \n\t"
		"smull2 v25.4s, v5.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[5], w6 \n\t"

//data:5,5
		"smull v24.4s, v5.4h, v13.4h \n\t"
		"smull2 v25.4s, v5.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[5], w6 \n\t"

//data:6,5
		"smull v24.4s, v5.4h, v14.4h \n\t"
		"smull2 v25.4s, v5.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[5], w6 \n\t"

//data:7,5
		"smull v24.4s, v5.4h, v15.4h \n\t"
		"smull2 v25.4s, v5.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[5], w6 \n\t"

//data:0,6
        	"smull v24.4s, v6.4h, v8.4h \n\t"
		"smull2 v25.4s, v6.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[6], w6 \n\t"
//data:1,6
		"smull v24.4s, v6.4h, v9.4h \n\t"
		"smull2 v25.4s, v6.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[6], w6 \n\t"
//data:2,6
		"smull v24.4s, v6.4h, v10.4h \n\t"
		"smull2 v25.4s, v6.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[6], w6 \n\t"

//data:3,6
		"smull v24.4s, v6.4h, v11.4h \n\t"
		"smull2 v25.4s, v6.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[6], w6 \n\t"

//data:4,6
		"smull v24.4s, v6.4h, v12.4h \n\t"
		"smull2 v25.4s, v6.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[6], w6 \n\t"

//data:5,6
		"smull v24.4s, v6.4h, v13.4h \n\t"
		"smull2 v25.4s, v6.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[6], w6 \n\t"

//data:6,6
		"smull v24.4s, v6.4h, v14.4h \n\t"
		"smull2 v25.4s, v6.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[6], w6 \n\t"

//data:7,6
		"smull v24.4s, v6.4h, v15.4h \n\t"
		"smull2 v25.4s, v6.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[6], w6 \n\t"

//data:0,7
        	"smull v24.4s, v7.4h, v8.4h \n\t"
		"smull2 v25.4s, v7.8h, v8.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v16.h[7], w6 \n\t"
//data:1,7
		"smull v24.4s, v7.4h, v9.4h \n\t"
		"smull2 v25.4s, v7.8h, v9.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v17.h[7], w6 \n\t"
//data:2,7
		"smull v24.4s, v7.4h, v10.4h \n\t"
		"smull2 v25.4s, v7.8h, v10.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v18.h[7], w6 \n\t"

//data:3,7
		"smull v24.4s, v7.4h, v11.4h \n\t"
		"smull2 v25.4s, v7.8h, v11.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v19.h[7], w6 \n\t"

//data:4,7
		"smull v24.4s, v7.4h, v12.4h \n\t"
		"smull2 v25.4s, v7.8h, v12.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v20.h[7], w6 \n\t"

//data:5,7
		"smull v24.4s, v7.4h, v13.4h \n\t"
		"smull2 v25.4s, v7.8h, v13.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v21.h[7], w6 \n\t"

//data:6,7
		"smull v24.4s, v7.4h, v14.4h \n\t"
		"smull2 v25.4s, v7.8h, v14.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v22.h[7], w6 \n\t"

//data:7,7
		"smull v24.4s, v7.4h, v15.4h \n\t"
		"smull2 v25.4s, v7.8h, v15.8h \n\t"
		"add v24.4s, v24.4s, v25.4s \n\t"
		"addv s24, v24.4s \n\t"
		//"mov x4, %3 \n\t"
		"mov w6, v24.s[0] \n\t"
		"asr w6, w6, w4			\n\t"
		"mov v23.h[7], w6 \n\t"
//*/
		//"mov w4,w5 \n\t"
		//"mov v16.h[0],w4 \n\t"
		//"mov v16.h[1],w5 \n\t"
		"st1 {v16.8h, v17.8h, v18.8h, v19.8h}, [%2]     \n\t"
		"st1 {v20.8h, v21.8h, v22.8h, v23.8h}, [x3]     \n\t"

//		"st1 {v8.8h, v9.8h, v10.8h, v11.8h}, [%2]     \n\t"
//		"st1 {v12.8h, v13.8h, v14.8h, v15.8h}, [x3]     \n\t"
		//t4 {v0.8h, v1.8h, v2.8h, v3.8h}, [%0]     \n\t"
        	: 
		"+r"(a),   //%0
	       	"+r"(b),   //%1
          	"+r"(c),    //%2
		"+r"(d),    //%3
		"+r"(e)    //%4
        	:
        	: "cc", "memory", "x1", "x2", "x3", "w4", "w5", "w6", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7","v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23"
	);
}//asm

