#include <limits.h>
#include <sys/param.h>

static inline int32_t
OSAtomicIncrement32(volatile int32_t *var)
{
    return __sync_add_and_fetch(var,1);
}

static inline int32_t
OSAtomicIncrement32Barrier(volatile int32_t *var)
{
    return __sync_add_and_fetch(var,1);
}

static inline int32_t
OSAtomicAdd32(volatile int32_t *var, int32_t val)
{
    return __sync_add_and_fetch(var,val);
}

// Simulation of mach_absolute_time related infrastructure
// For now, use gettimeofday.
// Consider using clockgettime(CLOCK_MONOTONIC) instead.

#include <sys/time.h>

struct mach_timebase_info {
  uint32_t numer;
  uint32_t denom;
};

typedef struct mach_timebase_info *mach_timebase_info_t;
typedef struct mach_timebase_info mach_timebase_info_data_t;

typedef int kern_return_t;

static inline
uint64_t
mach_absolute_time()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (1000ull)*((unsigned long long)tv.tv_sec*(1000000ull)+ tv.tv_usec);
}

static inline
int
mach_timebase_info(mach_timebase_info_t tbi)
{
	tbi->numer = 1;
	tbi->denom = 1;
	return 0;
}
