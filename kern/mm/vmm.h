#pragma once

#include <mm/page.h>

pte_t pd_map(pde_t *pd, pgva_t va, pte_t pte);
pte_t pd_unmap(pde_t *pd, pgva_t va);
pte_t pd_getmap(pde_t *pd, pgva_t va);
