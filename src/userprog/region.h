#ifndef USERPROG_REGION_H
#define USERPROG_REGION_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_REGIONS      16   /* per-process limit */

typedef int region_id_t;

struct region_desc {
  void *base;       /* start of the region’s buffer */
  size_t limit;     /* size in bytes */
  int perms;        /* e.g. READ=1, WRITE=2 */
};

void     region_init          (void);
region_id_t region_create     (size_t size, int perms);
bool     region_check_access  (region_id_t id, void *addr, bool write);
void     region_destroy       (region_id_t id);

#endif /* userprog/region.h */
