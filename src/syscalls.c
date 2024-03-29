#include "syscalls.h"
#include "uart.h"
#include "stm32f2xx.h"
#include "FreeRTOS.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

size_t   __malloc_margin = 256;
char    *__brkval;

void _exit(int code)
{
    for (;;);
}


ssize_t _read_r(struct _reent *r, int fd, void *ptr, size_t len)
{
#ifdef NULL_DBG
    return 0;
#else
    return uart_read_r(r, fd, ptr, len);
#endif
    
}


ssize_t _write_r(struct _reent *r, int fd, const void *ptr, size_t len)
{
#ifdef NULL_DBG
    return len;
#else
    return uart_write_r(r, fd, ptr, len);
#endif
}


off_t _lseek_r(struct _reent *r, int fd, _off_t ptr, int dir)
{
    fd  = fd;
    ptr = ptr;
    dir = dir;
    r->_errno = ENOSYS;
    return -1;
}


int _close_r(struct _reent *r, int fd)
{
    fd = fd;
    r->_errno = ENOSYS;
    return -1;
}


int _fstat_r(struct _reent *r, int fd, struct stat *st)
{
    if ((fd >= STDIN_FILENO) && (fd <= STDERR_FILENO)) {
      st->st_mode = S_IFCHR;
      return 0;
    }

    r->_errno = ENOSYS;
    return -1;
}


int _isatty_r(struct _reent *r, int fd)
{
    r  = r;
    fd = fd;
    return 1;
}


void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    extern char end;   // provided by the linker script

    if (__brkval == 0)
        __brkval = &end;

    if (__brkval + incr > (char*)__get_MSP() - __malloc_margin) {
        r->_errno = ENOMEM;
        return (void*)-1;
    }

    void *ret = __brkval;
    __brkval += incr;

    return ret;
}


int _kill_r(struct _reent *r, int pid, int signal)
{
    r->_errno = ENOSYS;
    return -1;
}


int _getpid_r(struct _reent *r)
{
    r->_errno = ENOSYS;
    return -1;
}


void __malloc_lock(struct _reent *r)
{
    vPortEnterCritical();
}


void __malloc_unlock(struct _reent *r)
{
    vPortExitCritical();
}
