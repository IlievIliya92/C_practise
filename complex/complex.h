#ifndef _COMPLEX_
#define _COMPLEX_

#include <math.h>

struct complex {
	double Re;
	double Im;
};
typedef struct complex complex;

#define Re(Z) ((Z).Re)
#define Im(Z) ((Z).Im)

#define MOV(A, B) do { \
	Re(A) = Re(B); \
	Im(A) = Im(B); \
} while (0)

#define SCALE(A, C) do { \
	Re(A) *= (C); \
	Im(A) *= (C); \
} while (0)

#define LEN(Z) (Re(Z) * Re(Z) + Im(Z) * Im(Z))

#define CONJ(Z) do { \
	Im(Z) = -Im(Z); \
} while (0)

#define ARG(Z) (atan2(Im(Z), Re(Z)))

#define ADD2(A, B) do { \
	(A).Re += (B).Re; \
	(A).Im += (B).Im; \
} while (0)

#define ADD3(C, A, B) do { \
	(C).Re = (A).Re + (B).Re; \
	(C).Im = (A).Im + (B).Im; \
} while (0)

#define SUB2(A, B) do { \
	(A).Re -= (B).Re; \
	(A).Im -= (B).Im; \
} while (0)

#define SUB3(C, A, B) do { \
	(C).Re = (A).Re - (B).Re; \
	(C).Im = (A).Im - (B).Im; \
} while (0)

#define MUL2(A, B) do { \
	double __t_Re, __t_Im; \
	__t_Re = Re(A) * Re(B) - Im(A) * Im(B); \
	__t_Im = Re(A) * Im(B) + Im(B) * Re(A); \
	Re(A) = __t_Re; \
	Im(A) = __t_Im; \
} while (0)

#define MUL3(C, A, B) do { \
	Re(C) = Re(A) * Re(B) - Im(A) * Im(B); \
	Im(C) = Re(A) * Im(B) + Im(B) * Re(A); \
} while (0)

#define DIV2(A, B) do { \
	complex __conj_B; \
	double __scale; \
	__scale = 1.0 / LEN(B); \
	MOV(__conj_B, B); \
	CONJ(__conj_B); \
	MUL2(__conj_B, A); \
	SCALE(__conj_B, __scale); \
	MOV(A, __conj_B); \
} while (0)

#define DIV3(C, A, B) do { \
	double __scale; \
	__scale = 1.0 / LEN(B); \
	MOV(C, B); \
	CONJ(C); \
	MUL2(C, A); \
	SCALE(C, __scale); \
} while (0)

#define EULER(Z, R, Arg) do { \
	Re(Z) = cos((Arg)); \
	Im(Z) = sin((Arg)); \
	SCALE(Z, R); \
} while (0)

#endif
