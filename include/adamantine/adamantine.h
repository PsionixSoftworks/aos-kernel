/*
 * File: adamantine.h
 * Author: Vincent C.
 * Description:
 * Used as a base for all subsequent files that utilize adamantine,
 * both in the kernel and in user space.
 *
 * Copyright (C) 2018-2021, Psionix Softworks LLC.
 * 
 */

#ifndef _ADAMANTINE_H
#define _ADAMANTINE_H

/* Check if we're using a 64-bit version of the operating system (we're not) */
#if !defined( __AOS64__ )
#include <adamantine/adamantine-x86.h>					// Include 32-bit adamantine types only!
#else
#include <adamantine/adamantine-x64.h>					// This is unusable right now...
#endif	// !__AOS64__

/* Only use this when you include this file and need common macros. Otherwise just leave it. */
#ifdef ADAMANTINE_MACROS
/* Include common macros */
#include <adamantine/aos-defs.h>
#endif	// !ADAMANTINE_MACROS

/* The macro for platform specific declarations */
#ifndef __ADAMANTINE__
#define __ADAMANTINE__ 		1
#endif	// !__ADAMANTINE__

/* Check if we want to use Centrix API from the CentrixOS line of operating systems */
#if defined( USING_CENTRIX_CORE )   					// Here's a hint: We're not... Yet...
#include <centrix/centrix-core.h>
#include <centrix/centrix.h>
#endif	// !USING_CENTRIX_CORE

/* Check if the kernel version is defined */
#ifdef KERNEL_VERSION_NUMBER				
#define K_VERSION	KERNEL_VERSION_NUMBER				// Shorthand version of 'KERNEL_VERSION_NUMBER'
#endif	// !KERNEL_VERSION_NUMBER
#endif	// !ADAMANTINE
