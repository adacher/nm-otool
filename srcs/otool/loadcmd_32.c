#include <otool.h>

static void process_section_64(struct section *sect, uint32_t nbsect, struct mach_header *header)
{
    while (nbsect)
    {
        if (!(ft_strcmp(sect->sectname, SECT_TEXT)))
        {
           ft_putendl("Contents of (__TEXT,__text) section");
           display_m32(sect, (char *)header);
        }
        sect += 1;
        nbsect--;
    }
}

static void process_segment_32(struct load_command *lc, struct mach_header *header)
{
    struct segment_command *segment;
    struct section         *sect;
    uint32_t                  nbsect;

    segment = (struct segment_command *)lc;
    nbsect = ppc_32(segment->nsects);
    if (nbsect == 0)
        return ;
    sect = (struct section *)((void *)segment + sizeof(*segment));
    process_section_64(sect, nbsect, header);
}

static void browse_loadcommands_32(struct load_command *lc, uint32_t nbcmd, struct mach_header *header)
{
    uint32_t                cmd;

    while (nbcmd)
    {
        cmd = ppc_32(lc->cmd);
        if (cmd == LC_SEGMENT)
            process_segment_32(lc, header);
        lc = (void *)lc + ppc_32(lc->cmdsize);
        nbcmd--;
    }
}

void do_bits_32(void *ptr)
{
    struct load_command     *lc;
    struct mach_header   *header;
    uint32_t                nbcmd;
    
    header = (struct mach_header *)ptr;
    set_ppc(swap_32(header->cputype) == CPU_TYPE_POWERPC);
    nbcmd = ppc_32(header->ncmds);
    if (nbcmd == 0)
        return ;
    lc = (struct load_command *)(header + 1);
    browse_loadcommands_32(lc, nbcmd, header);
}