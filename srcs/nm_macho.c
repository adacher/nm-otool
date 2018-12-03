#include <ft_nm.h>

void macho_64(void *ptr)
{
    struct mach_header_64	*header;
    struct load_command		*lc;
    struct symtab_command	*sym;
    char                    **load;
    uint32_t i;

    i = 0;
    sym = NULL;
    load = NULL;
    header = (struct mach_header_64*)ptr;
    lc = (void*)ptr + sizeof(*header);
    while (i < header->ncmds)
    {
        if (lc->cmd == LC_SEGMENT_64)
            load = get_section_64(load, (struct segment_command_64 *)lc);
        if (lc->cmd == LC_SYMTAB)
            sym = (struct symtab_command*)lc; 
        lc = (void*)lc + lc->cmdsize;
       i++;
    }
   // printf("%s\n", load[0]);
    display_m64(ptr, load, sym);
}

void macho_32(void *ptr)
{
    ptr = NULL;
    printf("macho32\n");
}