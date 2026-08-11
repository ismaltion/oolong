rm -r bin
rm src/bootloader/size.asm
mkdir bin

# Kernel drivers
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/drv/vgatext.c -o bin/kdrv_vgatext.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/drv/pit.c -o bin/kdrv_pit.o

# Kernel
nasm src/kernel/entry.asm -f elf -o bin/kernel_entry.o

clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/main.c -o bin/kernel_main.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/memory.c -o bin/kernel_memory.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/idt.c -o bin/kernel_idt.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/dev.c -o bin/kernel_dev.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/console.c -o bin/kernel_console.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/pic.c -o bin/kernel_pic.o
clang --target=i386-unknown-none -ffreestanding -m32 -fno-pie -c src/kernel/io.c -o bin/kernel_io.o

i386-elf-ld -m elf_i386 -T src/kernel_linker.ld \
    -o "./bin/kernel.elf" \
    "bin/kernel_entry.o" \
    "bin/kernel_main.o" \
    "bin/kernel_memory.o" \
    "bin/kernel_idt.o" \
    "bin/kernel_dev.o" \
    "bin/kernel_console.o" \
    "bin/kernel_io.o" \
    "bin/kernel_pic.o" \
    "bin/kdrv_pit.o" \
    "bin/kdrv_vgatext.o"

# Bootloader (scuffed af, needs size of kernel bruhhh lol)

objcopy -O binary bin/kernel.elf bin/kernel.bin
size=$(stat -c%s bin/kernel.bin)
sectors=$(( (size + 511) / 512 ))
cat > src/bootloader/size.asm <<EOF
%define KERNEL_SIZE $sectors
EOF

nasm src/bootloader/entry.asm -o bin/bootloader_entry.o
nasm src/bootloader/main.asm -o bin/bootloader_main.o
cat bin/bootloader_entry.o bin/bootloader_main.o > bin/bootloader.bin

# Finishing up
cat bin/bootloader.bin bin/kernel.bin > everything.bin