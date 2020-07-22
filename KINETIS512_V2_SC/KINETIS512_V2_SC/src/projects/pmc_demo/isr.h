/******************************************************************************
* File:    isr.h
* Purpose: Define interrupt service routines referenced by the vector table.
* Note: Only "vectors.c" should include this header file.
******************************************************************************/

#ifndef __ISR_H
#define __ISR_H 1


extern void port_a_isr(void);
extern void llwu_isr(void);

#undef VECTOR_103
#define VECTOR_103 port_a_isr


#undef VECTOR_037
#define VECTOR_037 llwu_isr


#endif  //__ISR_H

/* End of "isr.h" */
