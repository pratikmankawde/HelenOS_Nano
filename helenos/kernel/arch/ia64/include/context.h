/*
 * Copyright (c) 2005 Jakub Jermar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup ia64
 * @{
 */
/** @file
 */

#ifndef KERN_ia64_CONTEXT_H_
#define KERN_ia64_CONTEXT_H_

#include <typedefs.h>
#include <arch/register.h>
#include <align.h>
#include <arch/stack.h>

/*
 * context_save_arch() and context_restore_arch() are both leaf procedures.
 * No need to allocate scratch area.
 *
 * One item is put onto the stack to support get_stack_base().
 */
#define SP_DELTA  (0 + ALIGN_UP(STACK_ITEM_SIZE, STACK_ALIGNMENT))

/* RSE stack starts at the bottom of memory stack, hence the division by 2. */
#define context_set(c, _pc, stack, size) \
	do { \
		(c)->pc = (uintptr_t) _pc; \
		(c)->bsp = ((uintptr_t) stack) + ALIGN_UP((size / 2), REGISTER_STACK_ALIGNMENT); \
		(c)->ar_pfs &= PFM_MASK; \
		(c)->sp = ((uintptr_t) stack) + ALIGN_UP((size / 2), STACK_ALIGNMENT) - SP_DELTA; \
	} while (0)

/*
 * Only save registers that must be preserved across
 * function calls.
 */
typedef struct {

	/*
	 * Application registers
	 */
	uint64_t ar_pfs;
	uint64_t ar_unat_caller;
	uint64_t ar_unat_callee;
	uint64_t ar_rsc;
	uintptr_t bsp;		/* ar_bsp */
	uint64_t ar_rnat;
	uint64_t ar_lc;

	/*
	 * General registers
	 */
	uint64_t r1;
	uint64_t r4;
	uint64_t r5;
	uint64_t r6;
	uint64_t r7;
	uintptr_t sp;		/* r12 */
	uint64_t r13;
	
	/*
	 * Branch registers
	 */
	uintptr_t pc;		/* b0 */
	uint64_t b1;
	uint64_t b2;
	uint64_t b3;
	uint64_t b4;
	uint64_t b5;

	/*
	 * Predicate registers
	 */
	uint64_t pr;

	uint128_t f2 __attribute__ ((aligned(16)));
	uint128_t f3;
	uint128_t f4;
	uint128_t f5;

	uint128_t f16;
	uint128_t f17;
	uint128_t f18;
	uint128_t f19;
	uint128_t f20;
	uint128_t f21;
	uint128_t f22;
	uint128_t f23;
	uint128_t f24;
	uint128_t f25;
	uint128_t f26;
	uint128_t f27;
	uint128_t f28;
	uint128_t f29;
	uint128_t f30;
	uint128_t f31;
	
	ipl_t ipl;
} context_t;

#endif

/** @}
 */
