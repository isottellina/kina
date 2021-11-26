#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

typedef struct {
    int total_size;
    int reserved;
} __attribute((packed)) multiboot_header_t;

typedef struct {
    int type;
    int size;
} __attribute((packed)) multiboot_tag_t;

enum multiboot_tag_type {
     MULTIBOOT_CMDLINE_TAG = 1,
     MULTIBOOT_LOADER_NAME_TAG = 2,
     MULTIBOOT_MODULE_TAG = 3,
     MULTIBOOT_BASIC_MEM_TAG = 4,
     MULTIBOOT_BOOT_DEVICE_TAG = 5,
     MULTIBOOT_MEMORY_MAP_TAG = 6,
     MULTIBOOT_VBE_TAG = 7,
     MULTIBOOT_FRAMEBUFFER_TAG = 8,
     MULTIBOOT_ELF_SYMBOL_TAG = 9,
     MULTIBOOT_APM_TABLE_TAG = 10,
     MULTIBOOT_ELF32_SYMTAB_TAG = 11,
     MULTIBOOT_ELF64_SYMTAB_TAG = 12,
     MULTIBOOT_SMBIOS_TAG = 13,
     MULTIBOOT_OLD_ACPI_TAG = 14,
     MULTIBOOT_NEW_ACPI_TAG = 15,
     MULTIBOOT_NETWORK_TAG = 16,
     MULTIBOOT_EFI_MAP_TAG = 17,
     MULTIBOOT_EFI_NOT_TERMINATED_TAG = 18,
     MULTIBOOT_EFI32_HANDLE_TAG = 19,
     MULTIBOOT_EFI64_HANDLE_TAG = 20,
     MULTIBOOT_LOAD_BASE_TAG = 21,
};

multiboot_tag_t *multiboot_get_first_tag(multiboot_header_t *);
multiboot_tag_t *multiboot_get_next_tag(multiboot_tag_t *);
multiboot_tag_t *multiboot_get_tag_with_type(multiboot_header_t *, enum multiboot_tag_type);
const char *multiboot_get_tag_name(enum multiboot_tag_type);

#endif // MULTIBOOT_H_
