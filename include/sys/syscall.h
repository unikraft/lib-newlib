#include <uk/config.h>
#if CONFIG_LIBSYSCALL_SHIM
#include <uk/syscall.h>
#else
#error "Provide alternative syscall.h header"
#endif
