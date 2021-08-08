## flags


### Functions/Structure/Types


##### flags (structure)
A wrapper for setting up flags.<br>Its methods are:
- <code>addString(name cpstring, help cpstring)</code> to add a flag of type string (<code>./program -myFlag "myValue"</code>)
- <code>addBool(name cpstring, help cpstring)</code> to add a flag of type bool (<code>./program -myFlag</code>)
- <code>addInt(name cpstring, help cpstring)</code> to add a flag of type int (<code>./program -myFlag "myValue"</code>)
- <code>addFloat(name cpstring, help cpstring)</code> to add a flag of type float (<code>./program -myFlag "myValue"</code>)
- <code>invalidate()</code> to invoke the help menu and exit the program
- <code>get(name cpstring) cpstring</code> to get the content of a flag as a cpstring
- <code>getInt(name cpstring) int</code> to get the content of a flag as an int
- <code>getFloat(name cpstring) float</code> to get the content of a flag as an int
- <code>isSet(name cpstring)</code> to get weither or not a flag has been set by the user
- <code>pare(args []cpstring)</code> to parse the args of a given program's arguments


#### Example
<code>
#include "iostream.bah"
#include "flags.bah"

main(args []cpstring) {
    flags = flags{}
    flags.addString("name", "Enter your name")
    flags.parse()

    if flags.isSet("name") == 0 {
        panic("Must enter your name")
    }

    name = flags.isSet("name")
    print("Your name is: ")
    println(name)

}
</code>



