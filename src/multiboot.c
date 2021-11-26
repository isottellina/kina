#include "multiboot.h"

multiboot_tag_t *multiboot_get_first_tag(multiboot_header_t *header) {
    return (multiboot_tag_t *)(header + 8);
}

multiboot_tag_t *multiboot_get_next_tag(multiboot_tag_t *tag) {
    // Align size on 8 bytes
    int size = tag->size;

    if (size % 8) {
        size = tag->size + (8 - (tag->size % 8));
    }

    return (multiboot_tag_t *)((char *)tag + size);
}

multiboot_tag_t *multiboot_get_tag_with_type(multiboot_header_t *header, enum multiboot_tag_type type) {
    multiboot_tag_t *tag = multiboot_get_first_tag(header);

    while(tag->type) {
        if (tag->type == type)
            return tag;
    }

    return (multiboot_tag_t *)0;
}

const char *multiboot_get_tag_name(enum multiboot_tag_type name) {
    switch (name) {
        case MULTIBOOT_CMDLINE_TAG:
            return "Cmdline";
        case MULTIBOOT_LOADER_NAME_TAG:
            return "Bootloader name";
        case MULTIBOOT_MODULE_TAG:
            return "Module";
        case MULTIBOOT_BASIC_MEM_TAG:
            return "Basic memory";
        case MULTIBOOT_BOOT_DEVICE_TAG:
            return "Boot device";
        case MULTIBOOT_MEMORY_MAP_TAG:
            return "Memory map";
        case MULTIBOOT_VBE_TAG:
            return "VBE";
        case MULTIBOOT_FRAMEBUFFER_TAG:
            return "Framebuffer";
        case MULTIBOOT_ELF_SYMBOL_TAG:
            return "ELF symbol";
        case MULTIBOOT_APM_TABLE_TAG:
            return "APM table";
        case MULTIBOOT_ELF32_SYMTAB_TAG:
            return "ELF32 system table";
        case MULTIBOOT_ELF64_SYMTAB_TAG:
            return "ELF64 system table";
        case MULTIBOOT_SMBIOS_TAG:
            return "SMBIOS table";
        case MULTIBOOT_OLD_ACPI_TAG:
            return "ACPI old RSDP";
        case MULTIBOOT_NEW_ACPI_TAG:
            return "ACPI new RSDP";
        case MULTIBOOT_NETWORK_TAG:
            return "Networking";
        case MULTIBOOT_EFI_MAP_TAG:
            return "EFI memory map";
        case MULTIBOOT_EFI_NOT_TERMINATED_TAG:
            return "EFI boot services not terminated";
        case MULTIBOOT_EFI32_HANDLE_TAG:
            return "EFI32 image handle pointer";
        case MULTIBOOT_EFI64_HANDLE_TAG:
            return "EFI64 image handle pointer";
        case MULTIBOOT_LOAD_BASE_TAG:
            return "Image load base physical address";
    }

    return "Error: can't identify tag";
}
