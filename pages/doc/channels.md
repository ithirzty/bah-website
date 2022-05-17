<section>
# Channels
A channel is a thread safe data type that is used for sending and receiving values.
When a thread want to receive a value, if there is no value available, it will wait until there is one.
Channels are ordered.
The type of a channel is **chan:type**.

- [Declaration](#declaration),
- [sending](#sending),
- [receiving](#receinving).

<span id="declaration"></span>
## Declaration
To declare a channel:
```bah
<var>myChan</var> = <kw>chan</kw> <type>cpstring</type>
```

<span id="sending"></span>
## Sending
To send to a channel:
```bah
<str>"Hi!"</str> -> <var>myChan</var>
```

<span id="receiving"></span>
## Receiving
To receiving from a channel:
```bah
<var>myStr</var> = <- <var>myChan</var>
```

### Example
```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> <str>"iostream.bah"</str>

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {

    <var>myChan</var> = <kw>chan</kw> <type>cpstring</type>
    <str>"Hi!"</str> -> <var>myChan</var>
    <func>println</func>(<-<var>myChan</var>) <comment>//Should print "Hi!"</comment>

    <kw>return</kw> <val>0</val>
}
```


</section>