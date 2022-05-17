<section>
# Memory
There is two types of memory in Bah, the **stack** and the **heap**.
Variables declared on the stack have fixed size and an expected lifetime.
Variables declared on the heap can grow and shrink, further more, they are accessible until there are no more reference to them. 

- [Heap](#heap),
- [pointers](#pointers).

<span id="heap"></span>
## Heap
Some types such as channels, arrays and maps are always declared on the heap. This means that they should not be duplicated.
Passing an array as argument to a function will not duplicate the array. Both function will access and edit the same data.

[Structures](./structures) can easily be declared on the heap using the **new** keyword.

For other data types, you can use the **memoryAlloc(size int) ptr** function. Provided a size, this will return a pointer to the allocated block of memory. *If you are not programming at a low level, you should not use this function.*

```bah
<var>myBlock</var> = <func>memoryAlloc</func>(<val>64</val>) <comment>//Will allocate 64 bytes of memory</comment>
```

<span id="pointers"></span>
## Pointers
A pointer is a reference to a block of memory.

To make a pointer, you can either [allocate some memory](#heap) or get the pointer of a stack variable.
You can dereference a pointer to access the value that it is pointing to.
```bah
<var>myVar</var> = <val>55</val> <comment>// type of myPtr: int </comment>
<var>myPtr</var> = <var>&myVar</var> <comment>// type of myPtr: int* </comment>
<var>*myPtr</var> = <val>47</val> <comment>//Value of myVar is now 47.</comment>
```

### Example
```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> <str>"iostream.bah"</str>
<hash>#import</hash> <str>"string.bah"</str>

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {

    <var>myVar</var> = <val>55</val> <comment>// type of myPtr: int </comment>
    
    <func>println</func>(<func>intToStr</func>(<var>myVar</var>)) <comment>//Will print 55</comment>
    
    <var>myPtr</var> = <var>&myVar</var> <comment>// type of myPtr: int* </comment>
    <var>*myPtr</var> = <val>47</val> <comment>//Value of myVar is now 47.</comment>

    <func>println</func>(<func>intToStr</func>(<var>myVar</var>)) <comment>//Will print 47</comment>

    <kw>return</kw> <val>0</val>
}
```

</section>