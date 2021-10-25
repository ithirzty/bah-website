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
- <code>**scan**(e reflectElement) </code> Used for scanning the JSON element in a var.


### parseJson (func)
<code>parseJson(s cpstring) jsonElement&ast; </code>
To parse a json document.
This will return a pointer to the main element.


### toJson (func)
<code>toJson(e reflectElement) cpstring </code>
Converting a var into json.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "json.bah"
 struct user {
     name: cpstring
     id: int
     avatar: cpstring
     password: cpstring
 }
 struct post {
     title: cpstring
     content: cpstring
     author: user
     score: float
     identified: []int
 }
 main(args []cpstring) int {
     //Our JSON test string
     doc = "
     {
         \"title\": \"Test\",
         \"content\": \"This is a test post\",
         \"author\": {
             \"name\": \"Alois\",
             \"id\": 543,
             \"avatar\": \"cdn.example.com/avatar.jpeg\",
         },
         \"identified\": [324, 456, 875],
         \"score\": 43.65
     }"
     //parsing out test string
     root = parseJson(doc)
     //sacanning it to the post1 structure
     post1 = new post
     root.scan(post1)
     //converting our post1 structure into json
     postStr = toJson(post1)
     //parsing the json of out test1 structure
     post2Json = parseJson(postStr)
     //scanning it to our post2 structure
     post2 = new post
     post2Json.scan(post2)
     //converting our post2 structure into json and printting it
     println(toJson(post2))
     //fetching post title
     titleElem = root.map("title")
     //printing the title
     println("The post is titled: "+titleElem.content)
     return 0
 }
```