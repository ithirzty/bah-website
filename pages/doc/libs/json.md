## json


### Functions/Structure/Types


###### JSON_TYPE_STRING int (const)
Type of a json element as cpstring.


###### JSON_TYPE_INT int (const)
Type of a json element as an int.


###### JSON_TYPE_FLOAT int (const)
Type of a json element as a float.


###### JSON_TYPE_ARRAY int (const)
Type of a json element as a json array. *Use jsonElem.children[index] to get the element of an array by index*.


###### JSON_TYPE_MAP int (const)
Type of a json element as a json map. *Use jsonElem.map("index") to get the element of a map.*


##### parseJson (function)
Used for parsing json and returning json elements as: <code>parseJson(document cpstring) jsonElement&ast; </code>


##### jsonElement (struct)
A single json element.<br>Its methods are:
- <code>map(key cpstring) jsonElem&ast;</code> to get the element of a json array


Its fields are:
- <code>type int</code> the type of the element
- <code>content cpstring</code> the content of the element
- <code>children []jsonElement&ast;</code> every children of the element (weither it is an array or a map)
 

#### Example
<code>
#include "iostream.bah"
#include "json.bah"

main() {
    unparsed = "[54, {\"key\":[0,1]}, \"element\"]"
    json = parseJson(unparsed)
    fiftyfor = json.children[0]
    println(fiftyfor.content)
    jsonMap = json.children[1]
    jsonArray = jsonMap.map("key")
    println(jsonArray.content)
}

</code>