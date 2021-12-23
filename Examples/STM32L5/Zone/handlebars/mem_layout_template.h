#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

{{#each azone.partition.memory}}
/* {{this._info}} */
{{#if (eq this._parent "Flash_S")}}
#define REGION_{{uppercase this._name}}_START 0x{{hex_add "0x0C000000" this._offset}}
#define REGION_{{uppercase this._name}}_PADDR 0x{{hex_add "0x08000000" this._offset}}
{{/if}}
{{#if (eq this._parent "Flash_NS")}}
#define REGION_{{uppercase this._name}}_START 0x{{hex_add "0x08000000" this._offset}}
#define REGION_{{uppercase this._name}}_PADDR 0x{{hex_add "0x08000000" this._offset}}
{{/if}}
{{#if (eq this._parent "SRAM_S")}}
#define REGION_{{uppercase this._name}}_START 0x{{hex_add "0x03000000" this._offset}}
#define REGION_{{uppercase this._name}}_PADDR 0x{{hex_add "0x02000000" this._offset}}
{{/if}}
{{#if (eq this._parent "SRAM_NS")}}
#define REGION_{{uppercase this._name}}_START 0x{{hex_add "0x02000000" this._offset}}
#define REGION_{{uppercase this._name}}_PADDR 0x{{hex_add "0x02000000" this._offset}}
{{/if}}
#define REGION_{{uppercase this._name}}_SIZE {{this._size}}

{{/each}}

#endif