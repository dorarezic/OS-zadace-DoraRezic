# Operating Systems Assignments – University of Mostar

👋 Hello! I'm a 2nd-year Computer Science student at the University of Mostar, and this repository contains my assignments for the Operating Systems course. All assignments were developed using **Linux** and **VS Code**, with a focus on **processes**, **threads**, **signals**, **mutual exclusion**, and **inter-thread communication** using algorithms like Dekker, Lamport, and semaphores.

---

## 📌 Overview of Assignments

### 🧮 Task 1 – Persistent Background Process with Signal Handling
Simulates a long-running background process that calculates square numbers and stores them in a file (`obrada.txt`). It also maintains a resume state in `status.txt`. Supports Unix signals for runtime interaction:
- `SIGUSR1` prints the current number.
- `SIGTERM` safely saves state and exits.
- `SIGINT` exits abruptly, forcing recovery on the next run.

### 🔁 Task 2 – Mutual Exclusion: Dekker’s Algorithm
Implements Dekker's algorithm to allow two concurrent processes (created using `fork`) to safely access a critical section without conflicts.

### 🍽️ Task 3 – Thread-Based Table Reservation System (Lamport's Algorithm)
Simulates concurrent thread-based restaurant table reservations. Threads race to reserve tables and use Lamport’s bakery algorithm to avoid collisions and ensure safe mutual exclusion.

### 🎠 Task 4 – Carousel Ride Synchronization
Models a carousel (ringišpil) system using visitor and carousel threads. It ensures:
- Visitors can only board if there is a seat.
- The carousel starts only when full.
- Visitors can only leave after the ride ends.
Semaphores and a mutex protect shared state.

---

## ⚙️ Requirements

- GCC / Clang
- Linux or WSL
- POSIX threads (pthreads)
- Make (optional)

## 📦 Compilation

```bash
gcc -o zad1 zad1.c -lm
gcc -o zad2 zad2.c
gcc -o zad3 zad3.c -pthread
gcc -o zad4 zad4.c -pthread
