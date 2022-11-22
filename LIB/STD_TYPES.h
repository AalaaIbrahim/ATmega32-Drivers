
#ifndef LIB_STD_TYPES_H_
#define LIB_STD_TYPES_H_

typedef unsigned char 			u8 ;
typedef unsigned short int		u16;
typedef unsigned long int		u32;

typedef signed char 			s8 ;
typedef signed short int		s16;
typedef signed long int			s32;

typedef float                   f32;
typedef double                  f64;

typedef enum {OK, NOK, NULL_PTR, BUSY_FUNCTION}ErrorStatus;

typedef enum {ENABLE = 1, DISABLE}State;

#define 	NULL				0


#endif
