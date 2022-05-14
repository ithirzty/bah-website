# http


### http_url (struct)


### parseUrl (func)
<code>parseUrl(cps cpstring) http_url&ast; {   </code>
Used for parsing an URL.


### urlDecode (func)
<code>urlDecode(encoded cpstring) cpstring </code>
Used for decoding an url encoded string.


### closeSocket (func)
<code>closeSocket(sockfd int) </code>
Used for closing a socket.


### HTTP_SERVER_NO_ERROR (const)


### HTTP_SERVER_SOCKET_ERROR (const)


### HTTP_SERVER_BIND_ERROR (const)


### HTTP_SERVER_LISTEN_ERROR (const)


### http_server (struct)
A wrapper for a http web server.
__Its methods are:__
- <code>**stop**() </code> To stop the server.
- <code>**listenAndServe**() </code> To start the server.


### HTTP_OK (const)
HTTP code 200 means everything is ok


### HTTP_NOT_FOUND (const)
HTTP code 404 means file not found


### HTTP_FORBIDDEN (const)
HTTP code 400 means that you deny access to this request


### HTTP_ERROR (const)
HTTP code 500 means that the server encountered an internal error


### HTTP_REDIRECT (const)
HTTP code 301 means a permanent redirection


### HTTP_PARTIAL_CONTENT (const)
HTTP code 206 means content can be seeked up in a range


### http_transport (struct)
__Its methods are:__
- <code>**setHeader**(name cpstring, value cpstring) </code> To set a header by name.
- <code>**getHeader**(name cpstring) cpstring </code> To get the value of a header by name.
- <code>**write**(content cpstring) </code> To append to the body of the response.


### openSocket (func)
<code>openSocket(host cpstring, port int) int </code>


### http_response (struct)
A wrapper for HTTP responses. You will be able to set/retreive the headers sent/receive.
You will encounter this when doing a request or sending a response to the client.
__Its methods are:__
- <code>**send**() </code> Send the response.
*Use it only when sending response to the client from a http_server*.


### makeRespFromBody (func)
<code>makeRespFromBody(response string) http_response&ast; </code>


### makeRawHttpsRequest (func)
<code>makeRawHttpsRequest(host cpstring, message cpstring) cpstring </code>
Used for making TLS requests.
*This is an internal function, you should know what you're doing if you decide to use it.*


### http_request (struct)
A wrapper for requests.
When receiving a connection, you will be able to retreive the passed headers, path... from the client.
__Its methods are:__
- <code>**send**() http_response&ast; </code>
- <code>**parseForm**() bool </code> Call this to parse the post data form.
This will return false if anything goes wrong while parsing the form.
- <code>**getFormValue**(name cpstring) cpstring </code> Used for getting the value of a form's input.
- <code>**getCookie**(name cpstring) cpstring </code> Used for getting the value of a cookie.


### makeRawRequest (func)
<code>makeRawRequest(method cpstring, u http_url&ast;, args []cpstring) http_response </code>
Used for making any request.
Method is either http or https. The arguments (args) are the variables to pass (can be post or get variable) formatted as: name=value.


### get (func)
<code>get(url cpstring) http_response </code>
Used for making simple get request.


### post (func)
<code>post(url cpstring, args []cpstring) http_response </code>
Used for making simple post request with variables (args) formatted as name=value.


### isPortAvailable (func)
<code>isPortAvailable(port int) int </code>
Checks if a port is available.
*Note: this command is very slow.*


## Example
```bah
 &num;include "http.bah"


 server(serv http_server&ast;, connfd int) {

     request = http_request(connfd)
     response = http_response(connfd)

     response.setHeader("Content&minus;Type", "text/html")

     response.write("Current path:")
     response.write(request.path)

     response.write("\nIt works!")
     response.send()

 }

 main() {
  
     s = http_server{}
     s.port = 8080
     s.handle = server
     s.listenAndServe()

 }
```