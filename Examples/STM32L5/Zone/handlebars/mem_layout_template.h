#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

{{! Loop on the memory elements }}
{{#each fzone.system.memory}}
{{#if this.parent includeZero=false}}
{{! We take into account the applicative memory sections }}
/* {{this.info}} */
#define REGION_{{uppercase this.name}}_START {{this.start}} 
#define REGION_{{uppercase this.name}}_PADDR {{this.physical}}
#define REGION_{{uppercase this.name}}_SIZE {{this.size}}
{{else}}
{{! We must skip the system memory regions definitions : the elements having no parent have no interest for the application}}
{{/if}}
{{/each}}

#endif