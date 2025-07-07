#include "userprog/region.h"
#include "threads/malloc.h"
#include "threads/thread.h"

static struct region_desc regions[MAX_REGIONS];

void
region_init (void) 
{
  for (int i = 0; i < MAX_REGIONS; i++)
    regions[i].base = NULL;
}

/* Allocate a new region: carve out a contiguous buffer and install a descriptor. */
region_id_t
region_create (size_t size, int perms)
{
  for (int i = 0; i < MAX_REGIONS; i++) 
    if (regions[i].base == NULL) 
      {
        void *buf = palloc_get_multiple (PAL_ZERO, (size + PGSIZE - 1) / PGSIZE);
        if (!buf) return -1;
        regions[i].base  = buf;
        regions[i].limit = size;
        regions[i].perms = perms;
        return i;
      }
  return -1;  /* no free slot */
}

/* On every user access, we’ll call this (e.g. from syscall) to trap OOB. */
bool
region_check_access (region_id_t id, void *addr, bool write)
{
  if (id < 0 || id >= MAX_REGIONS) 
    return false;
  struct region_desc *r = &regions[id];
  if (!r->base) 
    return false;
  uintptr_t off = (uintptr_t)addr - (uintptr_t)r->base;
  if (off >= r->limit) 
    return false;
  if (write && !(r->perms & 2)) 
    return false;
  return true;
}

void
region_destroy (region_id_t id)
{
  if (id < 0 || id >= MAX_REGIONS) return;
  struct region_desc *r = &regions[id];
  if (r->base) 
    {
      palloc_free_multiple (r->base, (r->limit + PGSIZE - 1) / PGSIZE);
      r->base = NULL;
    }
}
