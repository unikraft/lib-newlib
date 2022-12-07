/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Florian Schmidt <florian.schmidt@neclab.eu>
 *
 * Copyright (c) 2018, NEC Labs Europe, NEC Corporation. All rights reserved.
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
 */

/* This header does by design not have include guards, so that it can be
 * included from multiple files. The __NEED_x macros instead make sure that
 * only those definitions are included that are required by that specific
 * file, and only if they haven't been defined on a previous pass through
 * this file.
 */

#include <uk/config.h>
#include <uk/arch/types.h>

#if defined(__NEED_socklen_t) && !defined(__DEFINED_socklen_t)
#ifdef __machine_socklen_t_defined
typedef __socklen_t socklen_t;
#else
typedef unsigned int __socklen_t;
typedef __socklen_t socklen_t;
#endif
#define __DEFINED_socklen_t
#define __machine_socklen_t_defined
#endif

#if (defined __NEED_time_t && !defined __DEFINED_time_t)
typedef long time_t;
#define __DEFINED_time_t
#endif

#if (defined __NEED_suseconds_t && !defined __DEFINED_suseconds_t)
typedef long suseconds_t;
#define __DEFINED_suseconds_t
#endif

#if (defined __NEED_struct_timeval && !defined __DEFINED_struct_timeval)
struct timeval {
	time_t      tv_sec;
	suseconds_t tv_usec;
};
#define __DEFINED_struct_timeval
#endif

#if (defined __NEED_struct_timespec && !defined __DEFINED_struct_timespec)
struct timespec {
	time_t tv_sec;
	long   tv_nsec;
};
#define __DEFINED_struct_timespec
#endif

#if defined(__NEED_timer_t) && !defined(__DEFINED_timer_t)
typedef void *timer_t;
#define __DEFINED_timer_t
#endif

#if (defined __NEED_clockid_t && !defined __DEFINED_clockid_t)
typedef int clockid_t;
#define __DEFINED_clockid_t
#endif

#if defined(__NEED_clock_t) && !defined(__DEFINED_clock_t)
typedef long clock_t;
#define __DEFINED_clock_t
#endif

#if defined(__NEED_sa_family_t) && !defined(__DEFINED_sa_family_t)
#ifdef __machine_sa_family_t_defined
typedef __sa_family_t sa_family_t;
#else
typedef unsigned short __sa_family_t;
typedef __sa_family_t sa_family_t;
#endif
#define __DEFINED_sa_family_t
#define __machine_sa_family_t_defined
#endif
