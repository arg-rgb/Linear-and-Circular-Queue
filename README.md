<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" style="height:64px;margin-right:32px"/>

# Queue Implementation in C

A **comprehensive, production-ready repository** showcasing both **Linear** and **Circular** queue data-structures in C, designed with **dynamic memory allocation**, **interactive CLI tooling**, and extensive in-code documentation. Ideal for learners exploring fundamental data-structures as well as practitioners needing a lightweight queue module for embedded or systems-level work.

## 1. Project Snapshot

|  | Linear Queue | Circular Queue |
| :-- | :-- | :-- |
| **Principle** | Straight FIFO list[^1] | FIFO list with wrap-around linkage[^2] |
| **Memory Model** | Contiguous array; unused slots may accumulate[^2][^3] | Contiguous array used as ring buffer; vacated slots reused automatically[^2][^3] |
| **Insertion Check** | `rear == size – 1` | `(rear + 1) % size == front` |
| **Deletion Check** | `front > rear` or `front == -1` | `front == -1` |
| **Typical Use-Cases** | Print spooling, simple buffers, BFS traversal[^4] | Round-robin CPU scheduling, fixed-size network buffers[^5][^6] |

## 2. Repository Layout

```
.
├── linear_queue.c        # Source for linear queue
├── circular_queue.c      # Source for circular queue
├── queue.h               # Shared data-types (optional include)
├── examples/             # Ready-to-run demo scenarios
│   ├── benchmark.sh
│   └── unit_tests.c
└── docs/
    └── README.md         # <— you are here
```


## 3. Key Features

* **Dynamic Capacity** — both queues allocate at runtime via `malloc()` and can expand safely with `realloc()` prompts.[^7][^8]
* **Interactive CLI** — menu-driven interface enables live enqueue, dequeue and display operations.
* **Overflow \& Underflow Protection** — graceful messages on full/empty detections with optional auto-expansion.
* **Clean Memory Lifecycle** — all heap blocks released with `free()` on normal exit paths.
* **Pedagogical Clarity** — abundant inline comments map each line of code to the underlying queue theory.
* **Modular Design** — drop-in `queue.h` lets other C files reuse the same structures without modification.


## 4. Build \& Run

### 4.1 Prerequisites

* GCC 9+ or Clang 10+
* POSIX-compatible shell (for example scripts)


### 4.2 Compilation

```bash
# Linear queue
gcc -Wall -Wextra -std=c11 linear_queue.c -o linear_queue

# Circular queue
gcc -Wall -Wextra -std=c11 circular_queue.c -o circular_queue
```


### 4.3 Interactive Session

```bash
./linear_queue
# or
./circular_queue
```

Follow on-screen prompts to enqueue, dequeue, display, or trigger automatic resizing.

## 5. Detailed Operation Flow

### 5.1 Enqueue (Insert)

1. **Capacity Check**
    * Linear — verify `rear < size – 1`.[^2]
    * Circular — evaluate wrap-around `(rear + 1) % size != front`.[^2]
2. **Dynamic Expansion** (optional)
Prompt for a new `size`; reallocate with `realloc()` and copy existing elements, maintaining order.[^7]
3. **Pointer Update**
    * Linear — `rear++`; set `front=0` if first insert.
    * Circular — `rear = (rear + 1) % size`; initialize `front=rear` if queue was empty.
4. **Store Element**
`queue[rear] = item;`

### 5.2 Dequeue (Delete)

* **Underflow Check**
    * Linear — `front == -1 || front > rear`[^9].
    * Circular — `front == -1` triggers empty message.
* **Retrieve \& Advance**
`deleted = queue[front];` then
    * Linear — `front++`.
    * Circular — `front = (front + 1) % size`; reset both pointers to `-1` if last element removed.


### 5.3 Display

Iterate from `front` to `rear` (with modulo for circular) printing each element and current pointer indices.

## 6. Algorithmic Analysis

| Operation | Linear Queue | Circular Queue | Notes |
| :-- | :-- | :-- | :-- |
| **Enqueue** | O(1) average, O(n) when resizing[^10] | O(1) average, O(n) when resizing | Resize copies entire array |
| **Dequeue** | O(1) | O(1)[^11] | No element shifting required |
| **Display / Traverse** | O(n) | O(n) | Includes wrap-around logic |
| **Space Efficiency** | May waste front slots (up to size/2 on average)[^2][^12] | Utilises all slots; only full when truly full[^6] |  |

## 7. Advantages \& Disadvantages

### 7.1 Linear Queue

| Aspect | Description |
| :-- | :-- |
| **Pros** | -  Simple array indices; minimal arithmetic[^1]  <br>-  Predictable FIFO semantics aid reasoning <br>-  Constant-time core operations (no resize) |
| **Cons** | -  Front holes create *false overflow* wasting memory[^2][^13] <br>-  Requires element shifting if implemented without `front` pointer[^11] <br>-  Inefficient for long-running services where queue shrinks and grows repeatedly |

### 7.2 Circular Queue

| Aspect | Description |
| :-- | :-- |
| **Pros** | -  Reuses freed slots, achieving near-100% utilisation[^5][^6] <br>-  Perfect for *fixed-size* ring buffers in embedded or real-time tasks[^3] <br>-  Constant-time enqueue/dequeue without element shifts |
| **Cons** | -  Slightly more complex pointer arithmetic and modulo operations[^2] <br>-  Harder to debug pointer wrap-around errors <br>-  Enqueue logic must differentiate *full* vs *empty* when pointers coincide |

## 8. Real-World Applications

* **Operating Systems** — round-robin process schedulers employ circular queues for equitable CPU slices.[^5]
* **Networking** — routers maintain ring buffers for packet queues under hard memory caps.[^14]
* **Print Spooling** — printers use linear queues when user jobs naturally drain without wrap-around concerns.[^4]
* **Graph Algorithms** — BFS traversal loads neighbouring vertices into a linear queue.[^9]
* **Multimedia Streaming** — circular queues feed audio frames to DACs, ensuring constant playback with zero gaps.[^6]


## 9. Extending the Project

1. **Thread-Safe Variant** – wrap operations with POSIX mutexes or C11 atomics.
2. **Generics with `void *`** – allow storage of any data-type via pointers.
3. **Linked-List Back-End** – eliminate fixed capacity altogether, at the cost of heap fragmentation.[^15]
4. **Benchmark Suite** – compare throughput and latency across queue sizes using the supplied `benchmark.sh`.
5. **Dead-Letter Queue Pattern** – integrate error-message rerouting strategies inspired by messaging systems.[^16]

## 10. Frequently Asked Questions

**Q1: Why use `realloc()` instead of doubling buffer size automatically?**
Manual confirmation teaches beginners about heap management cost and prevents runaway allocations in constrained environments.[^17][^7]

**Q2: Can the linear queue reclaim front space without resizing?**
Yes—by shifting all elements left, but that incurs O(n) per dequeue and defeats FIFO efficiency; the circular variant solves this elegantly.[^18]

**Q3: How big should my initial queue be?**
Start small (e.g., 8 or 16 elements) and rely on dynamic expansion. Heap-growth is amortised and rarely a bottleneck in typical workloads.[^8]

## 11. Getting Help

If you encounter build issues or have questions on algorithm internals, open a discussion in the repository’s *Discussions* tab or start a new issue with a clear title and reproduction steps. The community monitors queries weekdays 10:00–18:00 IST.

Master these queue implementations to solidify your understanding of **FIFO data-structures**, dynamic memory usage, and pointer arithmetic—cornerstones of efficient systems programming.

<div style="text-align: center">⁂</div>

[^1]: https://www.geeksforgeeks.org/dsa/what-is-queue-data-structure/

[^2]: https://www.geeksforgeeks.org/dsa/difference-between-linear-queue-and-circular-queue/

[^3]: https://prepbytes.com/blog/difference-between-linear-queue-and-circular-queue/

[^4]: https://www.w3schools.com/dsa/dsa_data_queues.php

[^5]: https://prepbytes.com/blog/advantages-of-circular-queue-over-linear-queue/

[^6]: https://www.ccbp.in/blog/articles/advantages-of-circular-queue-over-linear-queue

[^7]: https://www.scaler.com/topics/c/dynamic-memory-allocation-in-c/

[^8]: https://www.geeksforgeeks.org/c/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/

[^9]: https://www.geeksforgeeks.org/dsa/introduction-to-queue-data-structure-and-algorithm-tutorials/

[^10]: https://www.geeksforgeeks.org/dsa/time-and-space-complexity-analysis-of-queue-operations/

[^11]: https://www.geeksforgeeks.org/dsa/introduction-and-array-implementation-of-queue/

[^12]: https://techdifferences.com/difference-between-linear-queue-and-circular-queue.html

[^13]: https://www.ccbp.in/blog/articles/difference-between-linear-queue-and-circular-queue

[^14]: https://www.lenovo.com/in/en/glossary/fifo/

[^15]: https://en.wikipedia.org/wiki/C_dynamic_memory_allocation

[^16]: https://www.kai-waehner.de/blog/2022/05/30/error-handling-via-dead-letter-queue-in-apache-kafka/

[^17]: https://www.geeksforgeeks.org/c/difference-between-static-and-dynamic-memory-allocation-in-c/

[^18]: https://www.linkedin.com/advice/1/what-most-common-queue-implementation-mistakes-fcitc

[^19]: https://www.geeksforgeeks.org/dsa/fifo-first-in-first-out-approach-in-programming/

[^20]: https://dzone.com/articles/modern-queue-patterns-guide

[^21]: https://gpi.ac.in/DataImages/Document/Document_0_Anvita_4th%20sem_QUEUE.pdf

[^22]: https://byjus.com/gate/fifo-full-form/

[^23]: https://www.freecodecamp.org/news/queue-data-structure-definition-and-java-example-code/

[^24]: https://www.geeksforgeeks.org/dsa/fifo-principle-of-queue/

[^25]: https://docs.oracle.com/javase/tutorial/collections/implementations/queue.html

[^26]: https://stackoverflow.com/questions/30516897/what-is-the-best-data-structure-to-implement-a-queue

[^27]: https://byjus.com/gate/queue-notes/

[^28]: https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)

[^29]: https://heycoach.in/blog/queues-in-javascript/

[^30]: https://en.wikipedia.org/wiki/Queue_(abstract_data_type)

[^31]: https://dev.to/emmanuelayinde/understanding-queues-data-structure-mastering-fifo-principle-in-javascript-8di

[^32]: https://eicta.iitk.ac.in/knowledge-hub/data-structure-with-c/stacks-and-queues-implementation-operations-and-applications/

[^33]: https://www.youtube.com/watch?v=1j2gWyY5CK4

[^34]: https://blog.bitsrc.io/mastering-stacks-and-queues-understanding-lifo-and-fifo-data-structures-531c8d17194c

[^35]: https://developers.zip.co/v2/docs/edge-cases-and-error-handling

[^36]: https://discuss.boardinfinity.com/t/difference-between-linear-and-circular-queue/5417

[^37]: https://www.w3schools.com/c/c_memory_allocate.php

[^38]: https://heycoach.in/blog/circular-queue-implementation/

[^39]: https://www.upgrad.com/blog/difference-between-circular-queue-and-linear-queue/

[^40]: https://www.design-reuse.com/article/59725-dynamic-memory-allocation-and-fragmentation-in-c-and-c-/

[^41]: https://www.numberanalytics.com/blog/priority-queues-algorithm-optimization-deep-dive

[^42]: https://www.mcehassan.ac.in/assets/departments/AIML/materials/Module-1.pdf

