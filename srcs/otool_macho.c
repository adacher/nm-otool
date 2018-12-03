#include <ft_otool.h>

static void get_section_m32(struct segment_command *seg, struct mach_header *header)
{
    struct section *sect;
    uint32_t i;

    i = 0;
    sect = (struct section *)(seg + 1);
    while (i < seg->nsects)
    {
        if (!(ft_strcmp(sect->sectname, SECT_TEXT)))
            break;
        sect++;
        i++;
    }
    ft_putendl("Contents of (__TEXT,__text) section");
    display_m32(sect, (char *)header);
}

void macho_32(void *ptr, struct segment_command *tmp)
{
    struct mach_header *header;
    struct segment_command *seg;
    uint32_t i;

    i = 0;
    header = (struct mach_header *)ptr;
    seg = (struct segment_command *)(header + 1);
    while (i < header->ncmds)
    {
        if (seg->cmd == LC_SEGMENT)
        {
            if (!(ft_strcmp(seg->segname, SEG_TEXT)))
            {
                get_section_m32(seg, header);
                break;
            }
            tmp = seg;
        }
        seg = (struct segment_command *)((char *)seg + seg->cmdsize);
        i++;
    }
    if (tmp != NULL)
        get_section_m32(tmp, header);
}

static void get_section_m64(struct segment_command_64 *seg, struct mach_header_64 *header)
{
    struct section_64 *sect;
    uint32_t i;

    i = 0;
    sect = (struct section_64 *)(seg + 1);
    while (i < seg->nsects)
    {
        if (!(ft_strcmp(sect->sectname, SECT_TEXT)))
        {
            ft_putendl("Contents of (__TEXT,__text) section");
            display_m64(sect, (char *)header);
        }
        sect++;
        i++;
    }
}

void macho_64(void *ptr, struct segment_command_64 *tmp)
{
    struct mach_header_64 *header;
    struct segment_command_64 *seg;
    uint32_t i;

    i = 0;
    header = (struct mach_header_64 *)ptr;
    seg = (struct segment_command_64 *)(header + 1);
    while (i < header->ncmds)
    {
        if (seg->cmd == LC_SEGMENT_64)
        {
            if (!(ft_strcmp(seg->segname, SEG_TEXT)))
            {
                get_section_m64(seg, header);
                tmp = NULL;
                break;
            }
            tmp = seg;
        } 
        seg = (struct segment_command_64 *)((char *)seg + seg->cmdsize);
        i++;
    }
    if (tmp)
        get_section_m64(tmp, header);
}
