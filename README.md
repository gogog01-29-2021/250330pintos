flowchart TD
    subgraph Kernel [Pintos Kernel (src/userprog)]
      A[region.h<br/>& region.c] --> B[syscall.c<br/>+ SYS_REGION_* handlers]
      B -->|builds into| C[(Kernel with Region Support)]
    end

    subgraph Userland [Pintos Examples (src/examples)]
      D[seg_cv.c<br/>(uses SYS_REGION_CREATE/CHECK/DESTROY)] -->|executes on| C
    end

    C -->|provides syscalls to| D



# Try to compile syscall.c by itself
gcc -std=gnu99 -Wall -Werror -I../../threads -I../../lib -I../../devices -I../../userprog \
    -c syscall.c -o syscall.o

#Link it to an excecutable
gcc -o syscall_test syscall.o \
    -L../../threads -lthreads \
    -L../../lib     -l:libkernel.a \
    -L../../devices -ldevices \
    -L.             -luserprog \
    -lpintos-stubs  -lpintos-kernel


