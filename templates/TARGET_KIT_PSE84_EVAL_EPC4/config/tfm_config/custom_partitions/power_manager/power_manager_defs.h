/*
 * Copyright (c) 2026 Infineon Technologies AG, or an
 * affiliate of Infineon Technologies AG. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#if !defined(POWER_MANAGER_DEFS_H)
#define POWER_MANAGER_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cybsp.h"
#include "cy_pdl.h"

/* Wake-up sources */
#define WAKEUP_SOURCE_USER_BTN1  0x01

/* POWER_MANAGER Operation types */
#define POWER_MANAGER_GET_WAKEUP_SOURCE   1001
#define POWER_MANAGER_CLR_WAKEUP_SOURCE   1002

#ifdef __cplusplus
}
#endif

#endif /* POWER_MANAGER_DEFS_H */