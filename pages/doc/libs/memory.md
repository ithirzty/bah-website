# memory


### SIZE_OF_INT (const)


### SIZE_OF_CHAR (const)


### SIZE_OF_INT32 (const)


### SIZE_OF_FLOAT32 (const)


### SIZE_OF_FLOAT (const)


### len (func)
<code>len(a ptr) int </code>
Will return the length of an array.
This only works on arrays.


### memoryAlloc (func)
<code>memoryAlloc(s int) ptr </code>
Used for allocating memory (malloc in c). You must specify the size of the block to allocate.
Will return a pointer to the allocated block. The memory is garbage collected.
The allocated memory cannot be shared by multiple processes. Use the sharedMemory() function instead.


### destroy (func)
<code>destroy(a ptr) </code>
Destroy will force to free a pointer.


### clear (func)
<code>clear(a ptr) </code>
Clear will remove the content of an array.


### append (func)
<code>append(a ptr, b ptr) </code>
Append will add the array b to the array a.
Note: doesn't work with []char.


### copy (func)
<code>copy(a ptr, b ptr) </code>


### memoryRealloc (func)
<code>memoryRealloc(p ptr, s int) ptr </code>
Will realloc memory to a specified pointer.
*The data contained in the block of memory is not necessarly preserved.*


### PROT_READ (const)


### PROT_WRITE (const)


### MAP_SHARED (const)


### MAP_ANONYMOUS (const)


### sharedMemory (func)
<code>sharedMemory(size int) ptr </code>
Will allocate a page of shared memory and returns a pointer to it.
The size should be an multiple of 4096. A size of 0 will set the page size to the default (4096).
Shared memory can be shared between two processes (after the use of fork()).


## Example
```bah
 &num;include "string.bah"
 &num;include "memory.bah"
 main() {
     a cpstring = memoryAlloc(30)
     strcpy(a, "Hi!")
 }
```