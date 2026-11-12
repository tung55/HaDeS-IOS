#include "multiboot.h"
#include "pmm.h"
#include "gui.h"

// Hàm in chữ VGA
volatile unsigned short* vga_buffer = (unsigned short*)0xB8000;
int vga_row = 0, vga_col = 0;
void vga_print(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') { vga_row++; vga_col = 0; }
        else {
            int index = vga_row * 80 + vga_col;
            vga_buffer[index] = (vga_buffer[index] & 0xFF00) | str[i];
            vga_col++;
        }
    }
}

// Hàm main nhận tham số trực tiếp từ Assembly
void kernel_main(multiboot_info_t* mbd, uint32_t magic) {
    vga_print("1. Kernel V3 da chay!\n");
    
    // BỎ QUA KIỂM TRA MAGIC, CHẠY THẲNG VÀO GUI
    
    vga_print("2. Dang khoi tao bo nho...\n");
    pmm_init(mbd);  
    
    vga_print("3. Chuan bi ve giao dien...\n");
    gui_init(mbd);  

    vga_print("4. Da ve xong giao dien!\n");

    while (1) {
        __asm__ volatile("pause"); 
    }
}
