/*
 *  File: adamantine.c
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#include "../include/adamantine.h"
#include "../include/aos-defs.h"

MODULE("adamantine", "0.01a");

static string
    m_name,
    m_version;

void 
module_create(string name, string version)
{
    m_name      = name;
    m_version   = version;
}