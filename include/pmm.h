#ifndef PMM_H
#define PMM_H
#include "multiboot.h"
#define PAGE_SIZE 4096
#define MAX_PAGES 1048576
void pmm_init(multiboot_info_t* mbd);
#endif
