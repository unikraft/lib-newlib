// SPDX-License-Identifier: BSD-3-Clause
/*
 * Authors: Eduard Vintilă <eduard.vintila47@gmail.com>
 *
 * Copyright (c) 2022, University of Bucharest. All rights reserved.
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

#include <uk/tcb_impl.h>
#include <uk/plat/tls.h>
#include <uk/arch/tls.h>
#include <uk/alloc.h>
#include <uk/assert.h>
#include <sys/reent.h>

int uk_thread_uktcb_init(struct uk_thread *thread, void *tcb)
{
	/* We already initialize the TCB in ukarch_tls_tcb_init() */
}

/* Needed by newlib. Retrieves the reentrant structure of the current thread.*/
struct _reent *__getreent(void)
{
	void *tcb = ukarch_tls_tcb_get(ukplat_tlsp_get());
	struct _reent **reent = (struct _reent **) tcb;

	if (reent && *reent)
		return *reent;

	return _impure_ptr;
}

void uk_thread_uktcb_fini(struct uk_thread *thread, void *tcb)
{
	struct _reent **reent = (struct _reent **)tcb;

	uk_pr_debug("uk_thread_tcb_fini uk_thread %p, tcb %p\n", thread, tcb);
	uk_free(uk_alloc_get_default(), *reent);
}


/* Called for every thread. Initiliazes newlib's reentrant structure for the given TCB. */
void ukarch_tls_tcb_init(void *tcb)
{
	struct _reent **reent = (struct _reent **)tcb;

	uk_pr_info("ukarch_tls_tcb_init tcb %p\n", tcb);

	UK_ASSERT(reent);

	*reent = uk_memalign(
	    uk_alloc_get_default(),
	    __PAGE_SIZE,
	    sizeof(struct _reent));

	UK_ASSERT(*reent);

	_REENT_INIT_PTR(*reent);

#if 0
	/* TODO initialize basic signal handling */
	_init_signal_r(myreent);
#endif

	return 0;
}
