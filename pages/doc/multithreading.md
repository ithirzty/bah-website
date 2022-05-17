<section>
# Multithreading
Multithreading is used to make some parts of your program run in parallel (concurrently).
This is often tricky, but luckily, Bah comes with helpers for multithreading.


- [Async calls](#async_calls),
- [thread safety](#thread_safety).

<span id="async_calls"></span>
## Async calls
A thread is defined by an entry point just as the program as **main** as entry point.

This means that you can basically launch functions in other threads. To do so, we need to perform an async call:
```bah
<kw>async</kw> <func>myFunc</func>() <comment>//Will launch myFunc in another thread</comment>
```

<span id="thread_safety"></span>
## Thread safety
In the cases where multiple threads need to read/write to the same variable, this could lead to undefined behavior.

Lets say we have a global variable called count that is just an integer. If thread 1 and thread 2 both fetch, increment and save the value of count at the same time, count will not be incremented by 2 but by 1.

To avoid this problem, we need to synchronize threads to make sure that two threads do not access the same variable at the same time. To do so, we can use:
- [channels](./channels) where a single thread receive or send data to all the threads. This will make sure that not two threads get the same value.
- Mutexes are locks. When a thread obtain the lock of a mutex, other threads will need to wait for the thread to release the lock before obtaining it.
```nope

thread1: obtain lock -> do some stuff -> release lock
thread2: try to lock ->     wait      -> obtain lock  -> do some stuff
```

### Mutex
Mutexes are defined in the file **"thread.bah"**, make sure it is imported/included.

To declare a mutex:
```bah
<var>myMutex</var> = <func>mutex</func>()
```

To lock a mutex:
```bah
<var>myMutex</lock>.<func>lock</func>()
```

To unlock a mutex:
```bah
<var>myMutex</lock>.<func>unlock</func>()
```

To destroy a mutex:
```bah
<var>myMutex</lock>.<func>destroy</func>()
```

### Mutexes and channels are not enough?
If you need more control, you can use a **mutexCondition**.
This is used as a wrapper for a condition. One threads waits for the condition to be true, another one sends a signal when it may be the case:

Thread 1:
```bah
<kw>if</kw> <var>someStuff</var> == <var>true</var> {
    <var>myCond</var>.<func>send</func>()
}
```

Thread2:
```bah
<kw>for</kw> <var>someStuff</var> != <var>true</var> {
    <var>myCond</var>.<func>wait</func>()
}
```

</section>