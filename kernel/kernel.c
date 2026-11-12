#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic) {
    serial_print("Kernel bat dau chay!\n");
    
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        serial_print("LOI: Magic number sai!\n");
        while(1) { __asm__ volatile("hlt"); } 
    }

    pmm_init(mbd);  
    gui_init(mbd);  

    serial_print("Da ve xong giao dien!\n");

    while (1) {
        __asm__ volatile("pause"); 
    }
}
