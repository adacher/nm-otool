#include <ft_nm.h>

int verify_symtab(struct load_command *lc, size_t filesize, size_t checksize)
{
    struct symtab_command   *sym;
    uint32_t                nbsyms;
    uint32_t                i;

    i = 0;
    sym = (struct symtab_command *)lc;
    nbsyms = sym->nsyms;
    if (sym->cmdsize == 0)
        return (0);
    if (sym->strsize == 0)
        return (0);
    if (sym->stroff > filesize)
        return (0);
    while (i < nbsyms)
    {
        checksize += sizeof(struct nlist_64);
		if (checksize > filesize)
            return (0);
		i++;
    }
    return (1);
}

static int verify_32(void *ptr, size_t filesize)
{
    struct mach_header  *header;
    uint32_t            nbcmd;

    header = (struct mach_header *)ptr;
    nbcmd = header->ncmds;
    if (nbcmd == 0) //|| header->sizeofcmds <= 0)
        return (0);
    return (verify_lc_32(header, filesize, nbcmd));  
}

static int verify_64(void *ptr, size_t filesize)
{
    struct mach_header_64  *header;
    uint32_t                nbcmd;

    header = (struct mach_header_64 *)ptr;
    nbcmd = header->ncmds;
    if (nbcmd == 0) // || header->sizeofcmds <= 0)
        return (0);
    return (verify_lc_64(header, filesize, nbcmd));  
}

int check_file_content(void *ptr, size_t filesize)
{
    uint32_t magic;

    magic = *(uint32_t *)ptr;

    if (filesize <= 0)
        return (0);
    else if (magic == MH_MAGIC || magic == MH_CIGAM)
        return (verify_32(ptr, filesize));
    else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
        return (verify_64(ptr, filesize));
    else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
        return (1);
    else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
        return (1);
    else
        return (0);
    return (1);
}