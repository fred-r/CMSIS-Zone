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
{{setVar "MaxSauregions" fzone.system.processor.DnumSauRegions ~}}
#define SAU_REGIONS_MAX   {{MaxSauregions}} 	/* Max. number of SAU regions */

{{setVar "ConfiguredSauRegions" fzone.system.sau.length ~}}
{{#each fzone.system.sau}}
/*
//   <e>Initialize SAU Region {{@index}}
//   <i> Setup SAU Region  {{@index}} memory attributes
*/
#define SAU_INIT_REGION{{@index}}       1

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START{{@index}}       {{this.start}}      /* start address of SAU region {{@index}} */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END{{@index}}       {{this.end}}      /* end address of SAU region {{@index}} */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC{{@index}}       {{this.nsc}}
/*
//   </e>
*/
{{/each}}
{{! Add remaining SAU regions as not configured }}
{{#block_loop (sub MaxSauregions ConfiguredSauRegions)}}
/*
//   <e>Initialize SAU Region {{add this ../ConfiguredSauRegions}}
//   <i> Setup SAU Region  {{add this ../ConfiguredSauRegions}} memory attributes
*/
#define SAU_INIT_REGION{{add this ../ConfiguredSauRegions}}       0

/*
//     <o>Start Address <0-0xFFFFFFE0>
*/
#define SAU_INIT_START{{add this ../ConfiguredSauRegions}}       0x00000000      /* start address of SAU region {{add this ../ConfiguredSauRegions}} */

/*
//     <o>End Address <0x1F-0xFFFFFFFF>
*/
#define SAU_INIT_END{{add this ../ConfiguredSauRegions}}       0x00000000      /* end address of SAU region {{add this ../ConfiguredSauRegions}} */

/*
//     <o>Region is
//         <0=>Non-Secure
//         <1=>Secure, Non-Secure Callable
*/
#define SAU_INIT_NSC{{add this ../ConfiguredSauRegions}}       0
/*
//   </e>
*/    
{{/block_loop}}

{{! handle the IRQs now }}
/*
// </h>
*/

/*
// <h>Setup Interrupt Target
*/
{{! We have 4*32 IRQs to handle on STM32L5 }}
{{#block_loop 4}}
{{setVar "minIRQ" (mult this 32) ~}}
{{setVar "maxIRQ" (add (mult this 32) 31) }}
{{setVar "itns_init" 0 }}
/*
//   <e>Initialize ITNS {{this}} (Interrupts {{../minIRQ}}..{{../maxIRQ}})
*/
{{! We parse the array of declared interrupts each time }}
{{#each @root.fzone.system.interrupt}}
{{#if (is_in_range (str2int this.irqn) ../../minIRQ ../../maxIRQ)}}
{{#if (eq this.security.n "1")}}
{{setVar "itns_init" 1 ~}}
{{/if}}
{{/if}}
{{/each}}
{{#if (eq ../itns_init 1)}}
#define NVIC_INIT_ITNS{{this}}    1
{{else}}
#define NVIC_INIT_ITNS{{this}}    0
{{/if}}

/*
// Interrupts {{../minIRQ}}..{{../maxIRQ}}
{{init_global 0 ~}}
{{#block_loop 32}}
{{#each @root.fzone.system.interrupt}}
{{#if (is_in_range (str2int this.irqn) ../../minIRQ ../../maxIRQ)}}
//   <o.{{this.irqn}}>  Interrupt   {{this.irqn}}: {{this.name}} <0=> Secure state <1=> Non-Secure state
{{#if (eq this.security.n "1")}}
{{increment_global (power 2 (sub (str2int this.irqn) ../../minIRQ)) ~}}
{{/if}}
{{/if}}
{{/each}}
{{/block_loop}}
*/
{{#if (eq ../itns_init 0)}}
#define NVIC_INIT_ITNS{{this}}_VAL      0x00000000
{{else}}
#define NVIC_INIT_ITNS{{this}}_VAL      0x{{show_hex (get_global)}}
{{/if}}

/*
//   </e>
*/
{{/block_loop}}

/*
// </h>
*/

#endif  /* PARTITION_GEN_H */