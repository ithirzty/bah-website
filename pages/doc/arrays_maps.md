<section>
# Arrays and maps
Arrays and maps are two very simillar types. They are both lists.
Arrays are ordered and have an int as index and can be very fast to iterate over.
Maps are unordered, have a cpstring as index and are slow to iterate over but can be very fast accessing by key.

Arrays start at index 0. 

- [Declaration](#declaration),
- [Value](#value).

<span id="declaration"></span>
## Declaration
Every element inside an array or a maps are the same type. Their type is defined by the type of the array/maps.

To declare an array, use **[]** followed by the type name and optional values inside braces separated by comas.
```bah
<var>myArray</var> = <type>[]cpstring</type>
```
And with values:
```bah
<var>myArray</var> = <type>[]cpstring</type>{
    <str>"I'm index 0"</str>,
    <str>"I'm index 1"</str>,
    <str>"I'm the last one!"</str>
}
```

Maps are declared as:
```bah
<var>myMap</var> = <kw>map</kw> <type>int</type>
```

The type of an array is **[]type** and the type of a map is: **map:type**.

<span id="value"></span>
## Value
Accessing the value of a map/array can be done using the variable followed by the index/key inside brackets:
```bah
<comment>//setting the first value of myArr</comment>
<var>myArray</var>[<val>0</val>] = <str>"This is the first value"</str>
<comment>//getting the second value of myArr</comment>
<var>myStr</var> = <var>myArray</var>[<val>2</val>]

<comment>//setting key "a" of myMap</comment>
<var>myMap</var>[<str>"a"</str>] = <val>43.5</val>
<comment>//getting key "a" of myMap</comment>
<var>myFloat</var> = <var>myMap</var>[<str>"a"</str>]
```

### Appending
Maps and array have dynamic length.

To append to an array, simply set its value at the index equal to its length.
```nope
        length
          |
          v
[0, 1, 2] 3
       ^
       |
   last index

```
**Note:** the length on an array can accessed using **len(myArr)**.

Following this logic, appending to an array goes as follows:
```bah
<var>myArray</var>[<func>len</func>(<var>myArray</var>)] = <str>"I'm at index length-1 (3-1 = 2)"</str>
```

### Example
```bah
<button class="btn coder run">Run</button>

<hash>#import</hash> <str>"iostream.bah"</str>

<func>main</func>(<var>args</var> <type>[]cpstring</type>) <type>int</type> {
    <var>myArray</var> = <type>[]cpstring</type>{
        <str>"I'm index 0"</str>,
        <str>"I'm index 1"</str>,
        <str>"I'm the last one!"</str>
    }

    <var>myArray</var>[<func>len</func>(<var>myArray</var>)-<val>1</val>] = <str>"I was the last one at index 2"</str>
    <var>myArray</var>[<func>len</func>(<var>myArray</var>)] = <str>"I'm at index length (3)"</str>

    <comment>//What will be printed?</comment>
    <var>i</var>=<val>0</val>; <kw>for</kw> <var>i</var> < <func>len</func>(<var>myArray</var>), <var>i</var>++ {
        <func>println</func>(<var>myArray</var>[<var>i</var>])
    }

    <var>myMap</var> = <kw>map</kw> <type>int</type>

    <comment>//setting key "a" of myMap</comment>
    <var>myMap</var>[<str>"a"</str>] = <val>43</val>

    <kw>return</kw> <val>0</val>
}
```


</section>