/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * libnewlib glue code
 *
 * Authors: Felipe Huici <felipe.huici@neclab.eu>
 *          Florian Schmidt <florian.schmidt@neclab.eu>
 *
 * Copyright (c) 2017, NEC Europe Ltd., NEC Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * THIS HEADER MAY NOT BE EXTRACTED OR MODIFIED IN ANY WAY.
 */

#include <uk/plat/console.h>
#include <sys/stat.h>
#include <errno.h>
#undef errno
extern int errno;

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

int open(const char *name __unused, int flags __unused, int mode __unused)
{
	return -1;
}

int close(int file __unused)
{
	return -1;
}

int fstat(int file __unused, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int stat(const char *path __unused, struct stat *buf __unused)
{
	return -1;
}

int mkdir(const char *_path __unused, mode_t __mode __unused)
{
	return -1;
}

int link(char *old __unused, char *new __unused)
{
	errno = EMLINK;
	return -1;
}

int unlink(char *name __unused)
{
	errno = ENOENT;
	return -1;
}

int read(int file, char *ptr, int len)
{
	int read;

	switch (file) {
	case STDIN_FILENO:
		while ((read = ukplat_cink(ptr, len)) == 0)
			continue; /* busy wait */
		return read;
	case STDOUT_FILENO:
	case STDERR_FILENO:
		errno = EBADF;
		return -1;
	default:
		errno = EBADF;
		return -1;
	}
}

int write(int file, char *ptr, int len)
{
	switch (file) {
	case STDIN_FILENO:
		errno = EBADF;
		return -1;
	case STDOUT_FILENO:
		return ukplat_coutk(ptr, len);
	case STDERR_FILENO:
		return ukplat_coutd(ptr, len);
	default:
		errno = EBADF;
		return -1;
	}
}

int lseek(int file __unused, int ptr __unused, int dir __unused)
{
	return 0;
}

int chmod(const char *pathname __unused, mode_t mode __unused)
{
	return 0;
}

int access(const char *path __unused, int amode __unused)
{
	return 0;
}

int chdir(const char *path __unused)
{
	return 0;
}

#include <dirent.h>
int closedir(DIR *dirp __unused)
{
	return 0;
}

void rewinddir(DIR *dirp __unused)
{
}

struct dirent *readdir(DIR *dirp __unused)
{
	return NULL;
}

DIR *opendir(const char *dirname __unused)
{
	return NULL;
}

DIR *fdopendir(int fd __unused)
{
	return NULL;
}

int rmdir(const char *path __unused)
{
	return 0;
}

mode_t umask(mode_t cmask __unused)
{
	return 0;
}

long pathconf(const char *path __unused, int name __unused)
{
	return 0;
}

int dup2(int oldfd __unused, int newfd __unused)
{
	return 0;
}

#include <sys/mman.h>
void *mmap(void *addr __unused, size_t len __unused, int prot __unused,
		int flags __unused, int fildes __unused, off_t off __unused)
{
	return 0;
}

int munmap(void *addr __unused, size_t len __unused)
{
	return 0;
}
