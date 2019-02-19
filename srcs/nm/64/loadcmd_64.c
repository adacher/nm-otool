#include <nm.h>

static void browse_loadcommands_64(struct load_command *lc, uint32_t nbcmd, void *ptr, size_t filesize)
{
    uint32_t                cmd;
    t_section               *psects;
    t_symdata               *psymbols;

    psects = NULL;
    psymbols = NULL;
    while (nbcmd)
    {
        cmd = ppc_64(lc->cmd);
        if (cmd == LC_SEGMENT_64)
            process_segment_64(lc, &psects);
        if (cmd == LC_SYMTAB)
            process_symtable_64(lc, ptr, &psymbols, filesize);
        lc = (void *)lc + ppc_64(lc->cmdsize);
        nbcmd--;
    }
    insertion_sort(&psymbols);
    display_64(psects, psymbols);
}

void do_bits_64(void *ptr, size_t filesize) // changer nom fonction + clair
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
    browse_loadcommands_64(lc, nbcmd, ptr, filesize);
}