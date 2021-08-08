## memory.bah


### Functions/Structure/Types


##### memoryAlloc (function)
Used for allocating memory as: <code>memoryAlloc(size int) ptr</code>.
The allocated memory is garbage collected. You can use the C functions <code>malloc</code> and <code>free</code> to manage your memory by yourself.


##### detroy (function)
Used for de-allocating a pointer as: <code>destroy(pointer ptr)</code>.
*It is not recommended to use this function as memory is already managed and this may result in corrupted data.*


##### clear (function)
Used for clearing the content of an array as: <code>clear(array ptr)</code>.
*It is not recommended to use this function as memory is already managed and this may result in corrupted data.*


##### memoryRealloc (function)
Used for reallocation a pointer, as: <code>memoryRealloc(pointer ptr, size int)</code>. *The content of the pointer may not be preserved.* If not successful, will return a zero pointer.


#### Example
<code>
#include "string.bah"
#include "memory.bah"

main() {

    a cpstring = memoryAlloc(30)
    strcpy(a, "Hi!")

}
</code>