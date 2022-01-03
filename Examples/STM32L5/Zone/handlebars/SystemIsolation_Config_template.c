/*----------------------------------------------------------------------------
  System Isolation Configuration
  This function is responsible for Memory and Peripheral isolation
  for secure and non-secure application parts
 *----------------------------------------------------------------------------*/

#include "stm32l5xx_hal.h"

void SystemIsolation_Config(void)
{
  /* Enable GTZC peripheral clock */
  __HAL_RCC_GTZC_CLK_ENABLE();

  /* Setup Memory Protection Controller (MPC) */
{{#each fzone.system.mpc_setup}}
  {{! Compute the number of registers to be considered }}
  {{setVar "nb_reg" (div this.S_bit.length 32) ~}}
  /* {{this.info}} : {{../nb_reg}} registers */
  {{! Loop on blocks of 32 bits to write the registers }}
  {{#block_loop ../nb_reg}}
    {{! Compute the start index for this register in the S_bit array }}
    {{setVar "reg_index" this ~}}
    {{setVar "reg_start_index" (mult this 32) ~}}
    {{! Compute the register value from the appropriate 32 S_bit}}
  WRITE_REG({{../name}}->VCTR[{{../../reg_index}}], {{compute_reg_value ../../reg_start_index ../S_bit}}U);
  {{/block_loop}}
{{/each}}

  /* Setup Peripheral Protection Controller (PPC) */
{{#each fzone.system.reg_setup}}
  {{#replace "-&gt;" "->"}}WRITE_REG({{this.name}},{{/replace}}
  {{! The fzone provides a direct value or an array for the value(s) to be set}}
  {{#if (isArray this.value)}}
    {{#each this.value}}
      {{#if @last}}
    {{this}}   /* {{lookup ../peripheral @index}} */
      {{else}}
    {{this}} | /* {{lookup ../peripheral @index}} */
      {{/if}}
    {{/each}}
  {{else}}
    {{this.value}}   /* {{this.peripheral}} */
  {{/if}}
  );
{{/each}}

  /* Clear all illegal access pending interrupts in TZIC */
  if (HAL_GTZC_TZIC_ClearFlag(GTZC_PERIPH_ALL) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Enable all illegal access interrupts in TZIC */
  if(HAL_GTZC_TZIC_EnableIT(GTZC_PERIPH_ALL) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }

  /* Enable TZIC secure interrupt */
  HAL_NVIC_SetPriority(GTZC_IRQn, 0, 0); /* Highest priority level */
  HAL_NVIC_ClearPendingIRQ(GTZC_IRQn);
  HAL_NVIC_EnableIRQ(GTZC_IRQn);
}