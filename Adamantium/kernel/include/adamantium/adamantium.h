/*
 * File: adamantium.h
 * Author: Vincent C.
 * Description:
 * Used as a base for all subsequent files that utilize adamantiUM,
 * both in the kernel and in user space.
 *
 * Copyright (C) 2018-2021, Psionix Softworks LLC.
 * 
 */

#ifndef _ADAMANTIUM_H
#define _ADAMANTIUM_H

/* Check if we're using a 64-bit version of the operating system (we're not) */
#if !defined( __AOS64__ )
#include <adamantium/adamantium-x86.h>					// Include 32-bit adamantiUM types only!
#else
#include <adamantium/adamantium-x64.h>					// This is unusable right now...
#endif	// !__AOS64__

#include <sys/types.h>

/* Only use this when you include this file and need common macros. Otherwise just leave it. */
#ifndef ADAMANTIUM_MACROS
/* Include common macros */
#include <adamantium/aos-defs.h>
#endif	// !ADAMANTIUM_MACROS

/* The macro for platform specific declarations */
#ifndef __ADAMANTIUM__
#define __ADAMANTIUM__ 		1
#endif	// !__ADAMANTIUM__

/* Check if we want to use Centrix API from the CentrixOS line of operating systems */
#if defined( USE_CENTRIX_CORE )   					// Here's a hint: We're not... Yet...
#include <centrix/centrix-core.h>
#include <centrix/centrix.h>
#endif	// !USING_CENTRIX_CORE

// TODO: Change the common headers. These are common, but we should use osapi includes only.
#if defined(USE_COMMON_HEADERS)
#include <stdint.h>
#include <compiler.h>
#include <common.h>
#endif

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH     32						// The max name length per node in a file or directory
#endif

#define AOS_MODULE(...)                             // AOS Module. For future use.

/* Check if the kernel version is defined */
#ifdef KERNEL_VERSION_NUMBER				
#define K_VERSION	KERNEL_VERSION_NUMBER	        // Short-hand version of 'KERNEL_VERSION_NUMBER'
#endif	// !KERNEL_VERSION_NUMBER

#endif	// !ADAMANTIUM
