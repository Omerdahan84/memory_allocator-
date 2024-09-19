# Simple Memory Allocator in C

This project is a simple implementation of a memory allocator in C, demonstrating basic memory management techniques such as allocation and deallocation using a linked list to keep track of allocated memory blocks.

## Overview

The program provides a custom memory allocator that can:

- Allocate memory blocks of a specified size.
- Free memory blocks based on a memory ID (`mID`).
- Keep track of allocated memory blocks using a sorted linked list for efficient memory management.

This allocator is not intended for production use but serves as an educational example of how memory management can be implemented at a low level in C.

## Files

- `allocator.c`: Contains the implementation of the allocator functions and a `main` function with test cases.
- `README.md`: Provides an overview and instructions for the project.

## How It Works

1. **Allocator Creation (`allocatorCreate`)**: Initializes the allocator with a given size. It allocates a block of memory and sets up the necessary data structures.

2. **Memory Allocation (`allocatorAllocate`)**: Allocates a memory block of a specified size and assigns it an `mID`. It searches for the first suitable gap in the memory where the block can fit, maintaining a sorted linked list of allocated blocks.

3. **Memory Deallocation (`allocatorFreeMid`)**: Frees all memory blocks associated with a given `mID`. It removes the corresponding nodes from the linked list and frees the memory.

4. **Allocator Destruction (`allocatorFree`)**: Cleans up the allocator by freeing all allocated memory and associated data structures.

## Usage

### Compilation

To compile the program, use a C compiler like `gcc`:

```bash
gcc -o allocator allocator.c
```

### Running

After compiling, you can run the executable:

```bash
./allocator
```

### Sample Output

```
Allocator created successfully with 100 bytes.
Allocation result for 20 bytes with mID 1: 0
Allocation result for 30 bytes with mID 2: 20
Allocation result for 60 bytes with mID 3: -1
Freed memory block with mID 1.
Allocation result for 10 bytes with mID 4: 0
Allocation result for 10 bytes with mID 4: 10
Freed memory block with mID 4.
Allocator freed successfully.
```

## Functions

### Allocator* allocatorCreate(int n)

- **Description**: Creates a new allocator with `n` bytes of memory.
- **Parameters**:
  - `int n`: The total size of memory to manage.
- **Returns**: A pointer to the newly created `Allocator`.

### int allocatorAllocate(Allocator* obj, int size, int mID)

- **Description**: Allocates a block of memory of `size` bytes and assigns it an `mID`.
- **Parameters**:
  - `Allocator* obj`: Pointer to the allocator.
  - `int size`: The size of the memory block to allocate.
  - `int mID`: The memory ID to associate with this block.
- **Returns**: The starting index of the allocated block, or `-1` if allocation fails.

### int allocatorFreeMid(Allocator* obj, int mID)

- **Description**: Frees all memory blocks associated with the given `mID`.
- **Parameters**:
  - `Allocator* obj`: Pointer to the allocator.
  - `int mID`: The memory ID of the blocks to free.
- **Returns**: The total size of freed memory.

### void allocatorFree(Allocator* obj)

- **Description**: Frees the allocator and all associated memory.
- **Parameters**:
  - `Allocator* obj`: Pointer to the allocator.


