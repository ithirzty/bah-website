# json


### JSON_TYPE_STRING (const)


### JSON_TYPE_INT (const)


### JSON_TYPE_FLOAT (const)


### JSON_TYPE_ARRAY (const)


### JSON_TYPE_MAP (const)


### jsonElement (struct)
A single element of a json document.
This can be a map, an array, an int, a float or a string.
If the element is of type array (or map), all of its children will be contained in an array, the .children field.
__Its methods are:__
- <code>**map**(key cpstring) jsonElement&ast; </code> If the current element is of type map, this method is used to get a children element mapped to this key.
- <code>**str**() cpstring </code> To get the current element as a cpstring no matter its type.


### parseJson (func)
<code>parseJson(a cpstring) jsonElement&ast; </code>
To parse a json document.
This will return a pointer to the main element.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "json.bah"
 main() {
 unparsed = "[54, {\"key\":[0,1]}, \"element\"]"
 json = parseJson(unparsed)
 fiftyfor = json.children[0]
 println(fiftyfor.content)
 jsonMap = json.children[1]
 jsonArray = jsonMap.map("key")
 println(jsonArray.content)
 }
```