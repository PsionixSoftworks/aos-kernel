/*
 *  File: pci.h
 *  Author: Vincent Cupo
 *  
 * 	THIS FILE IS NOT TO BE VIEWED BY THE GENERAL PUBLIC WITHOUT 
 * 	WRITTEN CONSENT OF PSIONIX SOFTWORKS LLC.
 * 
 *  PROPERTY OF PSIONIX SOFTWORKS LLC.
 *  Copyright (c) 2018-2020, Psionix Softworks LLC.
 *
 */

#ifndef _AOS_PCI_
#define _AOS_PCI_

/* Includes go here. */
#include "../../aos-defs.h"

/* Define macros. */
#define PCI_ENABLE                          0x01
#define PCI_DEVICE_ENABLE_IO                (PCI_ENABLE << 0x00)
#define PCI_DEVICE_ENABLE_MEMORY            (PCI_ENABLE << 0x01)
#define PCI_DEVICE_ENABLE_MASTER            (PCI_ENABLE << 0x02)
#define PCI_DEVICE_ENABLE_SPECIAL           (PCI_ENABLE << 0x03)
#define PCI_DEVICE_ENABLE_INVALIDATE        (PCI_ENABLE << 0x04)
#define PCI_DEVICE_ENABLE_VGA_SNOOP         (PCI_ENABLE << 0x05)
#define PCI_DEVICE_ENABLE_PARITY            (PCI_ENABLE << 0x06)
#define PCI_DEVICE_ENABLE_WAIT              (PCI_ENABLE << 0x07)

struct aos_pci_device
{
    uint32_t vendor;
    uint32_t device;
    uint32_t subvendor;
    uint32_t subdevice;
    uint32_t class;
    uint32_t class_mask;
} PACKED PCI_Device_t;

/* define the pci struct. */
typedef struct aos_pci
{
    struct aos_pci_device device_id;
} PACKED PCI_t;

#endif
