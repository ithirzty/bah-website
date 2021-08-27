# time


### time (struct)
This is a wrapper that makes time manipulations easier.
By default, its .timestamp field is set to the current time.
__Its methods are:__
- <code>**now**() </code> To set the timestamp to the current time.
- <code>**format**(a cpstring) cpstring </code> To format the timestamp using the specified format.
The format options can be found [here](https://koor.fr/C/ctime/strftime.wp).
- <code>**since**() int </code> To get the number of seconds since the timestamp.


### getTimeUnix (func)
<code>getTimeUnix() int </code>
Returns the current timestamp in nanoseconds.
One nano second looks like this: 0000000000000000001.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "time.bah"
 main() {
 ts = time{}
 ts.now()
 formattedTime = ts.format("hou:min:sec")
 println(formattedTime)
 }
```