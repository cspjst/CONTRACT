![](https://github.com/cspjst/RESOURCE/blob/main/LOGOS/DbC_Shield_128x114.png)
# **Applying Design by Contract to C**
![Pair Programming](https://img.shields.io/badge/PAIR_PROGRAMMING-CO--DEVELOPED_WITH_QWEN3-8a2be2?style=flat&logo=alibaba&logoColor=white)

*Exploring a practical approach to bringing DbC principles to a language that has a bad reputation for safety.*

## Synopsis

> Design by contract was first coined by Bertrand Meyer in connection with the Eiffel programming language, and it was described in various articles starting in 1986, as well as in his book "Object-Oriented Software Construction" published in 1988 and 1997. The concept emphasizes defining formal interface specifications for software components, akin to business contracts. [Wikipedia](https://en.wikipedia.org/wiki/Design_by_contract)

My background reading suggests that Design by Contract (DbC) has never been mainstream and, even within academic circles, fell from favour. I think that, for its time at least, it was seen as an over-engineered solution to a set of problems that seem to have been regarded as less important(?).

However, time has moved on and, through bitter experience, the concepts of security, correctness, and accountability have taken firm root in the programming zeitgeist - driving development responses such as Test Driven Development (TDD) and languages like RUST.

I think that Design by Contract, or rather a modern pragmatic approach to it, can help constrain some of the downsides of programming in C, and, actually empower those of us who still choose to program in C to deliver _safer_ C.

## **Motivations**

C's reputation for speed comes with a well-known caveat: safety is largely left to the programmer. While `assert()` provides basic sanity checking, it disappears entirely in release builds, leaving production code vulnerable to subtle (and not-so-subtle) errors. This gap led me to explore how Design by Contract principles could be applied in C programming but in a way that feels native to the language's philosophy.

I do not like writing boilerplate code and testing for errors with a myriad of ``` if then else``` constructs tends to drown out the interesting parts. I also tend to make a poor job of implementing it and, whilst I have tended to favour asserts with a message ```assert(ptr && "NULL pointer!"``` they are not only ephemeral but lack the semantic power of well written DbC.

My DbC for C approach, embodied in the ```contract.h``` file and its companion ```posix_errno.h``` definitions file (more on that one later), focuses on making assumptions explicit and catching violations early. That has, experientially, turned frustrating debugging into clear, and logged, diagnosis.

Interestingly, a less tangible benefit that grows on you with using DbC is that it helps you think and then program more defensively. I found myself freely incorporating DbC safety into the code - rather than begrudgingly bolt on error checking as an after thought. An unexpected and pleasant benefit of DbC.

## Prior Art

Apart from the excellent [DbC for embedded C by Quantum Leap](https://github.com/QuantumLeaps/DBC-for-embedded-C) I could not find anything else specific to C.

## **Core Concepts: require, ensure, invariant**

The foundation rests on three types of assertions:

1. **Preconditions (`require`)** : Conditions that *must* be true before a function executes. These are the caller's responsibility. If a file descriptor is needed, `require_fd(fd >= 0, "...")` makes it explicit and checks it.



2. **Postconditions (`ensure`)** : Conditions that *must* be true after a function completes successfully. This is the function's promise. `ensure(result != NULL, "...")` guarantees a valid return value.



3. **Invariants (`invariant`)** : Conditions that must hold true throughout the lifetime of a data structure or during critical sections (like holding a lock). `invariant(list->count >= 0, "...")` enforces structural integrity.

Looking at this you might think, as I did, that ```require```, ```ensure```, and ```invariant``` are just 3 macros with an error message that ignore NDEBUG. Further, it could, rightly, be argued that there is no functional difference between the 3 DbC keywords, but this would be to miss the semantic point of DbC - an explicit and compact narrative of intent, _guaranteed_ intent.

Perhaps then, and this is where the pragmatic part comes in, there is more to be gained by adding both more semantic meaning and more debug feedback to three DbC keywords?

To this end I have extended ```require``` to a further 45 error condition specific keywords, such as ```require_address``` and ```require_fd```. The ```require_*``` family of preconditions not only add to the self documenting nature of code, they make the guarantees specific and the error logs more detailed. Further, and because the list of the symbolic error names are derived from the *POSIX.1-2001* ```errno.h``` header file, they have wide practical application and a degree of standards based gravitas.

## Extensions to require

The ```require_*``` extensions are grouped into 6 subsets, those being (ordered by personal experience of their utility):
Memory/Address Contracts, Filesystem Contracts, Network Contracts, Process/System Contracts, Math/Domain Contracts, and Stream Contracts.

A few before and after examples should help explain how they are used:

### **1. Memory Allocation**

**Before:** Opaque NULL returns are one of my pet peeves.

```c
void* allocate_buffer(size_t size) {
    if (size == 0) return NULL;  	// Schrödinger's error: intentional or bug?
    return malloc(size);
}
```

**After:** Rigid performance guarantees - returns a buffer or aborts with a detailed and logged error report.

```c
void* allocate_buffer(size_t size) {
    require_range(size > 0 && size <= MAX_BUFFER, "INVALID size!");  // Fails with ERANGE
    void* buf = malloc(size);
    require_mem(buf != NULL, "FAILED memory allocation!");  // Fails with ENOMEM
    return buf;  // turns "out of memory" from a silent killer into a logged event.
}
```

**Error Log example:**

```
[2024-07-22 15:30:00] arena.c:10|require_mem(buf != NULL)|ENOMEM(Bad address)|FAILED memory allocation!
```

### **2. Network Protocol Handling**

**Before:** A sea of vague error checking bolted on as an after thought once the protocol handling code is working.

```c
int send_packet(int sock, Packet* pkt) {
    if (sock < 0) return -1;
    if (!pkt) return -1;
    if (pkt->size > MAX_PKT_SIZE) return -1;
    if (pkt->version != 3) return -1;
    // etc., etc.
}
```

**After:** Declarative and woven in to code with a DbC mindset.

```c
int send_packet(int sock, Packet* pkt) {
    require_fd(sock >= 0, "SOCKET error!");
    require_address(pkt, "NULL packet!");
    require_range(pkt->size <= MAX_PKT_SIZE, "PACKET too large!");
    require(pkt->version == 3, "Version error!");

    ssize_t sent = send(sock, pkt, pkt->size, 0);
    require_io_success(sent == pkt->size, "SEND failure!");
    return 0;
}
```

**Error Log example:**

```
[2024-07-22 15:30:00] server.c:10|require_address(requested_path)|14(Bad address)|NULL packet!
```

### **3. Thread Safety**

**Before:** I really dislike adding these kind of comments...

```c
// NOTE: Caller must hold mutex!
void update_cache(Cache* cache, Data* data) {
    assert(cache);  // Disappears in production
    ...
}
```

**After:** Runtime-enforced discipline

```c
void update_cache(Cache* cache, Data* data) {
    require_address(cache, "NULL cache!");
    require_address(data, "NULL data!");
    invariant(pthread_mutex_is_locked(&cache->lock), "MUTEX invariant broken!");

    ...
    ensure(cache->size < CACHE_MAX, "CACHE broken"); // there is no return if the post-condition is not met
}
```

**Error Log example:**

```
[2024-06-12 09:00:00] cache.c:42|invariant(is_locked)|35(EDEADLK)|MUTEX invariant broken!
```

## Extensions to ensure and invariant

When it comes to ```ensure``` there is only a limited number of 6 ```ensure_*``` extensions and ```invariant``` has none.

To me this makes sense because ```require``` guards against external faults, such as invalid inputs, system errors, etc. All of which maps nicely to the POSIX standard as a familiar semantic alignment to system-level errors with standardized meanings. Whereas, ```ensure``` concerns itself with logical errors as per the post-condition concept of DbC. As such, the ```ensure``` post-condition keyword validates internal function correctness - not system errors.

By example post-condition logical correctness:

```c
// 1. Function return validation
double calculate_ratio(double a, double b) {
    double result = a / b;
    ensure(!isnan(result), "Invalid ratio computed");  // Catch math errors
    return result;
}

// 2. State machine integrity
void handle_state_transition(StateMachine* sm) {
    State new_state = /* complex logic */;
    ensure(is_valid_state(new_state), "Invalid state transition");
    sm->current = new_state;
}
```

Having said it all that, there is frequently overlap with post-condition errors and POSIX error values.

To that end I have extended ```ensure``` to 6 ```ensure_*``` specialisations that cover some 90% of the POSIX-relevant post-conditions that I have so far encountered and do so without over-engineering. Further, the 6 ```ensure_*``` extended keywords are split into 3 groups, namely:
Memory/Validity Guards, Mathematical Guarantees, and State Consistency.

Again, by example POSIX error overlaps for post-condition logical correctness:

```c
// 1. Pointer chains (avoid segfaults)
void process_config(Config* cfg) {
    ensure_address(cfg->network, "Missing network config");  // Implies EFAULT
    ensure_valid_encoding(cfg->hostname, "Invalid hostname encoding");  // Implies EILSEQ
}

// 2. API boundary checks
void* aligned_alloc(size_t alignment, size_t size) {
    void* ptr = _aligned_malloc(size, alignment);
    ensure_address(ptr, "Allocation failed");  // More explicit than vanilla ensure
}
```

```c
// 1. Physics simulation
void update_particle(Particle* p) {
    p->velocity += p->acceleration * DT;
    ensure_in_range(p->velocity, -C_LIGHT, C_LIGHT, "Relativity violation");  // Implies ERANGE

    p->energy = calculate_energy(p);
    ensure_no_overflow(p->energy, "Energy overflow");  // Implies EOVERFLOW
}

// 2. Financial calculations
Money convert_currency(Money amount, double rate) {
    Money result = amount * rate;
    ensure_in_range(result, -MAX_MONEY, MAX_MONEY, "Monetary overflow");
    ensure_no_overflow(result, "Arithmetic overflow");
    return result;
}
```

I thought long and hard about ```invariant``` and concluded that, based upon the DbC concept that an invariant is an absolute truth about the scope that the code is working in. Such that ```invariant``` should be reserved for situations that POSIX error codes can not meaningfully embrace - such as undefined behaviour.

Conceptually, ```invariant``` has been the trickiest of the 3 ideas to grasp. It seems that invariants are more subtle than pre/postconditions in that they capture something fundamental about object/state consistency - a code block's extant operating universe, if you will. That is, something that error codes alone are unable to express.

I think invariants in C should be seen as trying to protect the lifetime state of a block of code and guard against that great enemy of C code, undefined behaviour (UB). Ultimately then, I think invariants are about guaranteeing the predicates upon which the programmer's reasoning are founded.

To express this by example consider a runtime memory allocated but fixed sized structure such as a bounded array. Our reasoning about it is based upon the fact that it is bounded, and the invariants flow from that:

```c
typedef struct {
    int* data;
    size_t size;      // number of elements currently stored
    size_t capacity;  // maximum elements buffer can hold
} bounded_dynamic_array_t;

// INVARIANT: 0 <= size <= capacity
// INVARIANT: if capacity > 0, then data != NULL
// INVARIANT: if capacity == 0, then data == NULL
```

Creation establishes the invariants:

```c
bounded_dynamic_array_t* bda_create(size_t initial_capacity) {
    bounded_dynamic_array_t* arr = malloc(sizeof(bounded_dynamic_array_t));

    if (initial_capacity == 0) {
        arr->data = NULL;
        arr->capacity = 0;	// INVARIANT: if capacity == 0, then data == NULL
    } else {
        arr->data = malloc(initial_capacity * sizeof(int));
        require_mem(arr->data != NULL, "FAILED memory allocation!");  // Fails with ENOMEM
        arr->capacity = initial_capacity; // INVARIANT: if capacity > 0, then data != NULL
    }

    arr->size = 0;    // INVARIANT: 0 <= size <= capacity
    return arr;
}
```

Destruction invalidates the predicates and, ergo, the array's invariants:

```c
void bda_destroy(bounded_dynamic_array_t* arr) {
    require_address(arr, "NULL array!");
    free(arr->data);
    free(arr); // Object is now invalid - no need to maintain invariants
    // No explicit return needed as function is void and contracts abort on failure
}
```

However, in between creation and destruction every function that touches the ```bounded_dynamic_array_t``` must maintain its invariants:

```c
#include "contract.h"

void bda_append(bounded_dynamic_array_t*  arr, int value) {
		// Precondition
    require(arr != NULL, "Array pointer must not be NULL");

    // Invariant check before operation
    invariant(arr->size <= arr->capacity, "Size must not exceed capacity");
    invariant((arr->capacity > 0) == (arr->data != NULL), "Capacity and data pointer must be consistent");

    // Store original state for postcondition
    size_t old_size = arr->size;

    // Need to grow?
    if (arr->size == arr->capacity) {
        size_t new_capacity = (arr->capacity == 0) ? 4 : arr->capacity * 2;
        int* new_data = realloc(arr->data, new_capacity * sizeof(int));
        require_mem(new_data != NULL, "Memory allocation failed for array growth");

        arr->data = new_data;
        arr->capacity = new_capacity;
    }

    // Perform operation
    arr->data[arr->size] = value;
    arr->size++;

    // Postconditions
    ensure(arr->size == old_size + 1, "Size must increase by one");
    ensure(arr->data[arr->size - 1] == value, "Appended value must be at end");
    ensure(arr->size <= arr->capacity, "Size must not exceed capacity after append");
    ensure(arr->data != NULL, "Data pointer must not be NULL after append");

    // Invariant check after operation
    invariant(arr->size <= arr->capacity, "Size must not exceed capacity");
    invariant((arr->capacity > 0) == (arr->data != NULL), "Capacity and data pointer must be consistent");
}
```

Yes, it may seem like a lot of extra code but it is only 10 lines and without DbC there would likely be a spaghetti of confusing ```if``` statements as well as being much less self documenting and, I would have much less confidence in it.

## **Implementation Notes**

The implementation focuses on practicality and portability.

Portability is achieved by bringing along the *POSIX.1-2001* error codes in the ```posix_errno.h``` header file. Practicality arrives in the form of the error reporting/logging concise, structured log messages (timestamp, file, line, condition, error code, message) before calling `abort()`. The error reporting code is deliberately minimal and log file orientated but, of course, you are free to modify it to your own needs. Of note, the crash reporter itself avoids heap allocation to be usable even in constrained environments.

## Limitations and Considerations

This is an experimental approach, and it's important to understand its boundaries.

Neither Design by Contracts nor this implementation of it in C is a panacea for all errors. Contracts catch programming errors and violations are singular and final, triggering ```abort```. DbC is not designed for, nor do I attempt to enable, errors that are recoverable or should be handled gracefully.

There is a performance hit it is minimal, being implemented for each keyword as a single ```if true``` fast path for the error free outcome. However, there will always be a price to pay for errors whether or not you choose to handle them - you appetite for risk and the size of that of price will direct your choices.
