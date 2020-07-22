/*
 * File:		lpt.h
 * Purpose:		Low Power Timer header file
 *
 */

#ifndef __lptmr_H__
#define __lptmr_H__

#include "common.h"

//Pin Select constants for CSR[TPS]
#define HSCMP    0x0
#define LPTMR_ALT1 0x1
#define LPTMR_ALT2 0x2
#define LPTMR_ALT3 0x3

#define LPTMR_CLK_SRC_MCGIREF     0
#define LPTMR_CLK_SRC_LPO_1K      1
#define LPTMR_CLK_SRC_EXTREF_32K  2
#define LPTMR_CLK_SRC_EXTREF      3


//CSR[TPP] constants
#define RISING 0
#define FALLING LPTMR_CSR_TPP_MASK

uint16 get_counter_value();
void lptmr_clear_registers();

void lptmr_time_counter();
void lptmr_prescale();

void lptmr_internal_ref_input();
void lptmr_lpo_input();
void lptmr_external_32khz_input();
void lptmr_external_clk_input();

void lptmr_interrupt();

void lptmr_pulse_counter(char pin_select);

#endif /* __UART_H__ */