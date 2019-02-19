#include <nm.h>

static void browse_loadcommands_32(struct load_command *lc, uint32_t nbcmd, void *ptr, size_t filesize)
{
    uint32_t                cmd;
    t_section               *psects;
    t_symdata               *psymbols;

    psects = NULL;
    psymbols = NULL;
    while (nbcmd)
    {
        cmd = ppc_32(lc->cmd);
        if (cmd == LC_SEGMENT)
            process_segment_32(lc, &psects);
        if (cmd == LC_SYMTAB)
            process_symtable_32(lc, ptr, &psymbols, filesize);
        lc = (void *)lc + ppc_32(lc->cmdsize);
        nbcmd--;
    }
    insertion_sort(&psymbols);
    display_32(psects, psymbols);
}

void do_bits_32(void *ptr, size_t filesize)
{
    struct load_command     *lc;
    struct mach_header      *header;
    uint32_t                nbcmd;
    
    header = (struct mach_header *)ptr;
    set_ppc(swap_32(header->cputype) == CPU_TYPE_POWERPC);
    nbcmd = ppc_32(header->ncmds);
    if (nbcmd == 0)
        return ;
    lc = (struct load_command *)(header + 1);
    browse_loadcommands_32(lc, nbcmd, ptr, filesize);
}