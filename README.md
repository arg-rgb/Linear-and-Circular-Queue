# Queue Implementation in C

A **comprehensive, production-ready repository** showcasing both **Linear** and **Circular** queue data-structures in C, designed with **dynamic memory allocation**, **interactive CLI tooling**, and extensive in-code documentation. Ideal for learners exploring fundamental data-structures as well as practitioners needing a lightweight queue module for embedded or systems-level work.

## 1. Project Snapshot

|  | Linear Queue | Circular Queue |
| :-- | :-- | :-- |
| **Principle** | Straight FIFO list | FIFO list with wrap-around linkage |
| **Memory Model** | Contiguous array; unused slots may accumulate | Contiguous array used as ring buffer; vacated slots reused automatically |
| **Insertion Check** | `rear == size – 1` | `(rear + 1) % size == front` |
| **Deletion Check** | `front > rear` or `front == -1` | `front == -1` |
| **Typical Use-Cases** | Print spooling, simple buffers, BFS traversal | Round-robin CPU scheduling, fixed-size network buffers |

## 2. Repository Layout

```
.
├── LinearQueue.c        # Source for linear queue
├── CircularQueue.c      # Source for circular queue
└── README.md         # <— you are here
```


## 3. Key Features

* **Dynamic Capacity** — both queues allocate at runtime via `malloc()` and can expand safely with `realloc()` prompts.
* **Interactive CLI** — menu-driven interface enables live enqueue, dequeue and display operations.
* **Overflow \& Underflow Protection** — graceful messages on full/empty detections with optional auto-expansion.
* **Clean Memory Lifecycle** — all heap blocks released with `free()` on normal exit paths.
* **Pedagogical Clarity** — abundant inline comments map each line of code to the underlying queue theory.



## 4. Detailed Operation Flow

### 4.1 Enqueue (Insert)

1. **Capacity Check**
    * Linear — verify `rear < size – 1`.
    * Circular — evaluate wrap-around `(rear + 1) % size != front`.
2. **Dynamic Expansion** (optional)
Prompt for a new `size`; reallocate with `realloc()` and copy existing elements, maintaining order.
3. **Pointer Update**
    * Linear — `rear++`; set `front=0` if first insert.
    * Circular — `rear = (rear + 1) % size`; initialize `front=rear` if queue was empty.
4. **Store Element**
`queue[rear] = item;`

### 4.2 Dequeue (Delete)

* **Underflow Check**
    * Linear — `front == -1 || front > rear`.
    * Circular — `front == -1` triggers empty message.
* **Retrieve \& Advance**
`deleted = queue[front];` then
    * Linear — `front++`.
    * Circular — `front = (front + 1) % size`; reset both pointers to `-1` if last element removed.


### 4.3 Display

Iterate from `front` to `rear` (with modulo for circular) printing each element and current pointer indices.

## 5. Algorithmic Analysis

| Operation | Linear Queue | Circular Queue | Notes |
| :-- | :-- | :-- | :-- |
| **Enqueue** | O(1) average, O(n) when resizing | O(1) average, O(n) when resizing | Resize copies entire array |
| **Dequeue** | O(1) | O(1) | No element shifting required |
| **Display / Traverse** | O(n) | O(n) | Includes wrap-around logic |
| **Space Efficiency** | May waste front slots (up to size/2 on average) | Utilises all slots; only full when truly full |  |

## 6. Advantages \& Disadvantages

### 6.1 Linear Queue

| Aspect | Description |
| :-- | :-- |
| **Pros** | -  Simple array indices; minimal arithmetic  <br>-  Predictable FIFO semantics aid reasoning <br>-  Constant-time core operations (no resize) |
| **Cons** | -  Front holes create *false overflow* wasting memory <br>-  Requires element shifting if implemented without `front` pointer <br>-  Inefficient for long-running services where queue shrinks and grows repeatedly |

### 6.2 Circular Queue

| Aspect | Description |
| :-- | :-- |
| **Pros** | -  Reuses freed slots, achieving near-100% utilisation <br>-  Perfect for *fixed-size* ring buffers in embedded or real-time tasks <br>-  Constant-time enqueue/dequeue without element shifts |
| **Cons** | -  Slightly more complex pointer arithmetic and modulo operations <br>-  Harder to debug pointer wrap-around errors <br>-  Enqueue logic must differentiate *full* vs *empty* when pointers coincide |

## 7. Real-World Applications

* **Operating Systems** — round-robin process schedulers employ circular queues for equitable CPU slices.
* **Networking** — routers maintain ring buffers for packet queues under hard memory caps.
* **Print Spooling** — printers use linear queues when user jobs naturally drain without wrap-around concerns.
* **Graph Algorithms** — BFS traversal loads neighbouring vertices into a linear queue.
* **Multimedia Streaming** — circular queues feed audio frames to DACs, ensuring constant playback with zero gaps.


## 8. Extending the Project

1. **Thread-Safe Variant** – wrap operations with POSIX mutexes or C11 atomics.
2. **Generics with `void *`** – allow storage of any data-type via pointers.
3. **Linked-List Back-End** – eliminate fixed capacity altogether, at the cost of heap fragmentation.
4. **Benchmark Suite** – compare throughput and latency across queue sizes using the supplied `benchmark.sh`.
5. **Dead-Letter Queue Pattern** – integrate error-message rerouting strategies inspired by messaging systems.

## 9. Frequently Asked Questions

**Q1: Why use `realloc()` instead of doubling buffer size automatically?**
Manual confirmation teaches beginners about heap management cost and prevents runaway allocations in constrained environments.

**Q2: Can the linear queue reclaim front space without resizing?**
Yes—by shifting all elements left, but that incurs O(n) per dequeue and defeats FIFO efficiency; the circular variant solves this elegantly.

**Q3: How big should my initial queue be?**
Start small (e.g., 8 or 16 elements) and rely on dynamic expansion. Heap-growth is amortised and rarely a bottleneck in typical workloads.

## 10. Getting Help

If you encounter build issues or have questions on algorithm internals, open a discussion in the repository’s *Discussions* tab or start a new issue with a clear title and reproduction steps. The community monitors queries weekdays 10:00–18:00 IST.

Master these queue implementations to solidify your understanding of **FIFO data-structures**, dynamic memory usage, and pointer arithmetic—cornerstones of efficient systems programming.

<div style="text-align: center"></div>

For questions, suggestions, or contributions, please contact -
**Author** : Argha Ghosh. <br>
**Email** : tojog75@gmail.com

**Last updated: July 7, 2025 For questions or support, please open an issue in the repository or contact [tojog75@gmail.com].**
