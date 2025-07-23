# **Applying Design by Contract to C**

*Exploring a practical approach to bringing DbC principles to a language that predates them.*

## Synopsis

Design by contract was first coined by Bertrand Meyer in connection with the Eiffel programming language, and it was described in various articles starting in 1986, as well as in his book "Object-Oriented Software Construction" published in 1988 and 1997. The concept emphasizes defining formal interface specifications for software components, akin to business contracts. [Wikipedia](https://en.wikipedia.org/wiki/Design_by_contract)

## **Motivation**

C's reputation for speed comes with a well-known caveat: safety is largely left to the programmer. While `assert()` provides basic sanity checking, it disappears entirely in release builds - leaving production code vulnerable to subtle (and not-so-subtle) errors. This gap led me to explore how Design by Contract (DbC) principles could be applied in C programming but in a way that feels native to the language's philosophy.

I do not like writing boilerplate code and testing for errors with a myriad of ``` if then else``` constructs tends to drown out the interesting parts. I also tend to make a poor job of implementing it and, whilst I have tended to favour asserts with a message ```assert(ptr && "NULL pointer!")``` they are not only emphemeral but lack the semantic power of well written DbC. 

My DbC for C approach, embodied in the ``` contract.h```header file and its companion ```posix_errno.h``` definitions file (more on that one later), focuses on making assumptions explicit and catching violations early. Hopefully turning hours of debugging into minutes of clear, and logged, diagnosis. 

Interestingly, a less tangible benefit that grows on you with using DbC is that it helps you think and then program more defensively, and start to freely incorporate DbC safety into the code - rather than begrudgingly bolt on error checking as an after thought. An unexpected and pleasant benefit of DbC.

## **Core Concepts: require, ensure, invariant**

The foundation rests on three types of assertions:

1. **Preconditions (`require`)** : Conditions that *must* be true before a function executes. These are the caller's responsibility. If a file descriptor is needed, `require_fd(fd >= 0, "...")` makes it explicit and checks it.
2. **Postconditions (`ensure`)** : Conditions that *must* be true after a function completes successfully. This is the function's promise. `ensure(result != NULL, "...")` guarantees a valid return value.
3. **Invariants (`invariant`)** : Conditions that must hold true throughout the lifetime of a data structure or during critical sections (like holding a lock). `invariant(list->count >= 0, "...")` enforces structural integrity.

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
[2024-07-22 15:30:00] arena.c:10|_mem(buf != NULL|ENOMEM(Bad address)|FAILED memory allocation!
```

### **2. Network Protocol Handling**

**Before:** A sea of error checking bolted on as an after thought once the protocol handling code is working.

```
int send_packet(int sock, Packet* pkt) {
    if (sock < 0) return -1;
    if (!pkt) return -1;
    if (pkt->size > MAX_PKT_SIZE) return -1;
    if (pkt->version != 3) return -1;
    // etc., etc.
}
```

**After:** Declarative and woven in to code with a DbC mindset

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

## **Why This Approach?**

Moving from implicit assumptions to explicit contracts has changed how I write and debug C code.

- **Clarity:** Functions document their interface requirements directly in code. I have liked clean code concepts for some time and DbC helps move code towards being more self explanatory.
- **Fail Fast:** When a contract is violated, the program terminates immediately with a clear error message, including POSIX error codes (`EINVAL`, `ENOMEM`, etc.) and contextual information. 
- **Performance Consideration:** The overhead is minimal for correct code paths – essentially just an `if` check - respecting C's performance ethos.

## **Implementation Notes**

The implementation focuses on practicality and portability.

- **POSIX Errors:** Using standard POSIX error codes `posix_errno.h` provides a portable and well-understood taxonomy for reporting failures, rather than inventing custom error schemes. 
- **Crash Reporting:** Violations trigger a concise, structured log message (timestamp, file, line, condition, error code, message) before calling `abort()`. This aids debugging without complex error handling paths.
- **Minimal Overhead:** The core checking logic is designed to be simple and inline-friendly. The crash reporter itself avoids heap allocation to be usable even in constrained environments.

## **Limitations and Considerations**

This is an experimental approach, and it's important to understand its boundaries.

- **Not Magic:** Contracts catch *programming errors* – violations of explicit assumptions. They do not handle runtime resource exhaustion or invalid user input that should be handled gracefully.
- **Performance:** While overhead is minimal for correct paths, placing many checks in performance-critical loops requires careful measurement.
- **Discipline:** The benefits only accrue if contracts are used consistently and meaningfully.

This exploration of DbC for C has been driven by a desire to write more robust systems code without abandoning C's core strengths. Whether retrofitting safety into existing codebases or building new ones with a more natural safety-mindedness, this approach has proven valuable in my own projects. 

Contracts for C is a tangible result of this ongoing effort, aiming to make defensive C programming more accessible, natural and effective.
