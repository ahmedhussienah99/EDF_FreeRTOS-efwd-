/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <lpc21xx.h>
#include "GPIO.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION		1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			1
#define configCPU_CLOCK_HZ			( ( unsigned long ) 60000000 )	/* =12.0MHz xtal multiplied by 5 using the PLL. */
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 90 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) 13 * 1024 )
#define configMAX_TASK_NAME_LEN		( 8 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		0
#define configIDLE_SHOULD_YIELD		1
#define configQUEUE_REGISTRY_SIZE 	0
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configUSE_APPLICATION_TASK_TAG   1
#define configUSE_EDF_SCHEDULER 1

extern int Button_1_Monitor_InTime,  Button_1_Monitor_OutTime, Button_1_Monitor_TotalTime;
extern int Button_2_Monitor_InTime,  Button_2_Monitor_OutTime,  Button_2_Monitor_TotalTime;
extern int Periodic_Transmitter_InTime, Periodic_Transmitter_OutTime, Periodic_Transmitter_TotalTime;
extern int Uart_Receiver_InTime,    Uart_Receiver_OutTime,     Uart_Receiver_TotalTime;
extern int Load_1_Simulation_InTime,    Load_1_Simulation_OutTime,   Load_1_Simulation_TotalTime;
extern int Load_2_Simulation_InTime,    Load_2_Simulation_OutTime,    Load_2_Simulation_TotalTime;
extern int system_Time;
extern int cpu_Load;

#define traceTASK_SWITCHED_OUT()	do{\
		if ((int)pxCurrentTCB->pxTaskTag == 1)\
		{\
						GPIO_write (PORT_0, PIN1, PIN_IS_LOW);\
	         Button_1_Monitor_OutTime = T1TC;\
	         Button_1_Monitor_TotalTime += (Button_1_Monitor_OutTime - Button_1_Monitor_InTime);\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 2)\
		{\
			GPIO_write (PORT_0, PIN2, PIN_IS_LOW);\
			Button_2_Monitor_OutTime = T1TC;\
			Button_2_Monitor_TotalTime += (Button_2_Monitor_OutTime - Button_2_Monitor_InTime);\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 3)\
		{\
			GPIO_write (PORT_0, PIN3, PIN_IS_LOW);\
			Periodic_Transmitter_OutTime = T1TC;\
			Periodic_Transmitter_TotalTime += (Periodic_Transmitter_OutTime - Periodic_Transmitter_InTime);\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 4)\
		{\
			GPIO_write (PORT_0, PIN4, PIN_IS_LOW);\
			Uart_Receiver_OutTime = T1TC;\
			Uart_Receiver_TotalTime += (Uart_Receiver_OutTime - Uart_Receiver_InTime);\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 5)\
		{\
			GPIO_write (PORT_0, PIN5, PIN_IS_LOW);\
			Load_1_Simulation_OutTime = T1TC;\
			Load_1_Simulation_TotalTime += (Load_1_Simulation_OutTime - Load_1_Simulation_InTime);\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 6)\
		{\
			GPIO_write (PORT_0, PIN6, PIN_IS_LOW);\
			Load_2_Simulation_OutTime = T1TC;\
			Load_2_Simulation_TotalTime += (Load_2_Simulation_OutTime - Load_2_Simulation_InTime);\
		}\
		system_Time = T1TC;\
	cpu_Load =((Button_1_Monitor_TotalTime+Button_2_Monitor_TotalTime+Periodic_Transmitter_TotalTime+Uart_Receiver_TotalTime+Load_1_Simulation_TotalTime+Load_2_Simulation_TotalTime)/(float)system_Time ) * 100;\
	}while(0)

	
#define traceTASK_SWITCHED_IN()	  do{\
			if ((int)pxCurrentTCB->pxTaskTag == 1)\
		{\
			 GPIO_write (PORT_0, PIN1, PIN_IS_HIGH);\
	     Button_1_Monitor_InTime = T1TC;\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 2)\
		{\
			GPIO_write (PORT_0, PIN2, PIN_IS_HIGH);\
			Button_2_Monitor_InTime = T1TC;\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 3)\
		{\
			GPIO_write (PORT_0, PIN3, PIN_IS_HIGH);\
			Periodic_Transmitter_InTime = T1TC;\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 4)\
		{\
			GPIO_write (PORT_0, PIN4, PIN_IS_HIGH);\
			Uart_Receiver_InTime = T1TC;\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 5)\
		{\
			GPIO_write (PORT_0, PIN5, PIN_IS_HIGH);\
			Load_1_Simulation_InTime = T1TC;\
		}\
		else if ((int)pxCurrentTCB->pxTaskTag == 6)\
		{\
			GPIO_write (PORT_0, PIN6, PIN_IS_HIGH);\
			Load_2_Simulation_InTime = T1TC;\
		}\
	}while(0)

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1


#endif /* FREERTOS_CONFIG_H */
