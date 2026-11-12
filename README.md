# HaDeS/IOS

Hệ điều hành x86 32-bit tối giản: khởi động bằng GRUB (Multiboot 1), vẽ giao diện đồ họa 1024x768x32 qua framebuffer.

## Build

Cần: `gcc` (có `-m32`), `nasm`, `ld`, `make`, `grub-pc-bin`, `grub-common`, `xorriso`.

```sh
make          # tạo myos.iso
make run      # chạy thử bằng QEMU (cần qemu-system-i386)
make clean
```

Hoặc đẩy code lên GitHub: Actions tự build và xuất `myos.iso` ở mục Artifacts (`HaDeS-ISO`).

## Cấu trúc

```
.github/workflows/build.yml   tự động build trên GitHub
Makefile  linker.ld  boot.asm
include/  multiboot.h string.h pmm.h gui.h
kernel/   kernel.c string.c pmm.c gui.c
```

## Ghi chú

- `boot.asm` đẩy `ebx` rồi `eax`, nên `kernel_main(uint32_t magic, multiboot_info_t* mbd)` nhận magic trước.
- `gui.c`: font 8x8 đọc bit từ trái sang phải (0x80 là cột trái nhất). Đã có A-Z, a-z, 0-9 và `. , : ! ? - _ + = * < > ( ) / %`.
- Nếu GRUB không đặt được chế độ 32-bit, kernel báo lỗi bằng chữ trên màn hình VGA thay vì treo màn đen.
- `pmm.c` hiện mới chỉ khởi tạo bitmap trống (chưa cấp phát trang).
- Chưa có: ngắt, bàn phím, chuột, cấp phát bộ nhớ thật. GUI hiện là ảnh tĩnh.
