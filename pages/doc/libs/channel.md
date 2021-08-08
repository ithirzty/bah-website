# channel


### channel (struct)
Wrapper for a channel.
A channel is a queue that is thread safe. It can be safely used between different threads.
The length of the channel can be capped thanks to the **.cap** field.
**The channel will need to be destroyed after its utilization.**
*Note: a queue/channel can only take pointers.*
__Its methods are:__
- <code>**send**(data ptr) </code> To send data to the channel.
This can only send pointers.
- <code>**receive**() ptr </code> To receive data (a pointer) from the channel.
Note that this is a blockant operation.
If no data is available the function will pause the execution of the current thread.
- <code>**destroy**() </code> To destroy a channel after using it. Not destroying it could result in memory leaks.
- <code>**len**() int </code> To get the length of the current channel.
Returns the number of pointers stored inside the channel.


### channel (func)
<code>channel() channel </code>
To initiate a channel
*Do not use channel{}, this will not initiate the mutex and the queue.*


## Example
<code></code>