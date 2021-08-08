# queue


### queueNode (struct)
An internal structure used to define a single node (element) of the queue.


### queue (struct)
A wrapper for the queue.
A queue is a data-type like an inverted stack.
Inserting an element to it will put it on the top as the first element.
Popping an element of it will return and remove the last element. 
Keys works simillarly to the keys of an array. Each element as a key (index) that starts from 0.
*Note: queue can only contain pointers.*
__Its methods are:__
- <code>**insert**(data ptr) </code> Used to insert an element at the top of the queue.
- <code>**delete**(key int) </code> Used to delete an element mapped to the specified key.
- <code>**get**(key int) ptr </code> To get an element by its key.
- <code>**set**(key int, data ptr) </code> To replace an element at a specified key.
- <code>**pop**() ptr </code> To get and remove the last element (at the bottom of the queue).
This will return the oldest element of the queue.
This method does not matter about the key of the element.
- <code>**clear**() </code> To clear (remove every element) of the queue.


## Example
<code> #include "iostream.bah"
 #include "queue.bah"
 main() {
 queue = queue{}
 queue.insert("a")
 queue.insert("b")
 s = queue.pop()
 println(s) //will print a
 s = queue.pop()
 println(s) //will print b
 }
</code>