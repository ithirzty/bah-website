# flags


### FLAG_TYPE_CPSTRING (const)


### FLAG_TYPE_INT (const)


### FLAG_TYPE_FLOAT (const)


### FLAG_TYPE_BOOL (const)


### flag (struct)
A wrapper for parsing the arguments of the program as flags.
A flag is an argument beginning by a '-'.
*Note: the -h/-help flag is already defined and should be redefined.*


### flags (struct)
__Its methods are:__
- <code>**addString**(name cpstring, help cpstring) </code> To add a flag to be parsed as a cpstring.
- <code>**addBool**(name cpstring, help cpstring) </code> To add a flag that can either be set or not.
This flag cannot contain any value.
- <code>**addInt**(name cpstring, help cpstring) </code> To add a flag that will be parsed as a int.
- <code>**addFloat**(name cpstring, help cpstring) </code> To add a flag that will be parsed as a float.
- <code>**invalidate**() </code> This will invalidate all the flags.
It will print the help message and gracefully exit the program.
- <code>**getFlag**(name string) flag&ast; </code> To get the flag as a pointer to the flag.
This should normally not be used.
- <code>**get**(name cpstring) cpstring </code> To get the content of a flag as a cpstring.
This works with all types of flags.
This is how you should get a string flag.
- <code>**getInt**(name cpstring) int </code> To get the content of a flag as an int.
The requested flag must be of type int.
- <code>**getFloat**(name cpstring) float </code> To get the content of a flag as a float.
The requested flag must be of type float.
- <code>**isSet**(name cpstring) int </code> Returns 1 if a flag has been set by the user.
This is how you should check for a bool flag.
- <code>**parse**(args []cpstring) </code> This will parse the flags with the specified arguments.
The arguments specified should be the arguments passed in your declaration of main, of type []cpstring.


## Example
```bah
&#35;include "iostream.bah"
&#35;include "flags.bah"
 main(args []cpstring) {
     flags = flags{}
     flags.addString("name", "Your name")
     flags.parse(args)
     if flags.isSet("name") == 0 {
         flags.invalidate()
     }
     print("Your name is: ")
     name = flags.get("name")
     println(name)
 }
```