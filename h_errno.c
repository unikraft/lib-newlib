/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Authors: Razvan Deaconescu <razvand@unikraft.io>
 *
 * Copyright (c) 2022, Unikraft GmbH. All rights reserved.
 */

#include <uk/config.h>
#if CONFIG_LIBLWIP
#include <netdb.h>
#endif /* CONFIG_LIBLWIP */

int h_errno;
