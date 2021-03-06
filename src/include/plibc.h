/*
     This file is part of PlibC.
     (C) 2005, 2006, 2007, 2008, 2009, 2010 Nils Durner (and other contributing authors)

	   This library is free software; you can redistribute it and/or
	   modify it under the terms of the GNU Lesser General Public
	   License as published by the Free Software Foundation; either
	   version 2.1 of the License, or (at your option) any later version.

	   This library is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	   Lesser General Public License for more details.

	   You should have received a copy of the GNU Lesser General Public
	   License along with this library; if not, write to the Free Software
	   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @file include/plibc.h
 * @brief PlibC header
 * @attention This file is usually not installed under Unix,
 *            so ship it with your application
 * @version $Revision$
 */

#ifndef _PLIBC_H_
#define _PLIBC_H_

#define _PLIBC_ "PlibC-0.1.8k"
#define _PLIBC_MAJOR_ 0
#define _PLIBC_MINOR_ 1
#define _PLIBC_PATCHLEVEL_ 8
/* One character lib mod ID */
#define _PLIBC_MOD_ 'k'
/* Defined as 1 if UTF-8 is supported in PlibC */
#define _PLIBC_UTF8_ 1

#ifndef SIGALRM
 #define SIGALRM 14
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#ifdef Q_OS_WIN32
 #define WINDOWS 1
#endif

#define HAVE_PLIBC_FD 0

#ifdef WINDOWS

#if ENABLE_NLS
  #include "langinfo.h"
#endif

#include <ws2tcpip.h>
#include <windows.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>

#define __BYTE_ORDER BYTE_ORDER
#define __BIG_ENDIAN BIG_ENDIAN

/* Conflicts with our definitions */
#define __G_WIN32_H__

/* Convert LARGE_INTEGER to double */
#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + \
  (double)((x).LowPart))
#if !defined(_stat64) && !defined(stat64)
struct _stat64
{
    _dev_t st_dev;
    _ino_t st_ino;
    _mode_t st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    __int64 st_size;
    __time64_t st_atime;
    __time64_t st_mtime;
    __time64_t st_ctime;
};
#define stat64 _stat64
#endif

struct sockaddr_un {
  short sun_family; /*AF_UNIX*/
  char sun_path[108]; /*path name */
};

#ifndef pid_t
  #define pid_t intptr_t
#endif

#ifndef error_t
  #define error_t int
#endif

#ifndef WEXITSTATUS
	#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#endif

#ifndef MSG_DONTWAIT
  #define MSG_DONTWAIT 0
#endif

enum
{
  _SC_PAGESIZE = 30,
  _SC_PAGE_SIZE = 30
};

/* Thanks to the Cygwin project */
#define PLIBCEBASE 110
#ifndef ENOCSI
  #define ENOCSI 43+PLIBCEBASE	/* No CSI structure available */
#endif /* ENOCSI */
#ifndef EL2HLT
  #define EL2HLT 44+PLIBCEBASE	/* Level 2 halted */
#endif /* EL2HLT */
#ifndef  EDEADLK
	#define EDEADLK 45+PLIBCEBASE	/* Deadlock condition */
#endif
#ifndef  ENOLCK
	#define ENOLCK 46+PLIBCEBASE	/* No record locks available */
#endif
#ifndef EBADE
  #define EBADE 50+PLIBCEBASE	/* Invalid exchange */
#endif /* EBADE */
#ifndef EBADR
  #define EBADR 51+PLIBCEBASE	/* Invalid request descriptor */
#endif /* EBADR */
#ifndef EXFULL
  #define EXFULL 52+PLIBCEBASE	/* Exchange full */
#endif /* EXFULL */
#ifndef ENOANO
  #define ENOANO 53+PLIBCEBASE	/* No anode */
#endif /* ENOANO */
#ifndef EBADRQC
  #define EBADRQC 54+PLIBCEBASE	/* Invalid request code */
#endif /* EBADRQC */
#ifndef EBADSLT
  #define EBADSLT 55+PLIBCEBASE	/* Invalid slot */
#endif /* EBADSLT */
#ifndef  EDEADLOCK
	#define EDEADLOCK EDEADLK	/* File locking deadlock error */
#endif
#ifndef EBFONT
  #define EBFONT 57+PLIBCEBASE	/* Bad font file fmt */
#endif /* EBFONT */
#ifndef ENOSTR
  #define ENOSTR 60+PLIBCEBASE	/* Device not a stream */
#endif /* ENOSTR */
#ifndef ENODATA
  #define ENODATA 61+PLIBCEBASE	/* No data (for no delay io) */
#endif /* ENODATA */
#ifndef ETIME
  #define ETIME 62+PLIBCEBASE	/* Timer expired */
#endif /* ETIME */
#ifndef ENOSR
  #define ENOSR 63+PLIBCEBASE	/* Out of streams resources */
#endif /* ENOSR */
#ifndef ENONET
  #define ENONET 64+PLIBCEBASE	/* Machine is not on the network */
#endif /* ENONET */
#ifndef ENOPKG
  #define ENOPKG 65+PLIBCEBASE	/* Package not installed */
#endif /* ENOPKG */
#ifndef EREMOTE
  #define EREMOTE 66+PLIBCEBASE	/* The object is remote */
#endif /* EREMOTE */
#ifndef ENOLINK
  #define ENOLINK 67+PLIBCEBASE	/* The link has been severed */
#endif /* ENOLINK */
#ifndef EADV
  #define EADV 68+PLIBCEBASE		/* Advertise error */
#endif /* EADV */
#ifndef ESRMNT
  #define ESRMNT 69+PLIBCEBASE	/* Srmount error */
#endif /* ESRMNT */
#ifndef ECOMM
  #define ECOMM 70+PLIBCEBASE	/* Communication error on send */
#endif /* ECOMM */
#ifndef EPROTO
  #define EPROTO 71+PLIBCEBASE	/* Protocol error */
#endif /* EPROTO */
#ifndef EMULTIHOP
  #define EMULTIHOP 74+PLIBCEBASE	/* Multihop attempted */
#endif /* EMULTIHOP */
#ifndef ELBIN
  #define ELBIN 75+PLIBCEBASE	/* Inode is remote (not really error) */
#endif /* ELBIN */
#ifndef EDOTDOT
  #define EDOTDOT 76+PLIBCEBASE	/* Cross mount point (not really error) */
#endif /* EDOTDOT */
#ifndef EBADMSG
  #define EBADMSG 77+PLIBCEBASE	/* Trying to read unreadable message */
#endif /* EBADMSG */
#ifndef ENOTUNIQ
  #define ENOTUNIQ 80+PLIBCEBASE	/* Given log. name not unique */
#endif /* ENOTUNIQ */
#ifndef EBADFD
  #define EBADFD 81+PLIBCEBASE	/* f.d. invalid for this operation */
#endif /* EBADFD */
#ifndef EREMCHG
  #define EREMCHG 82+PLIBCEBASE	/* Remote address changed */
#endif /* EREMCHG */
#ifndef ELIBACC
  #define ELIBACC 83+PLIBCEBASE	/* Can't access a needed shared lib */
#endif /* ELIBACC */
#ifndef ELIBBAD
  #define ELIBBAD 84+PLIBCEBASE	/* Accessing a corrupted shared lib */
#endif /* ELIBBAD */
#ifndef ELIBSCN
  #define ELIBSCN 85+PLIBCEBASE	/* .lib section in a.out corrupted */
#endif /* ELIBSCN */
#ifndef ELIBMAX
  #define ELIBMAX 86+PLIBCEBASE	/* Attempting to link in too many libs */
#endif /* ELIBMAX */
#ifndef ELIBEXEC
  #define ELIBEXEC 87+PLIBCEBASE	/* Attempting to exec a shared library */
#endif /* ELIBEXEC */
#ifndef  ENOSYS
	#define ENOSYS 88+PLIBCEBASE	/* Function not implemented */
#endif
#ifndef ENMFILE
  #define ENMFILE 89+PLIBCEBASE      /* No more files */
#endif /* ENMFILE */
#ifndef  ENOTEMPTY
	#define ENOTEMPTY 90+PLIBCEBASE	/* Directory not empty */
#endif
#ifndef  ENAMETOOLONG
	#define ENAMETOOLONG 91+PLIBCEBASE	/* File or path name too long */
#endif
#ifndef ELOOP
  #define ELOOP 92+PLIBCEBASE	/* Too many symbolic links */
#endif /* ELOOP */
#ifndef EOPNOTSUPP
  #define EOPNOTSUPP 95+PLIBCEBASE	/* Operation not supported on transport endpoint */
#endif /* EOPNOTSUPP */
#ifndef EPFNOSUPPORT
  #define EPFNOSUPPORT 96+PLIBCEBASE /* Protocol family not supported */
#endif /* EPFNOSUPPORT */
#ifndef ECONNRESET
  #define ECONNRESET 104+PLIBCEBASE  /* Connection reset by peer */
#endif /* ECONNRESET */
#ifndef ENOBUFS
  #define ENOBUFS 105+PLIBCEBASE	/* No buffer space available */
#endif /* ENOBUFS */
#ifndef EAFNOSUPPORT
  #define EAFNOSUPPORT 106+PLIBCEBASE /* Address family not supported by protocol family */
#endif /* EAFNOSUPPORT */
#ifndef EPROTOTYPE
  #define EPROTOTYPE 107+PLIBCEBASE	/* Protocol wrong type for socket */
#endif /* EPROTOTYPE */
#ifndef ENOTSOCK
  #define ENOTSOCK 108+PLIBCEBASE	/* Socket operation on non-socket */
#endif /* ENOTSOCK */
#ifndef ENOPROTOOPT
  #define ENOPROTOOPT 109+PLIBCEBASE	/* Protocol not available */
#endif /* ENOPROTOOPT */
#ifndef ESHUTDOWN
  #define ESHUTDOWN 110+PLIBCEBASE	/* Can't send after socket shutdown */
#endif /* ESHUTDOWN */
#ifndef ECONNREFUSED
  #define ECONNREFUSED 111+PLIBCEBASE	/* Connection refused */
#endif /* ECONNREFUSED */
#ifndef EADDRINUSE
  #define EADDRINUSE 112+PLIBCEBASE		/* Address already in use */
#endif /* EADDRINUSE */
#ifndef ECONNABORTED
  #define ECONNABORTED 113+PLIBCEBASE	/* Connection aborted */
#endif /* ECONNABORTED */
#ifndef ENETUNREACH
  #define ENETUNREACH 114+PLIBCEBASE		/* Network is unreachable */
#endif /* ENETUNREACH */
#ifndef ENETDOWN
  #define ENETDOWN 115+PLIBCEBASE		/* Network interface is not configured */
#endif /* ENETDOWN */
#ifndef  ETIMEDOUT
	#define ETIMEDOUT 116+PLIBCEBASE		/* Connection timed out */
#endif
#ifndef EHOSTDOWN
  #define EHOSTDOWN 117+PLIBCEBASE		/* Host is down */
#endif /* EHOSTDOWN */
#ifndef EHOSTUNREACH
  #define EHOSTUNREACH 118+PLIBCEBASE	/* Host is unreachable */
#endif /* EHOSTUNREACH */
#ifndef EINPROGRESS
  #define EINPROGRESS 119+PLIBCEBASE		/* Connection already in progress */
#endif /* EINPROGRESS */
#ifndef EALREADY
  #define EALREADY 120+PLIBCEBASE		/* Socket already connected */
#endif /* EALREADY */
#ifndef EDESTADDRREQ
  #define EDESTADDRREQ 121+PLIBCEBASE	/* Destination address required */
#endif /* EDESTADDRREQ */
#ifndef EMSGSIZE
  #define EMSGSIZE 122+PLIBCEBASE		/* Message too long */
#endif /* EMSGSIZE */
#ifndef EPROTONOSUPPORT
  #define EPROTONOSUPPORT 123+PLIBCEBASE	/* Unknown protocol */
#endif /* EPROTONOSUPPORT */
#ifndef ESOCKTNOSUPPORT
  #define ESOCKTNOSUPPORT 124+PLIBCEBASE	/* Socket type not supported */
#endif /* ESOCKTNOSUPPORT */
#ifndef EADDRNOTAVAIL
  #define EADDRNOTAVAIL 125+PLIBCEBASE	/* Address not available */
#endif /* EADDRNOTAVAIL */
#ifndef ENETRESET
  #define ENETRESET 126+PLIBCEBASE		/* Connection aborted by network */
#endif /* ENETRESET */
#ifndef EISCONN
  #define EISCONN 127+PLIBCEBASE		    /* Socket is already connected */
#endif /* EISCONN */
#ifndef ENOTCONN
  #define ENOTCONN 128+PLIBCEBASE		/* Socket is not connected */
#endif /* ENOTCONN */
#ifndef ETOOMANYREFS
  #define ETOOMANYREFS 129+PLIBCEBASE	/* Too many references: cannot splice */
#endif /* ETOOMANYREFS */
#ifndef EPROCLIM
  #define EPROCLIM 130+PLIBCEBASE		/* Too many processes */
#endif /* EPROCLIM */
#ifndef EUSERS
  #define EUSERS 131+PLIBCEBASE			/* Too many users */
#endif /* EUSERS */
#ifndef EDQUOT
  #define EDQUOT 132+PLIBCEBASE			/* Disk quota exceeded */
#endif /* EDQUOT */
#ifndef ESTALE
  #define ESTALE 133+PLIBCEBASE          /* Unknown error */
#endif /* ESTALE */
#ifndef  ENOTSUP
	#define ENOTSUP 134+PLIBCEBASE		    /* Not supported */
#endif
#ifndef ENOMEDIUM
  #define ENOMEDIUM 135+PLIBCEBASE       /* No medium (in tape drive) */
#endif /* ENOMEDIUM */
#ifndef ENOSHARE
  #define ENOSHARE 136+PLIBCEBASE        /* No such host or network path */
#endif /* ENOSHARE */
#ifndef ECASECLASH
  #define ECASECLASH 137+PLIBCEBASE      /* Filename exists with different case */
#endif /* ECASECLASH */
#ifndef EWOULDBLOCK
  #define EWOULDBLOCK EAGAIN	/* Operation would block */
#endif /* EWOULDBLOCK */
#ifndef EOVERFLOW
  #define EOVERFLOW 139+PLIBCEBASE /* Value too large for defined data type */
#endif /* EOVERFLOW */

#undef HOST_NOT_FOUND
#define HOST_NOT_FOUND 1
#undef TRY_AGAIN
#define TRY_AGAIN 2
#undef NO_RECOVERY
#define NO_RECOVERY 3
#undef NO_ADDRESS
#define NO_ADDRESS 4

#define PROT_READ   0x1
#define PROT_WRITE  0x2
#define MAP_SHARED  0x1
#define MAP_PRIVATE 0x2 /* unsupported */
#define MAP_FIXED   0x10
#define MAP_ANONYMOUS 0x20 /* unsupported */
#define MAP_FAILED  ((void *)-1)

#define MS_ASYNC        1       /* sync memory asynchronously */
#define MS_INVALIDATE   2       /* invalidate the caches */
#define MS_SYNC         4       /* synchronous memory sync */

struct statfs
{
  long f_type;                  /* type of filesystem (see below) */
  long f_bsize;                 /* optimal transfer block size */
  long f_blocks;                /* total data blocks in file system */
  long f_bfree;                 /* free blocks in fs */
  long f_bavail;                /* free blocks avail to non-superuser */
  long f_files;                 /* total file nodes in file system */
  long f_ffree;                 /* free file nodes in fs */
  long f_fsid;                  /* file system id */
  long f_namelen;               /* maximum length of filenames */
  long f_spare[6];              /* spare for later */
};

/* Taken from the Wine project <http://www.winehq.org>
    /wine/include/winternl.h */
enum SYSTEM_INFORMATION_CLASS
{
  SystemBasicInformation = 0,
  Unknown1,
  SystemPerformanceInformation = 2,
  SystemTimeOfDayInformation = 3, /* was SystemTimeInformation */
  Unknown4,
  SystemProcessInformation = 5,
  Unknown6,
  Unknown7,
  SystemProcessorPerformanceInformation = 8,
  Unknown9,
  Unknown10,
  SystemDriverInformation,
  Unknown12,
  Unknown13,
  Unknown14,
  Unknown15,
  SystemHandleList,
  Unknown17,
  Unknown18,
  Unknown19,
  Unknown20,
  SystemCacheInformation,
  Unknown22,
  SystemInterruptInformation = 23,
  SystemExceptionInformation = 33,
  SystemRegistryQuotaInformation = 37,
  SystemLookasideInformation = 45
};

typedef struct
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER Reserved1[2];
    ULONG Reserved2;
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

#define sleep(secs) (Sleep(secs * 1000))

/*********************** statfs *****************************/
/* fake block size */
#define FAKED_BLOCK_SIZE 512

/* linux-compatible values for fs type */
#define MSDOS_SUPER_MAGIC     0x4d44
#define NTFS_SUPER_MAGIC      0x5346544E

/*********************** End of statfs ***********************/

#define SHUT_RDWR SD_BOTH

/* Operations for flock() */
#define LOCK_SH  1       /* shared lock */
#define LOCK_EX  2       /* exclusive lock */
#define LOCK_NB  4       /* or'd with one of the above to prevent
                            blocking */
#define LOCK_UN  8       /* remove lock */

/* Not supported under MinGW */
#define S_IRGRP 0
#define S_IWGRP 0
#define S_IROTH 0
#define S_IXGRP 0
#define S_IWOTH 0
#define S_IXOTH 0
#define S_ISUID 0
#define S_ISGID 0
#define S_ISVTX 0
#define S_IRWXG 0
#define S_IRWXO 0

#define SHUT_WR SD_SEND
#define SHUT_RD SD_RECEIVE
#define SHUT_RDWR SD_BOTH

#define SIGKILL 9
#define SIGTERM 15

#define SetErrnoFromWinError(e) _SetErrnoFromWinError(e, __FILE__, __LINE__)

BOOL _plibc_CreateShortcut(const char *pszSrc, const char *pszDest);
BOOL _plibc_CreateShortcutW(const wchar_t *pwszSrc, const wchar_t *pwszDest);
BOOL _plibc_DereferenceShortcut(char *pszShortcut);
BOOL _plibc_DereferenceShortcutW(wchar_t *pwszShortcut);
char *plibc_ChooseDir(char *pszTitle, unsigned long ulFlags);
wchar_t *plibc_ChooseDirW(wchar_t *pwszTitle, unsigned long ulFlags);
char *plibc_ChooseFile(char *pszTitle, unsigned long ulFlags);
wchar_t *plibc_ChooseFileW(wchar_t *pwszTitle, unsigned long ulFlags);

long QueryRegistry(HKEY hMainKey, const char *pszKey, const char *pszSubKey,
              char *pszBuffer, long *pdLength);
long QueryRegistryW(HKEY hMainKey, const wchar_t *pszKey, const wchar_t *pszSubKey,
              wchar_t *pszBuffer, long *pdLength);

BOOL __win_IsHandleMarkedAsBlocking(intptr_t hHandle);
void __win_SetHandleBlockingMode(intptr_t s, BOOL bBlocking);
void __win_DiscardHandleBlockingMode(intptr_t s);
int _win_isSocketValid(intptr_t s);
int plibc_conv_to_win_path(const char *pszUnix, char *pszWindows, size_t pszWindows_buff_length);
int plibc_conv_to_win_pathw(const wchar_t *pszUnix, wchar_t *pwszWindows, size_t pszWindows_buff_length);

int plibc_conv_to_win_pathwconv(const char *pszUnix, wchar_t *pwszWindows, size_t pszWindows_buff_length);
int plibc_conv_to_win_pathwconv_ex(const char *pszUnix, wchar_t *pszWindows, size_t pszWindows_buff_length, int derefLinks);

unsigned plibc_get_handle_count();

typedef void (*TPanicProc) (int, char *);
void plibc_set_panic_proc(TPanicProc proc);

int flock(int fd, int operation);
int fsync(int fildes);
int inet_pton(int af, const char *src, void *dst);
int inet_pton4(const char *src, u_char *dst, int pton);
#if USE_IPV6
int inet_pton6(const char *src, u_char *dst);
#endif
#ifndef FTRUNCATE_DEFINED
int truncate(const char *fname, int distance);
#endif /* FTRUNCATE_DEFINED */
int statfs(const char *path, struct statfs *buf);
const char *hstrerror(int err);
int mkstemp(char *tmplate);
char *strptime (const char *buf, const char *format, struct tm *tm);
const char *inet_ntop(int af, const void *src, char *dst, size_t size);
#ifndef gmtime_r
struct tm *gmtime_r(const time_t *clock, struct tm *result);
#endif

int plibc_init(char *pszOrg, char *pszApp);
int plibc_init_utf8(char *pszOrg, char *pszApp, int utf8_mode);
void plibc_shutdown();
int plibc_initialized();

void _SetErrnoFromWinError(long lWinError, char *pszCaller, int iLine);
void SetErrnoFromWinsockError(long lWinError);
void SetHErrnoFromWinError(long lWinError);
void SetErrnoFromHRESULT(HRESULT hRes);
int GetErrnoFromWinsockError(long lWinError);
FILE *_win_fopen(const char *filename, const char *mode);
int _win_fclose(FILE *);
DIR *_win_opendir(const char *dirname);
struct dirent *_win_readdir(DIR *dirp);
int _win_closedir(DIR *dirp);
int _win_open(const char *filename, int oflag, ...);
#ifdef ENABLE_NLS
char *_win_bindtextdomain(const char *domainname, const char *dirname);
#endif
int _win_chdir(const char *path);
int _win_close(intptr_t fd);
int _win_creat(const char *path, mode_t mode);
char *_win_ctime(const time_t *clock);
char *_win_ctime_r(const time_t *clock, char *buf);
int _win_fstat(int handle, struct _stat *buffer);
off_t _win_lseek(int fildes, off_t offset, int whence);
int _win_ftruncate(int fildes, off_t length);
void _win_gettimeofday(struct timeval *tp, void *tzp);
int _win_kill(pid_t pid, int sig);
int _win_pipe(intptr_t *phandles);
intptr_t _win_mkfifo(const char *path, mode_t mode);
int _win_rmdir(const char *path);
int _win_access( const char *path, int mode );
int _win_chmod(const char *filename, int pmode);
char *realpath(const char *file_name, char *resolved_name, size_t resolv_buffer_size);
long _win_random(void);
void _win_srandom(unsigned int seed);
int _win_remove(const char *path);
int _win_rename(const char *oldname, const char *newname);
int _win_stat(const char *path, struct _stat *buffer);
int _win_stat64(const char *path, struct stat64 *buffer);
long _win_sysconf(int name);
int _win_unlink(const char *filename);
int _win_write(int fildes, const void *buf, size_t nbyte);
int _win_read(int fildes, void *buf, size_t nbyte);
size_t _win_fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
size_t _win_fread( void *buffer, size_t size, size_t count, FILE *stream );
int _win_symlink(const char *path1, const char *path2);
void *_win_mmap(void *start, size_t len, int access, int flags, int fd,
                uint64_t offset);
int _win_msync(void *start, size_t length, int flags);
int _win_munmap(void *start, size_t length);
int _win_lstat(const char *path, struct _stat *buf);
int _win_lstat64(const char *path, struct stat64 *buf);
int _win_readlink(const char *path, char *buf, size_t bufsize);

int _win_printf(const char *format,...);
int _win_wprintf(const wchar_t *format, ...);

int _win_fprintf(FILE *f,const char *format,...);
int _win_fwprintf(FILE *f,const wchar_t *format, ...);

int _win_vprintf(const char *format, va_list ap);
int _win_vfwprintf(FILE *stream, const wchar_t *format, va_list arg_ptr);

int _win_vfprintf(FILE *stream, const char *format, va_list arg_ptr);
int _win_vwprintf(const wchar_t *format, va_list ap);

int _win_vsprintf(char *dest,const char *format, va_list arg_ptr);
int _win_vswprintf(wchar_t *dest, const wchar_t *format, va_list arg_ptr);

int _win_vsnprintf(char* str, size_t size, const char *format, va_list arg_ptr);
int _win_vsnwprintf(wchar_t* wstr, size_t size, const wchar_t *format, va_list arg_ptr);

int _win_snprintf(char *str,size_t size,const char *format,...);
int _win_snwprintf(wchar_t *str, size_t size, const wchar_t *format, ...);

int _win_sprintf(char *dest,const char *format,...);
int _win_swprintf(wchar_t *dest, const wchar_t *format, ...);

int _win_vsscanf(const char* str, const char* format, va_list arg_ptr);
int _win_vswscanf(const wchar_t* wstr, const wchar_t* format, va_list arg_ptr);

int _win_sscanf(const char *str, const char *format, ...);
int _win_swscanf(const wchar_t *wstr, const wchar_t *format, ...);

int _win_vfscanf(FILE *stream, const char *format, va_list arg_ptr);
int _win_vfwscanf(FILE *stream, const wchar_t *format, va_list arg_ptr);

int _win_vscanf(const char *format, va_list arg_ptr);
int _win_vwscanf(const wchar_t *format, va_list arg_ptr);

int _win_scanf(const char *format, ...);
int _win_wscanf(const wchar_t *format, ...);

int _win_fscanf(FILE *stream, const char *format, ...);
int _win_fwscanf(FILE *stream, const wchar_t *format, ...);


pid_t _win_waitpid(pid_t pid, int *stat_loc, int options);
intptr_t _win_accept(intptr_t s, struct sockaddr *addr, int *addrlen);
intptr_t _win_bind(intptr_t s, const struct sockaddr *name, int namelen);
int _win_connect(intptr_t s, const struct sockaddr *name, int namelen);
int _win_getpeername(intptr_t s, struct sockaddr *name,
                int *namelen);
int _win_getsockname(intptr_t s, struct sockaddr *name,
                int *namelen);
int _win_getsockopt(intptr_t s, int level, int optname, char *optval, int *optlen);
int _win_listen(intptr_t s, int backlog);
int _win_recv(intptr_t s, char *buf, int len, int flags);
int _win_recvfrom(intptr_t s, void *buf, int len, int flags,
             struct sockaddr *from, int *fromlen);
int _win_select(int max_fd, fd_set * rfds, fd_set * wfds, fd_set * efds,
                const struct timeval *tv);
int _win_send(intptr_t s, const char *buf, int len, int flags);
int _win_sendto(intptr_t s, const char *buf, int len, int flags,
                const struct sockaddr *to, int tolen);
int _win_setsockopt(intptr_t s, int level, int optname, const void *optval,
                    int optlen);
int _win_shutdown(intptr_t s, int how);
intptr_t _win_socket(int af, int type, int protocol);
struct hostent *_win_gethostbyaddr(const char *addr, int len, int type);
struct hostent *_win_gethostbyname(const char *name);
struct hostent *gethostbyname2(const char *name, int af);
char *_win_strerror(int errnum);
int IsWinNT();
char *index(const char *s, int c);

#if !HAVE_STRNDUP
char *strndup (const char *s, size_t n);
#endif
#if !HAVE_STRNLEN
#if !defined(__MINGW64_VERSION_MAJOR) && !defined(_INC_STRING)
size_t strnlen (const char *str, size_t maxlen);
#endif
#endif
char *stpcpy(char *dest, const char *src);
char *strcasestr(const char *haystack_start, const char *needle_start);
#ifndef __MINGW64_VERSION_MAJOR
#define strcasecmp(a, b) stricmp(a, b)
#define strncasecmp(a, b, c) strnicmp(a, b, c)
#endif
#define wcscasecmp(a, b) wcsicmp(a, b)
#define wcsncasecmp(a, b, c) wcsnicmp(a, b, c)
#endif /* WINDOWS */

#ifndef WINDOWS
 #define DIR_SEPARATOR '/'
 #define DIR_SEPARATOR_STR "/"
 #define PATH_SEPARATOR ':'
 #define PATH_SEPARATOR_STR ":"
 #define NEWLINE "\n"

#ifdef ENABLE_NLS
 #define BINDTEXTDOMAIN(d, n) bindtextdomain(d, n)
#endif
 #define CREAT(p, m) creat(p, m)
 #define PLIBC_CTIME(c) ctime(c)
 #define CTIME_R(c, b) ctime_r(c, b)
 #undef FOPEN
 #define FOPEN(f, m) fopen(f, m)
 #define FCLOSE(f) fclose(f)
 #define FTRUNCATE(f, l) ftruncate(f, l)
 #define OPENDIR(d) opendir(d)
 #define CLOSEDIR(d) closedir(d)
 #define READDIR(d) readdir(d)
 #define OPEN open
 #define CHDIR(d) chdir(d)
 #define CLOSE(f) close(f)
 #define LSEEK(f, o, w) lseek(f, o, w)
 #define RMDIR(f) rmdir(f)
 #define ACCESS(p, m) access(p, m)
 #define CHMOD(f, p) chmod(f, p)
 #define FSTAT(h, b) fstat(h, b)
 #define PLIBC_KILL(p, s) kill(p, s)
 #define PIPE(h) pipe(h)
 #define REMOVE(p) remove(p)
 #define RENAME(o, n) rename(o, n)
 #define STAT(p, b) stat(p, b)
 #define STAT64(p, b) stat64(p, b)
 #define SYSCONF(n) sysconf(n)
 #define UNLINK(f) unlink(f)
 #define WRITE(f, b, n) write(f, b, n)
 #define READ(f, b, n) read(f, b, n)
 #define GN_FREAD(b, s, c, f) fread(b, s, c, f)
 #define GN_FWRITE(b, s, c, f) fwrite(b, s, c, f)
 #define SYMLINK(a, b) symlink(a, b)
 #define MMAP(s, l, p, f, d, o) mmap(s, l, p, f, d, o)
 #define MKFIFO(p, m) mkfifo(p, m)
 #define MSYNC(s, l, f) msync(s, l, f)
 #define MUNMAP(s, l) munmap(s, l)
 #define STRERROR(i) strerror(i)
 #define RANDOM() random()
 #define SRANDOM(s) srandom(s)
 #define READLINK(p, b, s) readlink(p, b, s)
 #define LSTAT(p, b) lstat(p, b)
 #define LSTAT64(p, b) lstat64(p, b)
 #define PRINTF printf
 #define FPRINTF fprintf
 #define VPRINTF(f, a) vprintf(f, a)
 #define VFPRINTF(s, f, a) vfprintf(s, f, a)
 #define VSPRINTF(d, f, a) vsprintf(d, f, a)
 #define VSNPRINTF(str, size, fmt, a) vsnprintf(str, size, fmt, a)
 #define _REAL_SNPRINTF snprintf
 #define SPRINTF sprintf
 #define VSSCANF(s, f, a) vsscanf(s, f, a)
 #define SSCANF sscanf
 #define VFSCANF(s, f, a) vfscanf(s, f, a)
 #define VSCANF(f, a) vscanf(f, a)
 #define SCANF scanf
 #define FSCANF fscanf
 #define WAITPID(p, s, o) waitpid(p, s, o)
 #define ACCEPT(s, a, l) accept(s, a, l)
 #define BIND(s, n, l) bind(s, n, l)
 #define CONNECT(s, n, l) connect(s, n, l)
 #define GETPEERNAME(s, n, l) getpeername(s, n, l)
 #define GETSOCKNAME(s, n, l) getsockname(s, n, l)
 #define GETSOCKOPT(s, l, o, v, p) getsockopt(s, l, o, v, p)
 #define LISTEN(s, b) listen(s, b)
 #define RECV(s, b, l, f) recv(s, b, l, f)
 #define RECVFROM(s, b, l, f, r, o) recvfrom(s, b, l, f, r, o)
 #define SELECT(n, r, w, e, t) select(n, r, w, e, t)
 #define SEND(s, b, l, f) send(s, b, l, f)
 #define SENDTO(s, b, l, f, o, n) sendto(s, b, l, f, o, n)
 #define SETSOCKOPT(s, l, o, v, n) setsockopt(s, l, o, v, n)
 #define SHUTDOWN(s, h) shutdown(s, h)
 #define SOCKET(a, t, p) socket(a, t, p)
 #define GETHOSTBYADDR(a, l, t) gethostbyaddr(a, l, t)
 #define GETHOSTBYNAME(n) gethostbyname(n)
 #define GETTIMEOFDAY(t, n) gettimeofday(t, n)
 #define INSQUE(e, p) insque(e, p)
 #define REMQUE(e) remque(e)
 #define HSEARCH(i, a) hsearch(i, a)
 #define HCREATE(n) hcreate(n)
 #define HDESTROY() hdestroy()
 #define HSEARCH_R(i, a, r, h) hsearch_r(i, a, r, h)
 #define HCREATE_R(n, h) hcreate_r(n, h)
 #define HDESTROY_R(h) hdestroy_r(h)
 #define TSEARCH(k, r, c) tsearch(k, r, c)
 #define TFIND(k, r, c) tfind(k, r, c)
 #define TDELETE(k, r, c) tdelete(k, r, c)
 #define TWALK(r, a) twalk(r, a)
 #define TDESTROY(r, f) tdestroy(r, f)
 #define LFIND(k, b, n, s, c) lfind(k, b, n, s, c)
 #define LSEARCH(k, b, n, s, c) lsearch(k, b, n, s, c)
#else
 #define DIR_SEPARATOR '\\'
 #define DIR_SEPARATOR_STR "\\"
 #define PATH_SEPARATOR ';'
 #define PATH_SEPARATOR_STR ";"
 #define NEWLINE "\r\n"

#ifdef ENABLE_NLS
 #define BINDTEXTDOMAIN(d, n) _win_bindtextdomain(d, n)
#endif
 #define CREAT(p, m) _win_creat(p, m)
 #define PLIBC_CTIME(c) _win_ctime(c)
 #define CTIME_R(c, b) _win_ctime_r(c, b)
 #define FOPEN(f, m) _win_fopen(f, m)
 #define FCLOSE(f) _win_fclose(f)
 #define FTRUNCATE(f, l) _win_ftruncate(f, l)
 #define OPENDIR(d) _win_opendir(d)
 #define CLOSEDIR(d) _win_closedir(d)
 #define READDIR(d) _win_readdir(d)
 #define OPEN _win_open
 #define CHDIR(d) _win_chdir(d)
 #define CLOSE(f) _win_close(f)
 #define PLIBC_KILL(p, s) _win_kill(p, s)
 #define LSEEK(f, o, w) _win_lseek(f, o, w)
 #define FSTAT(h, b) _win_fstat(h, b)
 #define RMDIR(f) _win_rmdir(f)
 #define ACCESS(p, m) _win_access(p, m)
 #define CHMOD(f, p) _win_chmod(f, p)
 #define PIPE(h) _win_pipe(h)
 #define RANDOM() _win_random()
 #define SRANDOM(s) _win_srandom(s)
 #define REMOVE(p) _win_remove(p)
 #define RENAME(o, n) _win_rename(o, n)
 #define STAT(p, b) _win_stat(p, b)
 #define STAT64(p, b) _win_stat64(p, b)
 #define SYSCONF(n) _win_sysconf(n)
 #define UNLINK(f) _win_unlink(f)
 #define WRITE(f, b, n) _win_write(f, b, n)
 #define READ(f, b, n) _win_read(f, b, n)
 #define GN_FREAD(b, s, c, f) _win_fread(b, s, c, f)
 #define GN_FWRITE(b, s, c, f) _win_fwrite(b, s, c, f)
 #define SYMLINK(a, b) _win_symlink(a, b)
 #define MMAP(s, l, p, f, d, o) _win_mmap(s, l, p, f, d, o)
 #define MKFIFO(p, m) _win_mkfifo(p, m)
 #define MSYNC(s, l, f) _win_msync(s, l, f)
 #define MUNMAP(s, l) _win_munmap(s, l)
 #define STRERROR(i) _win_strerror(i)
 #define READLINK(p, b, s) _win_readlink(p, b, s)
 #define LSTAT(p, b) _win_lstat(p, b)
 #define LSTAT64(p, b) _win_lstat64(p, b)
 #define PRINTF(f, ...) _win_printf(f , __VA_ARGS__)
 #define FPRINTF(fil, fmt, ...) _win_fprintf(fil, fmt, __VA_ARGS__)
 #define VPRINTF(f, a) _win_vprintf(f, a)
 #define VFPRINTF(s, f, a) _win_vfprintf(s, f, a)
 #define VSPRINTF(d, f, a) _win_vsprintf(d, f, a)
 #define VSNPRINTF(str, size, fmt, a) _win_vsnprintf(str, size, fmt, a)
 #define _REAL_SNPRINTF(str, size, fmt, ...) _win_snprintf(str, size, fmt, __VA_ARGS__)
 #define SPRINTF(d, f, ...) _win_sprintf(d, f, __VA_ARGS__)
 #define VSSCANF(s, f, a) _win_vsscanf(s, f, a)
 #define SSCANF(s, f, ...) _win_sscanf(s, f, __VA_ARGS__)
 #define VFSCANF(s, f, a) _win_vfscanf(s, f, a)
 #define VSCANF(f, a) _win_vscanf(f, a)
 #define SCANF(f, ...) _win_scanf(f, __VA_ARGS__)
 #define FSCANF(s, f, ...) _win_fscanf(s, f, __VA_ARGS__)
 #define WAITPID(p, s, o) _win_waitpid(p, s, o)
 #define ACCEPT(s, a, l) _win_accept(s, a, l)
 #define BIND(s, n, l) _win_bind(s, n, l)
 #define CONNECT(s, n, l) _win_connect(s, n, l)
 #define GETPEERNAME(s, n, l) _win_getpeername(s, n, l)
 #define GETSOCKNAME(s, n, l) _win_getsockname(s, n, l)
 #define GETSOCKOPT(s, l, o, v, p) _win_getsockopt(s, l, o, v, p)
 #define LISTEN(s, b) _win_listen(s, b)
 #define RECV(s, b, l, f) _win_recv(s, b, l, f)
 #define RECVFROM(s, b, l, f, r, o) _win_recvfrom(s, b, l, f, r, o)
 #define SELECT(n, r, w, e, t) _win_select(n, r, w, e, t)
 #define SEND(s, b, l, f) _win_send(s, b, l, f)
 #define SENDTO(s, b, l, f, o, n) _win_sendto(s, b, l, f, o, n)
 #define SETSOCKOPT(s, l, o, v, n) _win_setsockopt(s, l, o, v, n)
 #define SHUTDOWN(s, h) _win_shutdown(s, h)
 #define SOCKET(a, t, p) _win_socket(a, t, p)
 #define GETHOSTBYADDR(a, l, t) _win_gethostbyaddr(a, l, t)
 #define GETHOSTBYNAME(n) _win_gethostbyname(n)
 #define GETTIMEOFDAY(t, n) _win_gettimeofday(t, n)
 #define INSQUE(e, p) _win_insque(e, p)
 #define REMQUE(e) _win_remque(e)
 #define HSEARCH(i, a) _win_hsearch(i, a)
 #define HCREATE(n) _win_hcreate(n)
 #define HDESTROY() _win_hdestroy()
 #define HSEARCH_R(i, a, r, h) _win_hsearch_r(i, a, r, h)
 #define HCREATE_R(n, h) _win_hcreate_r(n, h)
 #define HDESTROY_R(h) _win_hdestroy_r(h)
 #define TSEARCH(k, r, c) _win_tsearch(k, r, c)
 #define TFIND(k, r, c) _win_tfind(k, r, c)
 #define TDELETE(k, r, c) _win_tdelete(k, r, c)
 #define TWALK(r, a) _win_twalk(r, a)
 #define TDESTROY(r, f) _win_tdestroy(r, f)
 #define LFIND(k, b, n, s, c) _win_lfind(k, b, n, s, c)
 #define LSEARCH(k, b, n, s, c) _win_lsearch(k, b, n, s, c)
#endif

/* search.h */

/* Prototype structure for a linked-list data structure.
   This is the type used by the `insque' and `remque' functions.  */

struct PLIBC_SEARCH_QELEM
  {
    struct qelem *q_forw;
    struct qelem *q_back;
    char q_data[1];
  };


/* Insert ELEM into a doubly-linked list, after PREV.  */
void _win_insque (void *__elem, void *__prev);

/* Unlink ELEM from the doubly-linked list that it is in.  */
void _win_remque (void *__elem);


/* For use with hsearch(3).  */
typedef int (*PLIBC_SEARCH__compar_fn_t) (__const void *, __const void *);

typedef PLIBC_SEARCH__compar_fn_t _win_comparison_fn_t;

/* Action which shall be performed in the call the hsearch.  */
typedef enum
  {
    PLIBC_SEARCH_FIND,
    PLIBC_SEARCH_ENTER
  }
PLIBC_SEARCH_ACTION;

typedef struct PLIBC_SEARCH_entry
  {
    char *key;
    void *data;
  }
PLIBC_SEARCH_ENTRY;

/* The reentrant version has no static variables to maintain the state.
   Instead the interface of all functions is extended to take an argument
   which describes the current status.  */
typedef struct _PLIBC_SEARCH_ENTRY
{
  unsigned int used;
  PLIBC_SEARCH_ENTRY entry;
}
_PLIBC_SEARCH_ENTRY;


/* Family of hash table handling functions.  The functions also
   have reentrant counterparts ending with _r.  The non-reentrant
   functions all work on a signle internal hashing table.  */

/* Search for entry matching ITEM.key in internal hash table.  If
   ACTION is `FIND' return found entry or signal error by returning
   NULL.  If ACTION is `ENTER' replace existing data (if any) with
   ITEM.data.  */
PLIBC_SEARCH_ENTRY *_win_hsearch (PLIBC_SEARCH_ENTRY __item, PLIBC_SEARCH_ACTION __action);

/* Create a new hashing table which will at most contain NEL elements.  */
int _win_hcreate (size_t __nel);

/* Destroy current internal hashing table.  */
void _win_hdestroy (void);

/* Data type for reentrant functions.  */
struct PLIBC_SEARCH_hsearch_data
  {
    struct _PLIBC_SEARCH_ENTRY *table;
    unsigned int size;
    unsigned int filled;
  };

/* Reentrant versions which can handle multiple hashing tables at the
   same time.  */
int _win_hsearch_r (PLIBC_SEARCH_ENTRY __item, PLIBC_SEARCH_ACTION __action, PLIBC_SEARCH_ENTRY **__retval,
          struct PLIBC_SEARCH_hsearch_data *__htab);
int _win_hcreate_r (size_t __nel, struct PLIBC_SEARCH_hsearch_data *__htab);
void _win_hdestroy_r (struct PLIBC_SEARCH_hsearch_data *__htab);


/* The tsearch routines are very interesting. They make many
   assumptions about the compiler.  It assumes that the first field
   in node must be the "key" field, which points to the datum.
   Everything depends on that.  */
/* For tsearch */
typedef enum
{
  PLIBC_SEARCH_preorder,
  PLIBC_SEARCH_postorder,
  PLIBC_SEARCH_endorder,
  PLIBC_SEARCH_leaf
}
PLIBC_SEARCH_VISIT;

/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP and insert a new element if not found.  */
void *_win_tsearch (__const void *__key, void **__rootp,
          PLIBC_SEARCH__compar_fn_t __compar);

/* Search for an entry matching the given KEY in the tree pointed to
   by *ROOTP.  If no matching entry is available return NULL.  */
void *_win_tfind (__const void *__key, void *__const *__rootp,
        PLIBC_SEARCH__compar_fn_t __compar);

/* Remove the element matching KEY from the tree pointed to by *ROOTP.  */
void *_win_tdelete (__const void *__restrict __key,
          void **__restrict __rootp,
          PLIBC_SEARCH__compar_fn_t __compar);

typedef void (*PLIBC_SEARCH__action_fn_t) (__const void *__nodep, PLIBC_SEARCH_VISIT __value,
             int __level);

/* Walk through the whole tree and call the ACTION callback for every node
   or leaf.  */
void _win_twalk (__const void *__root, PLIBC_SEARCH__action_fn_t __action);

/* Callback type for function to free a tree node.  If the keys are atomic
   data this function should do nothing.  */
typedef void (*PLIBC_SEARCH__free_fn_t) (void *__nodep);

/* Destroy the whole tree, call FREEFCT for each node or leaf.  */
void _win_tdestroy (void *__root, PLIBC_SEARCH__free_fn_t __freefct);


/* Perform linear search for KEY by comparing by COMPAR in an array
   [BASE,BASE+NMEMB*SIZE).  */
void *_win_lfind (__const void *__key, __const void *__base,
        size_t *__nmemb, size_t __size, PLIBC_SEARCH__compar_fn_t __compar);

/* Perform linear search for KEY by comparing by COMPAR function in
   array [BASE,BASE+NMEMB*SIZE) and insert entry if not found.  */
void *_win_lsearch (__const void *__key, void *__base,
          size_t *__nmemb, size_t __size, PLIBC_SEARCH__compar_fn_t __compar);


#ifdef __cplusplus
}
#endif


#endif //_PLIBC_H_

/* end of plibc.h */
