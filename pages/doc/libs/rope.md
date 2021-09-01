# rope


### ROPE_LEAF_LEN (const)


### rope (struct)
__Its methods are:__
- <code>**getParent**() rope&ast; </code> Used to get the parent of the node.
*Note: this is an internal function.*
- <code>**addStr**(s cpstring&ast;) </code> Used to add the content of the node to a specified cpstring.
*Note: this is an internal function.*
- <code>**toStr**() cpstring </code> Used to get the rope as a cpstring.
- <code>**add**(root2 rope&ast;) rope&ast; </code> Used for concatenation.
This is the method that will be called when doing `a + b`.


### createRopeStructure (func)
<code>createRopeStructure(par rope&ast;, a cpstring, l int, r int) rope&ast; </code>
This is used to initiate a new node.
a: the content of the node
l: the left offset
r: the right offset
*Note: this is an internal function.*


### concatenateRopes (func)
<code>concatenateRopes(root1 rope&ast;, root2 rope&ast;) rope&ast; </code>
Old way of concatenating ropes by specifying in order the ropes to concatenate.


### rope (func)
<code>rope(a cpstring) rope&ast; </code>
Used to initiate a rope with a cpstring.


## Example
```bah
 main(args []cpstring) int {
     a = rope("This is a test: ") //Initiates rope a
     b = rope("I'm a substring.") //Initiates rope b
     i=0; for i &lt; 99999 { //Iterates from 0 to 99998 (executes the following code 99999 times)
         a = a + b //Concatenates b to a
         i = i + 1 //Increments i by 1
     }
     println(a.toStr()) //Converts a to a cpstring and prints it
 }
```