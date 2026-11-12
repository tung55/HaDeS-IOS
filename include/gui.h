#ifndef GUI_H
#define GUI_H
#include <stdint.h>
#include "multiboot.h"

void gui_init(multiboot_info_t* mbd);
void serial_print(const char* str); // Thêm dòng này để in log

#endif
