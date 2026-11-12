#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

void kernel_main(uint32_t magic, multiboot_info_t* mbd) {   /* boot.asm đẩy ebx trước, eax sau => magic là đối số 1 */
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        while(1) __asm__ volatile("hlt");
    }

    pmm_init(mbd);  // Khởi tạo bộ nhớ
    gui_init(mbd);  // Vẽ giao diện

    while (1) {
        __asm__ volatile("hlt"); // Dừng CPU
    }
}
