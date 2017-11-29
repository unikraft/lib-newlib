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

#include <sys/time.h>
#include <utime.h>
#include <uk/config.h>
#if HAVE_SCHED
#include <uk/sched.h>
#else
#include <uk/plat/lcpu.h>
#endif

int
gettimeofday(struct timeval *tv __unused, void *tz __unused)
{
	return 0;
}

int utime(const char *filename __unused, const struct utimbuf *times __unused)
{
	return 0;
}

/* currently only have millisecond resolution on timers */
static void msleep(uint32_t milliseconds)
{
#if HAVE_SCHED
	uk_sched_sleep(milliseconds);
#else
	ukplat_lcpu_halt_to(milliseconds);
#endif
}

/* TODO: nanosleep() does not properly set rem, or return the right value if
 * the sleep got interrupted.
 * However, we can only fix this once we have a better timer implementation.
 */
int nanosleep(const struct timespec *req, struct timespec *rem)
{
	msleep((req->tv_sec * 1000) + (req->tv_nsec / 1000000));
	if (rem) {
		rem->tv_sec = 0;
		rem->tv_nsec = 0;
	}
	return 0;
}
