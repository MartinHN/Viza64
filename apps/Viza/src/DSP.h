//
//  DSP.h
//  ViZa
//
//  Created by martin hermant on 31/03/15.
//
//

#ifndef ViZa_DSP_h
#define ViZa_DSP_h
#include "ofConstants.h"

static inline float
fastpow2 (float p)
{
    float offset = (p < 0) ? 1.0f : 0.0f;
    float clipp = (p < -126) ? -126.0f : p;
    int w = clipp;
    float z = clipp - w + offset;
    union { uint32_t i; float f; } v = { static_cast<uint32_t> ( (1 << 23) * (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f * z) ) };
    
    return v.f;
}

static inline float
fastexp (float p)
{
    return fastpow2 (1.442695040f * p);
}


#define DSP_ACCELERATE 1


#if !DSP_ACCELERATE
#include <eigen3/Eigen/Core>
#endif

// wierd variable name for not colliding with existing ones
#define P_DSP_ qwertasdfg


#define SQRT std::sqrt



#if DSP_ACCELERATE & defined(TARGET_OSX)
#include <Accelerate/Accelerate.h>

#define DSP_normalize(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_Mean,__vDSP_StandardDeviation,__vDSP_N) \
vDSP_normalize(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_Mean,__vDSP_StandardDeviation,__vDSP_N)


#define DSP_vspdp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N) \
vDSP_vspdp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N)

#define DSP_vdpsp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N) \
vDSP_vdpsp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N)

#define DSP_minv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N) \
vDSP_minv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N)

#define DSP_maxv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N) \
vDSP_maxv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N)


#define DSP_vsadd(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N) \
vDSP_vsadd(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N)


#define DSP_vsmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N) \
vDSP_vsmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N)


#define DSP_vsma(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_D,__vDSP_ID,__vDSP_N) \
vDSP_vsma(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_D,__vDSP_ID,__vDSP_N)


#define DSP_vsub(__vDSP_B,__vDSP_IB,__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC) \
vDSP_vsub(__vDSP_B,__vDSP_IB,__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC)

#define DSP_vsmsa(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_D,__vDSP_ID,__vDSP_N) \
vDSP_vsmsa(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_D,__vDSP_ID,__vDSP_N)

#define DSP_mmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_IC,__vDSP_M,__vDSP_N,__vDSP_P) \
vDSP_mmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_IC,__vDSP_M,__vDSP_N,__vDSP_P)

#define DSP_dotprD(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_N) \
vDSP_dotprD(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_N)



#else

#include <Accelerate/Accelerate.h>

#define DSP_normalize(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_Mean,__vDSP_StandardDeviation,__vDSP_N) \
*__vDSP_Mean=0 ; *__vDSP_StandardDeviation=0; \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){ \
*__vDSP_Mean+= *(__vDSP_A + P_DSP_I*__vDSP_IA);*__vDSP_StandardDeviation+= *(__vDSP_A + P_DSP_I*__vDSP_IA ) * *(__vDSP_A + P_DSP_I*__vDSP_IA ) ;} \
*__vDSP_Mean/=__vDSP_N; *__vDSP_StandardDeviation=SQRT(*__vDSP_StandardDeviation/__vDSP_N - *__vDSP_Mean* *__vDSP_Mean);\
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=(*(__vDSP_A+ P_DSP_I*__vDSP_IA)-*__vDSP_Mean)/ *__vDSP_StandardDeviation;} \



#define DSP_vspdp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA);}

#define DSP_vdpsp(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA);}

#define DSP_minv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N) \
vDSP_minv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N)

#define DSP_maxv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N) \
vDSP_maxv(__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_N)


#define DSP_vsadd(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA) + *__vDSP_B;}


#define DSP_vsmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA) * *__vDSP_B;}


#define DSP_vsma(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_IC,__vDSP_D,__vDSP_ID,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA) * *__vDSP_B + *(__vDSP_C+ P_DSP_I*__vDSP_IC) ;}


#define DSP_vsub(__vDSP_B,__vDSP_IB,__vDSP_A,__vDSP_IA,__vDSP_C,__vDSP_IC) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_C + P_DSP_I*__vDSP_IC)=*(__vDSP_A+ P_DSP_I*__vDSP_IA) - *(__vDSP_C+ P_DSP_I*__vDSP_IC) ;}

#define DSP_vsmsa(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_C,__vDSP_D,__vDSP_ID,__vDSP_N) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_N; P_DSP_I++){*(__vDSP_D + P_DSP_I*__vDSP_ID)=*(__vDSP_A+ P_DSP_I*__vDSP_IA) * *__vDSP_B + *__vDSP_C ;}

/*  Maps:
 
 A is regarded as a two-dimensional matrix with dimemnsions [M][P]
 and stride IA.  B is regarded as a two-dimensional matrix with
 dimemnsions [P][N] and stride IB.  C is regarded as a
 two-dimensional matrix with dimemnsions [M][N] and stride IC.
 
 Pseudocode:     Memory:
 A[m][p]         A[(m*P+p)*IA]
 B[p][n]         B[(p*N+n)*IB]
 C[m][n]         C[(m*N+n)*IC]
 
 These compute:
 
 for (m = 0; m < M; ++m)
 for (n = 0; n < N; ++n)
 C[m][n] = sum(A[m][p] * B[p][n], 0 <= p < P);
 
 int P_DSP_SUM= 0 ; \
 *(__vDSP_C + __vDSP_IC*(P_DSP_I*__vDSP_N + P_DSP_J)) = P_DSP_SUM; \

 */
#define DSP_mmul(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_IC,__vDSP_M,__vDSP_N,__vDSP_P) \
for( int P_DSP_I = 0 ; P_DSP_I < __vDSP_M;P_DSP_I++){for( int P_DSP_J = 0 ; P_DSP_J < __vDSP_N;P_DSP_J++){ \
*(__vDSP_C + __vDSP_IC*(P_DSP_I*__vDSP_N + P_DSP_J)) = 0;\
for( int P_DSP_K = 0 ; P_DSP_K < __vDSP_P;P_DSP_K++){  *(__vDSP_C + __vDSP_IC*(P_DSP_I*__vDSP_N + P_DSP_J))+= *(__vDSP_A + __vDSP_IA*(P_DSP_I*__vDSP_P+P_DSP_K)) * (*(__vDSP_B + __vDSP_IB*(P_DSP_K*__vDSP_N+P_DSP_J))); } \
}}




#define DSP_dotprD(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_N) \
vDSP_dotprD(__vDSP_A,__vDSP_IA,__vDSP_B,__vDSP_IB,__vDSP_C,__vDSP_N)






#endif




#endif
