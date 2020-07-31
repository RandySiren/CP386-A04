# CP386-A04

CP386 Spring 2020 - Assignment 4 Code

## Motivation

Code here is for Assignment 4 for our CP386 Spring 2020 class at Wilfrid Laurier University

## Installation

To install, clone the repository locally and navigate to it from your terminal.
Then follow the instructions in the Makefile to compile; you can compile with the 2 commands:

```bash
make
```

which is the same as

```bash
make warnings_BAD
```

or you can compile with warnings allowed

```bash
make warnings_OK
```

---

You can delete before recompiling to ensure clean compiling by running:

```bash
make clean
```

---

Then to run the program, simply:

```bash
./Assignment_4 a b c...y z
```

Replacing the a,b,c parameters with any amount of integers to act as the available resources.

## Screenshots

![Code](https://cdn.discordapp.com/attachments/670139641025921046/737414849750892544/unknown_2.png)

## Individual Contributions
* main - Mandeep/Raman
* threadRun - Raman
* getSafetySequence - Mandeep/Raman
* readFile -Mandeep
* printDoublePointerData -Mandeep
* printSinglePointerData -Raman

## Features
* Request resources (allocate) (RQ)
* Release resources (de-allocate) (RL)
* Print current states (*)
* Run the current sequence (Run)
* Exit the program (exit)

## Tests
See screenshot

## Code Example
Invoke program by passing number of available resources.
```bash
./Assignment_4 3 3 2
```

Command for requesting resources where the variables represents integers.
```bash
Enter Command: RQ a b c d
```

Command for listing available resources, allocated resources and needed resources.
```bash
Enter Command: *
```
Enter this command to run the threads.
```bash
Enter Command: Run
```

To exit the program, simply write the following command. 
```bash
Enter Command: Exit
```
## Authors
* Mandeep Sran
* Raman Kala