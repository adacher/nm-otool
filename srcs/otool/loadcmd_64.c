#include <otool.h>

static void process_section_64(struct section_64 *sect, uint32_t nbsect, struct mach_header_64 *header)
{
    while (nbsect)
    {
        if (!(ft_strcmp(sect->sectname, SECT_TEXT)))
        {
           ft_putendl("Contents of (__TEXT,__text) section");
           display_m64(sect, (char *)header);
        }
        sect += 1;
        nbsect--;
    }
}

static void process_segment_64(struct load_command *lc, struct mach_header_64 *header)
{
    struct segment_command_64 *segment;
    struct section_64         *sect;
    uint32_t                  nbsect;

    segment = (struct segment_command_64 *)lc;
    nbsect = ppc_64(segment->nsects);
    if (nbsect == 0)
        return ;
    sect = (struct section_64 *)((void *)segment + sizeof(*segment));
    process_section_64(sect, nbsect, header);
}

static void browse_loadcommands_64(struct load_command *lc, uint32_t nbcmd, struct mach_header_64 *header)
{
    uint32_t                cmd;

    while (nbcmd)
    {
        cmd = ppc_64(lc->cmd);
        if (cmd == LC_SEGMENT_64)
            process_segment_64(lc, header);
        lc = (void *)lc + ppc_64(lc->cmdsize);
        nbcmd--;
    }
}

void do_bits_64(void *ptr)
{
    struct load_command     *lc;
    struct mach_header_64   *header;
    uint32_t                nbcmd;
    
    header = (struct mach_header_64 *)ptr;
    set_ppc(swap_64(header->cputype) == CPU_TYPE_POWERPC64);
    nbcmd = ppc_64(header->ncmds);
    if (nbcmd == 0)
        return ;
    lc = (struct load_command *)(header + 1);
    browse_loadcommands_64(lc, nbcmd, header);
}