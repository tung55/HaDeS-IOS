#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic) {
    // Không in VGA Text Mode nữa để tránh rác màn hình
    pmm_init(mbd);  
    gui_init(mbd);  

    // Giữ CPU chạy
    while (1) {
        __asm__ volatile("pause"); 
    }
}
