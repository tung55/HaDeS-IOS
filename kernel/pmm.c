#include "pmm.h"
static uint32_t pmm_bitmap[MAX_PAGES / 32];
void pmm_init(multiboot_info_t* mbd) {
    (void)mbd;
    // Reset bitmap (Đơn giản hóa để test GUI trước)
    for (uint32_t i = 0; i < MAX_PAGES / 32; i++) pmm_bitmap[i] = 0;
}
