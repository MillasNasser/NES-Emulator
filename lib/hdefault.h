#if !defined(_DEFAULT_HEADER_)
#define _DEFAULT_HEADER_

    // Includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdint.h>
    #include <stdbool.h>

    // Definitions
    #define not_imp(ret) do { printf("%s not implemented yet\n", __func__); return ret; } while(0)
    #define check_alloc(a, ret) if(a == NULL) { fprintf(stderr, "[error] cannot alloc in %d line\n", __LINE__); return ret; }
    #define error(msg, code) do { fprintf(stderr, "[ERROR %d] " msg "\n", code); exit(code); }while(0)
    #define bit(a) (0x1&a)
#endif // _DEFAULT_HEADER_
