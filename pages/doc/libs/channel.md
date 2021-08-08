## channel.bah


### Functions/Structure/Types


##### channel() (function)
Used for making and initiating a channel as: <code>channel() channel</code>


##### channel (struct)
A thread safe queue.<br>*Its queue can only contain pointers.*<br>Its methods are:
- <code>send(data ptr)</code> to send data in the channel
- <code>receive()ptr</code> to receive data from the channel
- <code>len() int</code> to get the current channel length (how many elements in queue)
- <code>destroy()</code> to destroy the current channel. *For memory management purposes, it is needed to destroy a channel when it is no longer in use*.


Its fields:
- <code>cap int</code> the maximum number of elements that can be contained inside the channel<br>Must be set after the call to <code>channel()</code>. Set to -1 for no limit.


#### Example
<code>
#include "iostream.bah"
#include "string.bah"
#include "thread.bah"
#include "channel.bah"

c channel

test() {
    for 1 {
        c.send("test")
        sleep(1)
    }
}

main(){

    c = channel()

    t = thread{}
    t.handle = &test
    t.create()

    for 1 {
    s = c.receive()

    println(<cpstring>s)
    }

    c.destroy()

}
</code>