# Process Memory Information in xv6

## Overview
This project extends the xv6 operating system by implementing system calls that provide information about the memory usage of a process. The project helps in understanding how xv6 manages process memory, virtual memory, and page tables.

The implemented system calls allow a user program to:
- Retrieve the total memory size of the current process
- Retrieve the number of virtual memory pages used
- Retrieve the number of valid page table entries

The project also includes a user-level program to test and display this information.

---

# Objectives

- Understand process memory organization in xv6
- Study virtual memory management and page tables
- Learn how system calls are implemented in xv6
- Explore how xv6 allocates and maps memory pages
- Implement kernel-level functionality and expose it to user programs

---

# Project Structure

Important xv6 source files used in this project:

| File | Purpose |
|---|---|
| `proc.h` | Defines `struct proc` |
| `proc.c` | Process management functions |
| `vm.c` | Virtual memory and page allocation |
| `mmu.h` | Paging structures and constants |
| `syscall.h` | System call numbers |
| `syscall.c` | System call dispatch table |
| `sysproc.c` | System call implementations |
| `user.h` | User-level syscall declarations |
| `usys.S` | User syscall stubs |
| `Makefile` | Build configuration |

---

# Process Memory in xv6

Each process in xv6 has its own virtual address space consisting of:
- Text segment (code)
- Data segment
- Heap
- Stack

The process memory size is stored in:

```c
uint sz;
```

inside `struct proc`.

Memory allocation flow in xv6:

```text
sbrk()
   ↓
sys_sbrk()
   ↓
growproc()
   ↓
allocuvm()
   ↓
mappages()
```

---

# Implemented System Calls

## 1. Get Process Memory Size

Returns the total size of memory used by the current process in bytes.

### Kernel Logic

```c
return myproc()->sz;
```

---

## 2. Get Number of Virtual Pages

Returns the number of virtual pages allocated to the process.

Formula used:

```text
Pages = Process Size (sz) / PGSIZE
```

where:
- `sz` = process size in bytes
- `PGSIZE` = 4096 bytes

---

## 3. Get Number of Valid Page Table Entries

Traverses the process page tables and counts entries where the present bit (`PTE_P`) is set.

This indicates the number of valid mapped pages.

---

# Steps to Add a System Call in xv6

The following modifications were made:

## 1. Define syscall numbers

Added entries in:

```text
syscall.h
```

---

## 2. Add syscall handlers

Added function mappings in:

```text
syscall.c
```

---

## 3. Implement kernel functions

Implemented syscall functions in:

```text
sysproc.c
```

---

## 4. Add user-level declarations

Added prototypes in:

```text
user.h
```

---

## 5. Add syscall stubs

Added syscall stubs in:

```text
usys.S
```

---

# User Program

A user-level test program was written to:
- Invoke the implemented system calls
- Display process memory information
- Observe changes after memory allocation

Example output:

```text
Process Memory Size : 16384 bytes
Number of Pages     : 4
Valid PTE Entries   : 4
```

---

# Building and Running

## Compile and Run xv6

```bash
make qemu
```

---

## Run the User Program

Inside xv6 shell:

```bash
meminfo
```

---

# Testing Performed

## 1. Initial Process Memory

Observed default process memory usage after system startup.

---

## 2. Dynamic Memory Allocation

Used `sbrk()` to allocate additional memory and verified:
- increase in process size
- increase in page count
- increase in valid PTE count

---

## 3. Fork Experiment

Created child processes using `fork()` and observed:
- parent and child initially have same memory size
- separate page tables are maintained

---

# Key Concepts Learned

- Virtual memory management in xv6
- Page tables and address translation
- Kernel-user interaction through system calls
- Process memory organization
- Dynamic memory allocation in operating systems

---

# Future Improvements

Possible extensions:
- Display physical memory usage
- Show detailed page table mappings
- Implement demand paging
- Track shared memory usage
- Add per-segment memory statistics

---

# Conclusion

This project provided hands-on experience with:
- xv6 internals
- operating system memory management
- page table traversal
- system call implementation

It demonstrated how xv6 manages process memory and how kernel functionality can be exposed to user programs through system calls.
