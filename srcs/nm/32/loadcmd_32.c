#include <ft_nm.h>

static void browse_loadcommands_32(struct load_command *lc, uint32_t nbcmd, void *ptr, size_t filesize)
{
    uint32_t                cmd;
    t_section               *psects;
    t_symdata               *psymbols;

    psects = NULL;
    psymbols = NULL;
    while (nbcmd)
    {
        cmd = lc->cmd;
        if (cmd == LC_SEGMENT)
            process_segment_32(lc, &psects);
        if (cmd == LC_SYMTAB)
            process_symtable_32(lc, ptr, &psymbols, filesize);
        lc = (void *)lc + lc->cmdsize;
        nbcmd--;
    }
    insertion_sort(&psymbols);
    display_32(psects, psymbols);
}

void bits_32(void *ptr, uint32_t filesize)
{
    struct load_command     *lc;
    struct mach_header      *header;
    uint32_t                nbcmd;
    
    header = (struct mach_header *)ptr;
    nbcmd = header->ncmds;
    if (nbcmd == 0)
        return ;
    lc = (struct load_command *)(header + 1);
    browse_loadcommands_32(lc, nbcmd, ptr, filesize);
}