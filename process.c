/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * libnewlib glue code
 *
 * Authors: Felipe Huici <felipe.huici@neclab.eu>
 *
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

#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/resource.h>
#undef errno
extern int errno;

int execve(char *name __unused, char **argv __unused, char **env __unused)
{
	errno = ENOMEM;
	return -1;
}

int execv(const char *path __unused, char *const argv[] __unused)
{
	return 0;
}

int system(const char *command __unused)
{
	return 0;
}

FILE *popen(const char *command __unused, const char *type __unused)
{
	return NULL;
}

int pclose(FILE *stream __unused)
{
	return 0;
}

int fork(void)
{
	errno = EAGAIN;
	return -1;
}

int getpid(void)
{
	return 1;
}

pid_t getppid(void)
{
	return 0;
}

int kill(int pid __unused, int sig __unused)
{
	errno = EINVAL;
	return -1;
}

int times(struct tm *buf __unused)
{
	return -1;
}

int wait(int *status __unused)
{
	errno = ECHILD;
	return -1;
}

int setpgrp(void)
{
	return 0;
}


int killpg(int pgrp __unused, int sig __unused)
{
	return 0;
}


pid_t wait3(int *wstatus __unused, int options __unused,
		struct rusage *rusage __unused)
{
	return 0;
}

pid_t wait4(pid_t pid __unused, int *wstatus __unused, int options __unused,
		struct rusage *rusage __unused)
{
	return 0;
}

pid_t waitpid(pid_t pid __unused, int *wstatus __unused, int options __unused)
{
	return 0;
}

pid_t setsid(void)
{
	return 0;
}

pid_t getsid(pid_t pid __unused)
{
	return 0;
}

int setpgid(pid_t pid __unused, pid_t pgid __unused)
{
	return 0;
}

pid_t getpgid(pid_t pid)
{
	return 0;
}


int tcsetpgrp(int fd __unused, pid_t pgrp __unused)
{
	return 0;
}

pid_t tcgetpgrp(int fd __unused)
{
	return 0;
}

int nice(int inc __unused)
{
	return 0;
}
