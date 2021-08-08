## queue.bah


### Functions/Structure/Types


##### queue (struct)
A simple implementation of linked lists (enables you to make queue without fixed sizes).<br>*A queue can only contain pointers.*<br>Its methods are:
- <code>insert(data ptr)</code> to insert a value inside the queue
- <code>delete(key int)</code> to delete a value inside the queue
- <code>get(key int) ptr</code> to retreive a value inside the queue
- <code>set(key int, data ptr)</code> to set a value inside the queue by key
- <code>pop() ptr</code> to get the last element and delete it *(usefull for queues)*

It's fields are:
- <code>length int</code> the current queue's length


#### Example
<code>
#include "iostream.bah"
#include "queue.bah"

main() {
    //todo
}
</code>