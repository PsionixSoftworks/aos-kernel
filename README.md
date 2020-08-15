# AdamantineOS
The main repo for AdamantineOS. AdamantineOS is the next big thing in the OS community. It will 

# Contributing
AdamantineOS (AOS) must keep structure when developing for the kernel. You must make sure to abide by all rules for AOS Kernel dev. If you have access to this project, then you are one of very few who will ever work on this project. As such it is your sworn responsibility to follow the NDA and formatting rules. Thank you.

# Writing AdamantineOS (AOS) Kernel
Adamantine is a word for a nearly indestructable mythological material, usually greenish or pink in color. As such, the security algorithm is one of the backbones of the kernel's design. Adamantine is a microkernel whose sole purpose is to produce a potentially unbreakable system with a proprietary file system that will not be readable by standard filesystems. This is done to prevent copying or decompiling the software written in the OS environment. Software should only be written in AdamantineOS so that base executables will not be able to leave traces on other OS's. Additionally, most applications should be run as lauch configurations with the base executable in a hidden location. The kernel will have a Global Descriptor Table (GDT), Interrupt Descriptor Table (IDT), Memory & Paging system, Proprietary Filesystem, User access, CPU Controls, and a very simple Keyboard Driver.

# Current Issues

