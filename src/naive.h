#ifndef _NAIVE_H_
#define _NAIVE_H_

#ifdef _NAIVE_VERSION_

#define CALC_ADD(TOP, L, R) TOP = L + R
#define CALC_SUB(TOP, L, R) TOP = L - R
#define CALC_MUL(TOP, L, R) TOP = L * R
#define CALC_DIV(TOP, L, R) TOP = L / R
#define CALC_ABS(TOP, ARG) TOP = fabs(ARG)
#define CALC_NEG(TOP, ARG) TOP = -ARG
#define CALC_NUM(TOP, ARG) TOP = ARG
#define CALC_RESULT(TOP) TOP

#endif /* _NAIVE_VERSION_ */

#endif /* _NAIVE_H_ */