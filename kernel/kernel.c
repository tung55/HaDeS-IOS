#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

void kernel_main(multiboot_info_t* mbd, uint32_t magic) {
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        while(1) { __asm__ volatile("hlt"); } 
    }

    pmm_init(mbd);  // Khởi tạo bộ nhớ
    gui_init(mbd);  // Vẽ giao diện

    // Sửa lệnh "hlt" thành "pause" để VMware không hiểu nhầm là tắt máy
    while (1) {
        __asm__ volatile("pause"); 
    }
}
