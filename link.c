/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Charalampos Mainas <charalampos.mainas@neclab.eu>
 *
 * Copyright (c) 2019, NEC Europe Ltd., NEC Corporation. All rights reserved.
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

#include <uk/essentials.h>
#include <stddef.h>
#include <link.h>
#include <elf.h>

#include <stdlib.h>

#ifdef DRUNTIME
struct DG {
    void * addr;
    struct dl_phdr_info* result;
};

extern char __bss_start[];
extern char _end[];
#endif

int dl_iterate_phdr(
		int (*callback)(struct dl_phdr_info *info,
				size_t size, void *data),
		void *data)
{
#ifdef DRUNTIME
    struct DG* temp = (struct DG *)data;

    temp->result->dlpi_addr = (ElfW(Addr))__bss_start;
    temp->result->dlpi_phnum = 1;
    temp->result->dlpi_adds  = 0;
	temp->result->dlpi_subs  = 0;
	temp->result->dlpi_name = "";

    ElfW(Phdr) *segment_data = (ElfW(Phdr) *)malloc(sizeof(ElfW(Phdr)));
    segment_data->p_type = PT_LOAD;
    segment_data->p_flags = PF_W;
    segment_data->p_vaddr = 0;
    segment_data->p_memsz = _end - __bss_start;

    temp->result->dlpi_phdr = segment_data;

    return 1;
#else
    return 0;
#endif
}
