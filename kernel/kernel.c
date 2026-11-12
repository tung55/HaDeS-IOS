#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

// Địa chỉ bộ nhớ VGA Text Mode (80x25 ký tự)
volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;
int vga_row = 0;
int vga_col = 0;

// Hàm in chữ trực tiếp lên màn hình đen
void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            vga_row++;
            vga_col = 0;
        } else {
            int index = vga_row * 80 + vga_col;
            vga_buffer[index] = (vga_buffer[index] & 0xFF00) | str[i];
            vga_col++;
        }
    }
}

void kernel_main(multiboot_info_t* mbd, uint32_t magic) {
    // In thông báo ra màn hình ngay lập tức
    vga_print("1. Kernel bat dau chay!\n");
    
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        vga_print("LOI: Magic number sai!\n");
        while(1) { __asm__ volatile("hlt"); } 
    }

    vga_print("2. Magic number chinh xac. Dang khoi tao bo nho...\n");
    pmm_init(mbd);  
    
    vga_print("3. Da xong PMM. Chuan bi ve giao dien...\n");
    gui_init(mbd);  

    vga_print("4. Da ve xong giao dien (neu man hinh van den la loi VESA)\n");

    while (1) {
        __asm__ volatile("pause"); 
    }
}
