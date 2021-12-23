#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

/* Non-secure FLASH for CODE execution */
#define REGION_CODE_NS_START 0x08040000 
#define REGION_CODE_NS_PADDR 0x08040000
#define REGION_CODE_NS_SIZE 0x40000
/* Secure FLASH for CODE execution */
#define REGION_CODE_S_START 0x0C000000 
#define REGION_CODE_S_PADDR 0x08000000
#define REGION_CODE_S_SIZE 0x3E000
/* Secure FLASH for CODE Veneer table */
#define REGION_VENEER_START 0x0C03E000 
#define REGION_VENEER_PADDR 0x0803E000
#define REGION_VENEER_SIZE 0x2000
/* Non-secure RAM for DATA section */
#define REGION_DATA_NS_START 0x20000000 
#define REGION_DATA_NS_PADDR 0x20000000
#define REGION_DATA_NS_SIZE 0x20000
/* Secure RAM for DATA section */
#define REGION_DATA_S_START 0x30020000 
#define REGION_DATA_S_PADDR 0x20020000
#define REGION_DATA_S_SIZE 0x20000

#endif