# AdamantineOS
The main repo for AdamantineOS.

# Contributing
AdamantineOS (AOS) must keep structure when developing for the kernel. You must make sure to abide by all rules for AOS Kernel dev. If you have access to this project, then you are one of very few who will ever work on this project. As such it is your sworn responsibility to ensure the development lifecycle the best you can. Thank you.

# Writing AdamantineOS (AOS) Kernel
Adamantine is a word for a nearly indestructable mythological material, usually greenish or pink in color. As such, the security algorithm is one of the backbones of the kernel's design. Adamantine is a microkernel whose sole purpose is to produce a potentially unbreakable system with a proprietary file system that will not be readable by standard filesystems. This is done to prevent copying or decompiling the software written in the OS environment. Software should only be written in AdamantineOS so that base executables will not be able to leave traces on other OS's. Additionally, most applications should be run as launch configurations with the base executable in a hidden location. The kernel will have a Global Descriptor Table (GDT), Interrupt Descriptor Table (IDT), memory & Paging system, Proprietary Filesystem, user access, CPU Controls, and a very simple keyboard Driver.

# Additional Information
- If you use this kernel to develop an Operating System, you may not explicitly call it AdamantineOS. That is the name of the Operating system being developed around this kernel.
- You must give credit to me, and inform me of its use.
- You must abide by the terms of the license attached to this repo.

# Current Issues
- The IDT cannot process interrupts and triple faults whenever one is met. (Broken again...)
