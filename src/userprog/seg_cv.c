/* userprog/seg_cv.c 
   A toy pixel-by-pixel mask writer that traps OOB. */

#include <stdio.h>
#include "pintos/syscall.h"

int
main (void) 
{
  /* Create a “segment” for our 64×64 mask (4 KB) */
  int seg = region_create (64*64, /*bytes*/ 2 /*READ|WRITE*/);
  if (seg < 0) {
    printf ("Failed to alloc region\n");
    return 1;
  }

  /* Paint each pixel in that region */
  for (int i = 0; i < 64*64; i++)
    {
      if (!region_check (seg, (void*)(/*base*/0 + i), true))
        {
          printf ("OOB at pixel %d!\n", i);
          break;
        }
      /* pretend to write mask value */
      *(char*)(/*base*/0 + i) = (i%2) ? 0xFF : 0x00;
    }

  /* Done with our “mask” */
  region_destroy (seg);
  return 0;
}




//syscall.c with  seg_cv.c
#include "userprog/region.h"
…
#define SYS_REGION_CREATE    20
#define SYS_REGION_CHECK     21
#define SYS_REGION_DESTROY   22
…

static void
syscall_handler (struct intr_frame *f ) 
{
  …
  switch (syscall_number) 
    {
      …
      case SYS_REGION_CREATE:
        {
          size_t size = get_user (f->esp + 4);
          int perms   = get_user (f->esp + 8);
          f->eax = region_create (size, perms);
          break;
        }
      case SYS_REGION_CHECK:
        {
          int id    = get_user (f->esp + 4);
          void *a   = (void *) get_user (f->esp + 8);
          bool wr   = get_user (f->esp + 12);
          f->eax = region_check_access (id, a, wr);
          break;
        }
      case SYS_REGION_DESTROY:
        {
          int id = get_user (f->esp + 4);
          region_destroy (id);
          break;
        }
      …
    }
}
