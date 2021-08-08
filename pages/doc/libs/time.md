## time.bah


### Functions/Structure/Types


##### time (struct)
A wrapper to make handling timestamps easier.<br>Its methods are:
- <code>now()</code> to set its timestamp to the current one
- <code>format(format cpstring) cpstring</code> to format the timestamp following the specified format (yea-day-mon hou:min:sec)
- <code>since() int</code> to calculate how many seconds have past since the timestamp

Its fields are:
- <code>timestamp</code> the timestamp to use for calculations/formatting


#### Example
<code>
#include "iostream.bah"
#include "time.bah"

main() {
    ts = time{}
    ts.now()

    formattedTime = ts.format("hou:min:sec")
    println(formattedTime)
}
</code>