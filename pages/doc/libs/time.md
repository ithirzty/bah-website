# time


### time (struct)
This is a wrapper that makes time manipulations easier.
By default, its .timestamp field is set to the current time.
__Its methods are:__
- <code>**now**() </code> To set the timestamp to the current time.
- <code>**format**(a cpstring) cpstring </code> To format the timestamp using the specified format.
The format options can be found [here](https://koor.fr/C/ctime/strftime.wp).
- <code>**since**() int </code> To get the number of seconds since the timestamp.


## Example
```bah
 &#35;include "iostream.bah"
 &#35;include "time.bah"
 main() {
 ts = time{}
 ts.now()
 formattedTime = ts.format("hou:min:sec")
 println(formattedTime)
 }
```