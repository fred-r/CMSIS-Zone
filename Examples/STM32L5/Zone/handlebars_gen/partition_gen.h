/**************************************************************************//**
 * @file     partition_gen.h
 * @brief    CMSIS-CORE Initial Setup for Secure / Non-Secure Zones for STM32L5xx Device
 * @version  V1.0.0      (FreeMarker generated)
 * @date     ${aDateTime?date} ${aDateTime?time}
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PARTITION_GEN_H
#define PARTITION_GEN_H

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <h>Initialize Security Attribution Unit (SAU) Address Regions
// <i>SAU configuration specifies regions to be one of:
// <i> - Secure and Non-Secure Callable
// <i> - Non-Secure
// <i>Note: All memory regions not configured by SAU are Secure
*/
#define SAU_REGIONS_MAX   8 	/* Max. number of SAU regions */

/*
//   <e>Initialize SAU Region 0
//   <i> Setup SAU Region  0 memory attributes
*/
#define SAU_INIT_REGION0       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START0       0x08040000      /* start address of SAU region 0 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END0       0x0807FFFF      /* end address of SAU region 0 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC0       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 1
//   <i> Setup SAU Region  1 memory attributes
*/
#define SAU_INIT_REGION1       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START1       0x0C03E000      /* start address of SAU region 1 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END1       0x0C03FFFF      /* end address of SAU region 1 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC1       1
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 2
//   <i> Setup SAU Region  2 memory attributes
*/
#define SAU_INIT_REGION2       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START2       0x20000000      /* start address of SAU region 2 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END2       0x2001FFFF      /* end address of SAU region 2 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC2       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 3
//   <i> Setup SAU Region  3 memory attributes
*/
#define SAU_INIT_REGION3       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START3       0x40000000      /* start address of SAU region 3 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END3       0x4FFFFFFF      /* end address of SAU region 3 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC3       0
/*
//   </e>
*/
/*
//   <e>Initialize SAU Region 4
//   <i> Setup SAU Region  4 memory attributes
*/
#define SAU_INIT_REGION4       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START4       0x00000000      /* start address of SAU region 4 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END4       0x00000000      /* end address of SAU region 4 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC4       0
/*
//   </e>
*/    
/*
//   <e>Initialize SAU Region 5
//   <i> Setup SAU Region  5 memory attributes
*/
#define SAU_INIT_REGION5       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START5       0x00000000      /* start address of SAU region 5 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END5       0x00000000      /* end address of SAU region 5 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC5       0
/*
//   </e>
*/    
/*
//   <e>Initialize SAU Region 6
//   <i> Setup SAU Region  6 memory attributes
*/
#define SAU_INIT_REGION6       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START6       0x00000000      /* start address of SAU region 6 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END6       0x00000000      /* end address of SAU region 6 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC6       0
/*
//   </e>
*/    
/*
//   <e>Initialize SAU Region 7
//   <i> Setup SAU Region  7 memory attributes
*/
#define SAU_INIT_REGION7       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START7       0x00000000      /* start address of SAU region 7 */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END7       0x00000000      /* end address of SAU region 7 */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC7       0
/*
//   </e>
*/    

/*
// </h>
*/

/*
// <h>Setup Interrupt Target
*/


/*
//   <e>Initialize ITNS 0 (Interrupts 0..31)
*/
#define NVIC_INIT_ITNS0    0

/*
// Interrupts 0..31
//   <o.029>  Interrupt   029: DMA1_Channel1 <0=> Secure state <1=> Non-Secure state
//   <o.030>  Interrupt   030: DMA1_Channel2 <0=> Secure state <1=> Non-Secure state
//   <o.031>  Interrupt   031: DMA1_Channel3 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS0_VAL      0x00000000

/*
//   </e>
*/


/*
//   <e>Initialize ITNS 1 (Interrupts 32..63)
*/
#define NVIC_INIT_ITNS1    1

/*
// Interrupts 32..63
//   <o.032>  Interrupt   032: DMA1_Channel4 <0=> Secure state <1=> Non-Secure state
//   <o.033>  Interrupt   033: DMA1_Channel5 <0=> Secure state <1=> Non-Secure state
//   <o.034>  Interrupt   034: DMA1_Channel6 <0=> Secure state <1=> Non-Secure state
//   <o.035>  Interrupt   035: DMA1_Channel7 <0=> Secure state <1=> Non-Secure state
//   <o.036>  Interrupt   036: DMA1_Channel8 <0=> Secure state <1=> Non-Secure state
//   <o.037>  Interrupt   037: ADC1_2 <0=> Secure state <1=> Non-Secure state
//   <o.039>  Interrupt   039: FDCAN1_IT0 <0=> Secure state <1=> Non-Secure state
//   <o.040>  Interrupt   040: FDCAN1_IT1 <0=> Secure state <1=> Non-Secure state
//   <o.041>  Interrupt   041: TIM1_BRK <0=> Secure state <1=> Non-Secure state
//   <o.042>  Interrupt   042: TIM1_UP <0=> Secure state <1=> Non-Secure state
//   <o.043>  Interrupt   043: TIM1_TRG_COM <0=> Secure state <1=> Non-Secure state
//   <o.044>  Interrupt   044: TIM1_CC <0=> Secure state <1=> Non-Secure state
//   <o.045>  Interrupt   045: TIM2 <0=> Secure state <1=> Non-Secure state
//   <o.046>  Interrupt   046: TIM3 <0=> Secure state <1=> Non-Secure state
//   <o.047>  Interrupt   047: TIM4 <0=> Secure state <1=> Non-Secure state
//   <o.048>  Interrupt   048: TIM5 <0=> Secure state <1=> Non-Secure state
//   <o.049>  Interrupt   049: TIM6 <0=> Secure state <1=> Non-Secure state
//   <o.050>  Interrupt   050: TIM7 <0=> Secure state <1=> Non-Secure state
//   <o.051>  Interrupt   051: TIM8_BRK <0=> Secure state <1=> Non-Secure state
//   <o.052>  Interrupt   052: TIM8_UP <0=> Secure state <1=> Non-Secure state
//   <o.053>  Interrupt   053: TIM8_TRG_COM <0=> Secure state <1=> Non-Secure state
//   <o.054>  Interrupt   054: TIM8_CC <0=> Secure state <1=> Non-Secure state
//   <o.055>  Interrupt   055: I2C1_EV <0=> Secure state <1=> Non-Secure state
//   <o.056>  Interrupt   056: I2C1_ER <0=> Secure state <1=> Non-Secure state
//   <o.057>  Interrupt   057: I2C2_EV <0=> Secure state <1=> Non-Secure state
//   <o.058>  Interrupt   058: I2C2_ER <0=> Secure state <1=> Non-Secure state
//   <o.059>  Interrupt   059: SPI1 <0=> Secure state <1=> Non-Secure state
//   <o.060>  Interrupt   060: SPI2 <0=> Secure state <1=> Non-Secure state
//   <o.061>  Interrupt   061: USART1 <0=> Secure state <1=> Non-Secure state
//   <o.062>  Interrupt   062: USART2 <0=> Secure state <1=> Non-Secure state
//   <o.063>  Interrupt   063: USART3 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS1_VAL      0x40008020

/*
//   </e>
*/


/*
//   <e>Initialize ITNS 2 (Interrupts 64..95)
*/
#define NVIC_INIT_ITNS2    0

/*
// Interrupts 64..95
//   <o.064>  Interrupt   064: UART4 <0=> Secure state <1=> Non-Secure state
//   <o.065>  Interrupt   065: UART5 <0=> Secure state <1=> Non-Secure state
//   <o.066>  Interrupt   066: LPUART1 <0=> Secure state <1=> Non-Secure state
//   <o.067>  Interrupt   067: LPTIM1 <0=> Secure state <1=> Non-Secure state
//   <o.068>  Interrupt   068: LPTIM2 <0=> Secure state <1=> Non-Secure state
//   <o.069>  Interrupt   069: TIM15 <0=> Secure state <1=> Non-Secure state
//   <o.070>  Interrupt   070: TIM16 <0=> Secure state <1=> Non-Secure state
//   <o.071>  Interrupt   071: TIM17 <0=> Secure state <1=> Non-Secure state
//   <o.072>  Interrupt   072: COMP <0=> Secure state <1=> Non-Secure state
//   <o.076>  Interrupt   076: OCTOSPI1 <0=> Secure state <1=> Non-Secure state
//   <o.080>  Interrupt   080: DMA2_CH1 <0=> Secure state <1=> Non-Secure state
//   <o.081>  Interrupt   081: DMA2_CH2 <0=> Secure state <1=> Non-Secure state
//   <o.082>  Interrupt   082: DMA2_CH3 <0=> Secure state <1=> Non-Secure state
//   <o.083>  Interrupt   083: DMA2_CH4 <0=> Secure state <1=> Non-Secure state
//   <o.084>  Interrupt   084: DMA2_CH5 <0=> Secure state <1=> Non-Secure state
//   <o.085>  Interrupt   085: DMA2_CH6 <0=> Secure state <1=> Non-Secure state
//   <o.086>  Interrupt   086: DMA2_CH7 <0=> Secure state <1=> Non-Secure state
//   <o.087>  Interrupt   087: DMA2_CH8 <0=> Secure state <1=> Non-Secure state
//   <o.088>  Interrupt   088: I2C3_EV <0=> Secure state <1=> Non-Secure state
//   <o.089>  Interrupt   089: I2C3_ER <0=> Secure state <1=> Non-Secure state
//   <o.090>  Interrupt   090: SAI1 <0=> Secure state <1=> Non-Secure state
//   <o.091>  Interrupt   091: SAI2 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS2_VAL      0x00000000

/*
//   </e>
*/


/*
//   <e>Initialize ITNS 3 (Interrupts 96..127)
*/
#define NVIC_INIT_ITNS3    0

/*
// Interrupts 96..127
//   <o.099>  Interrupt   099: SPI3 <0=> Secure state <1=> Non-Secure state
//   <o.100>  Interrupt   100: I2C4_ER <0=> Secure state <1=> Non-Secure state
//   <o.101>  Interrupt   101: I2C4_EV <0=> Secure state <1=> Non-Secure state
//   <o.102>  Interrupt   102: DFSDM1_FLT0 <0=> Secure state <1=> Non-Secure state
//   <o.103>  Interrupt   103: DFSDM1_FLT1 <0=> Secure state <1=> Non-Secure state
//   <o.104>  Interrupt   104: DFSDM1_FLT2 <0=> Secure state <1=> Non-Secure state
//   <o.105>  Interrupt   105: DFSDM1_FLT3 <0=> Secure state <1=> Non-Secure state
//   <o.106>  Interrupt   106: UCPD1 <0=> Secure state <1=> Non-Secure state
*/
#define NVIC_INIT_ITNS3_VAL      0x00000000

/*
//   </e>
*/

/*
// </h>
*/

#endif  /* PARTITION_GEN_H */