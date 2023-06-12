# CS342 - Operating Systems
This repository contains all the assignments and projects completed during the course. The homework assignments introduce and solidify foundational concepts. The projects demonstrate practical application of these concepts through the development of functional programs.

## Homework

- **Homework 1:** Introduction to Linux, Virtual Machines, and C programming.

  _Grade:_ **100/100**
- **Homework 2:** Preparation for the final exam, covering topics such as Deadlocks, Memory Management, Virtual Memory, File Systems, Mass Storage, and Input/Output.

  _Grade:_ **100/100**

## Projects

### Project 1: Top-K Words Finder
This application finds the K most frequently occurring words (i.e., top-K words) in a given dataset. The program has two variations:
- **Part A:** Uses multiple child processes to process the data set.
- **Part B:** Utilizes multiple threads for processing.

Both variations pass information to the parent process through shared memory, with each child process accessing and using a portion of the shared memory.

  _Grade:_ **70/100**

### Project 2: Multiprocessor Scheduling Simulation
This project simulates multiprocessor scheduling. It implements two approaches:
- **Single-Queue Approach:** A common ready queue (runqueue) used by all processors.
- **Multi-Queue Approach:** Each processor has its individual ready queue.

The program, `mps`, simulates FCFS (first-come first-served), SJF (shortest job first - nonpreemptive), and RR(Q) (round robin with time quantum Q) scheduling algorithms.

  _Grade:_ **43/100**

### Project 3: Resource Manager Library
This project presents a resource manager library for a multithreaded application. The library allows multiple threads to request, use, and release resources during their lifetime.

  _Grade:_ **100/100**?

### Project 4: Process and System Memory Information
This Linux program, called `pvm`, provides memory-related information for a process and the physical memory of the system. The information is retrieved from the /proc virtual file system, which interfaces the kernel for user-space programs. The /proc directory includes various files that provide information about the system state and processes, and includes a sub-directory for each process, offering process-specific information maintained by the kernel.

  _Grade:_ **100/100**?
