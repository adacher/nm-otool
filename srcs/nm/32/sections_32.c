#include <ft_nm.h>

static void add_section_32(t_section **p, char *sectname)
{
    t_section *create;
    t_section *tmp;

    create = (t_section *)malloc(sizeof(t_section));
    create->name = sectname;
    create->next = NULL;
    if (!*p)
    {
        create->index = 1;
        create->next = NULL;
        create->end = create;
        *p = create;
    }
    else
    {
        tmp = (*p)->end;
        create->index = tmp->index + 1;
        create->next = NULL;
        create->end = create;
        tmp->next = create;
        (*p)->end = create;
    }
}

static void process_section_32(t_section **psects, struct section *sect, uint32_t nbsect)
{
    t_section *p;

    p = *psects;
    while (nbsect)
    {
        add_section_32(&p, sect->sectname);
        *psects = p;
        sect += 1;
        nbsect--;
    }
}

void process_segment_32(struct load_command *lc, t_section **psects)
{
    struct segment_command   *segment;
    struct section           *sect;
    uint32_t                 nbsect;

    segment = (struct segment_command *)lc;
    nbsect = segment->nsects;
    if (nbsect == 0)
        return ;
    sect = (struct section *)((void *)segment + sizeof(*segment));
    process_section_32(psects, sect, nbsect);
}