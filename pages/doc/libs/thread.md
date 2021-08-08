## thread.bah


### Functions/Structure/Types


##### mutex (function)
Used for creatting and initiating a mutex as: <code>mutex() mutex</code>


##### mutex (struct)
A mutex (lock) to make your program thread safe.<br>Its methods are:
- <code>init()</code> to initialize the mutex
- <code>lock()</code> to lock the mutex
- <code>unlock()</code> to unlock the mutex
- <code>destroy()</code> to destroy the mutex after you're done using it.


##### thread (struct)
A wrapper for creatting and handling a thread.<br>Its methods are:
- <code>handle()</code> you will need to set the handle to the function to execute in a different thread
- <code>create()</code> to create a new thread
- <code>createWithArg(arg ptr)</code> to create a new thread passing an argument
- <code>wait()</code> to wait for the end of the thread's execution


#### Example
<code>
#include "iostream.bah"
#include "thread.bah"

printHello() {
    println("Hello")
}

main() {
    t = thread{}
    t.handle = &printHello
    t.create()
    t.wait()
}
</code>