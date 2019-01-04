#include <ft_nm.h>

static int verify_sections_64(size_t filesize, size_t checksize, struct section_64 *sect, uint32_t nbsect)
{
    while (nbsect)
    {
        if (checksize > filesize)
            return (0);
        if ((size_t)sect->offset > filesize)
			return (0);
        checksize += sizeof(struct section_64);
        sect += 1;
        nbsect--;
    }
    return (1);
}

static int verify_segname_64(struct segment_command_64 *segment)
{
    if (!(ft_strcmp(segment->segname, "__DATA"))
        || (!(ft_strcmp(segment->segname, "__TEXT"))))
    {
        if (segment->cmdsize == 0)
            return (0);
        if (segment->filesize == 0)
            return (0);
        if (segment->nsects == 0)
            return (0);
    }
    return (1);
}

static int verify_seg_64(size_t filesize, struct load_command *lc, size_t checksize)
{
    struct segment_command_64  *segment;
    struct section_64           *sect;
    uint32_t                    nbsect;

    segment = (struct segment_command_64 *)lc;
    nbsect = segment->nsects;
    sect = (struct section_64 *)((void *)segment + sizeof(*segment));
    if (!(verify_segname_64(segment)))
        return (0);
    if (!(verify_sections_64(filesize, checksize, sect, nbsect)))
        return (0);
    return (1);
}

static int verify_lc_64_2(struct load_command *lc, size_t filesize, size_t checksize)
{
    if (lc->cmd == LC_SEGMENT_64)
    {
        if (!(verify_seg_64(filesize, lc, checksize)))
            return (0);
    }
    if (lc->cmd == LC_SYMTAB)
    {
        if (!(verify_symtab(lc, filesize, checksize)))
            return (0);
    }
    return (1);
}

int verify_lc_64(struct mach_header_64 *header, size_t filesize, uint32_t nbcmd)
{
    struct load_command     *lc; 
    size_t                  checksize;

    checksize = 0;
    lc = (struct load_command *)(header + 1);
    while (nbcmd)
    {
        if (checksize > filesize)
            return (0);
        if (lc->cmdsize % 8 != 0)
            return (0);
        if (!(verify_lc_64_2(lc, filesize, checksize)))
            return (0);
        checksize += (size_t)lc->cmdsize;
        lc = (void *)lc + lc->cmdsize;
        nbcmd--;
    }
    return (1);
}