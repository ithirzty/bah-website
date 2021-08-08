# thread


### mutex (struct)
This structure implements a mutex.
A mutex is a thread safe lock.
*Note: the mutex needs to be initiated ans destroyed when you finished using it.*
__Its methods are:__
- <code>**init**() </code> This initiaties the mutex.
- <code>**lock**() </code> This locks the mutex.
Every other thread trying to lock it will need to wait for it to be unlocked.
- <code>**unlock**() </code> This unlocks the mutex.
- <code>**destroy**() </code> This destroyes the mutex.


### thread (struct)
A wrapper for a thread.
__Its methods are:__
- <code>**handle**(id int) </code> This will need to ne set by the user.
The specified function will be the entry point for the thread.
- <code>**create**() </code> This will launch the thread.
- <code>**createWithArg**(arg ptr) </code> This will launch the thread by passing to its entry point funtion an argument.
The argument can only be a pointer.
- <code>**wait**() </code> This waits until the thread has finished executting.


### mutex (func)
<code>mutex() mutex </code>
This initiates a mutex and returns it.


## Example
<code> #include "iostream.bah"
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