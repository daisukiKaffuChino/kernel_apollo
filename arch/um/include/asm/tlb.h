/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __UM_TLB_H
#define __UM_TLB_H

#include <asm/tlbflush.h>
#include <asm-generic/cacheflush.h>
#include <asm-generic/tlb.h>

static inline void
tlb_flush_pmd_range(struct mmu_gather *tlb, unsigned long address,
		    unsigned long size)
{
	tlb->need_flush = 1;

	if (tlb->start > address)
		tlb->start = address;
	if (tlb->end < address + size)
		tlb->end = address + size;
}

/**
 * tlb_remove_tlb_entry - remember a pte unmapping for later tlb invalidation.
 *
 * Record the fact that pte's were really umapped in ->need_flush, so we can
 * later optimise away the tlb invalidate.   This helps when userspace is
 * unmapping already-unmapped pages, which happens quite a lot.
 */
#define tlb_remove_tlb_entry(tlb, ptep, address)		\
	do {							\
		tlb->need_flush = 1;				\
		__tlb_remove_tlb_entry(tlb, ptep, address);	\
	} while (0)

#define tlb_remove_huge_tlb_entry(h, tlb, ptep, address)	\
	tlb_remove_tlb_entry(tlb, ptep, address)

static inline void tlb_change_page_size(struct mmu_gather *tlb, unsigned int page_size)
{
}

#define pte_free_tlb(tlb, ptep, addr) __pte_free_tlb(tlb, ptep, addr)

#define pud_free_tlb(tlb, pudp, addr) __pud_free_tlb(tlb, pudp, addr)

#define pmd_free_tlb(tlb, pmdp, addr) __pmd_free_tlb(tlb, pmdp, addr)

#define tlb_migrate_finish(mm) do {} while (0)

#endif
