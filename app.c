//COMPILE WITH: 'gcc ././app.c -w  -lgc -DPARALLEL_MARK -lm -lssl -lcrypto -lpthread -g'

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <gc.h>

#define noCheck(v) v
#define array(type)	struct{	type *data; long int length; long int elemSize; }

void __CRASH_BAH_HANDLE(int sig) {
void *array[10];
size_t size;
size = backtrace(array, 10);
char * sigStr = "unknown";
if (sig == 11) {
    sigStr = "Seg fault";
};
fprintf(stderr, "Program crashed, received signal %s:\n", sigStr);
backtrace_symbols_fd(array, size, STDERR_FILENO);
exit(1);
}


int main(int argc, char ** argv) {
GC_INIT();
array(char*) * args = GC_MALLOC(sizeof(array(char*)));
args->data = GC_MALLOC(sizeof(char*)*argc);
memcpy(args->data, argv, sizeof(char*)*argc);
args->elemSize = sizeof(char*);
args->length = argc;
signal(SIGSEGV, __CRASH_BAH_HANDLE);
__BAH__main(args);
};
#define main(v) __BAH__main(v)
#include <signal.h>
#include <string.h>
#include <gc.h>
#include <sys/mman.h>
#define SIZE_OF_INT 8
#define SIZE_OF_CHAR 1
#define SIZE_OF_INT32 4
#define SIZE_OF_FLOAT32 4
#define SIZE_OF_FLOAT 8
long int len(void * a){
long int i =  0;
;
noCheck( array ( void* ) *arr = a );
noCheck( i = arr -> length );
return i;
};
void * memoryAlloc(long int s){
void * p =  GC_MALLOC(s);
;
return p;
};
void destroy(void * a){
GC_FREE(a);
};
void clear(void * a){
noCheck( array ( void* ) *arr = a );
noCheck( destroy ( arr -> data ) );
noCheck( arr -> data = memoryAlloc ( sizeof ( 0 ) ) );
noCheck( arr -> length = 0 );
};
void append(void * a,void * b){
noCheck( array ( void* ) *arrA = a );
noCheck( array ( void* ) *arrB = b );
long int lenA =  0;
;
long int lenB =  0;
;
long int realSizeA =  0;
;
long int realSizeB =  0;
;
noCheck( lenA = len ( arrA ) );
noCheck( lenB = len ( arrB ) );
if ((lenB==0)) {
return ;
}
if ((lenA==0)) {
noCheck( arrA -> data = arrB -> data );
noCheck( arrA -> length = arrB -> length );
return ;
}
noCheck( realSizeA = lenA * arrA -> elemSize );
noCheck( realSizeB = lenB * arrB -> elemSize );
void * buff =  memoryAlloc(realSizeA + realSizeB + 32);
;
noCheck( memcpy ( buff , arrA -> data , realSizeA ) );
noCheck( memcpy ( buff + lenA , arrB -> data , realSizeB ) );
noCheck( arrA -> length = lenA + lenB );
noCheck( arrA -> data = buff );
};
void copy(void * a,void * b){
noCheck( array ( void* ) *arrA = a );
noCheck( array ( void* ) *arrB = b );
long int lenB =  0;
;
long int realSizeB =  0;
;
noCheck( lenB = len ( arrB ) );
noCheck( realSizeB = lenB * arrB -> elemSize );
noCheck( arrA -> data = memoryAlloc ( realSizeB ) );
noCheck( memcpy ( arrA -> data , arrB -> data , realSizeB ) );
noCheck( arrA -> length = arrB -> length );
};
void * memoryRealloc(void * p,long int s){
void * np =  GC_REALLOC(p,s);
;
return np;
};
#define PROT_READ 1
#define PROT_WRITE 2
#define MAP_SHARED 1
#define MAP_ANONYMOUS 2
void * sharedMemory(long int size){
if ((size==0)) {
size =  4096;
;
}
void * r =  mmap(0,size,PROT_READ + PROT_WRITE,MAP_SHARED + MAP_ANONYMOUS,-1,0);
;
return r;
};
char * concatCPSTRING(char * a,char * b){
long int lenA =  strlen(a);
;
long int lenB =  strlen(b);
;
char * r =  memoryAlloc(lenA + lenB + 1);
;
strncpy(r,a,lenA);
strcat(r,b);
return r;
};
char * __STR(char * a){
long int lenA =  strlen(a);
;
char * r =  memoryAlloc(lenA + 1);
;
strncpy(r,a,lenA);
return r;
};
#define null (void *)0
#define true (int)1
#define false (int)0
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
char * charToString(char c){
char * s =  memoryAlloc(2);
;
strncpy(s,(char *)&c,1);
return s;
};
long int isUpper(char c){
if ((c>(char)64)) {
if ((c<(char)91)) {
return 1;
}
}
return 0;
};
long int isLower(char c){
if ((c>(char)96)) {
if ((c<(char)123)) {
return 1;
}
}
return 0;
};
long int isLetter(char s){
if (isUpper(s)) {
return 1;
}
if (isLower(s)) {
return 1;
}
return 0;
};
long int isNumber(char c){
if ((c>(char)47)) {
if ((c<(char)58)) {
return 1;
}
}
return 0;
};
long int isAlphaNumeric(char s){
if (isLetter(s)) {
return 1;
}
if (isNumber(s)) {
return 1;
}
return 0;
};
long int isSpace(char c){
if ((c==(char)32)) {
return 1;
}
if ((c==(char)9)) {
return 1;
}
if ((c==(char)10)) {
return 1;
}
if ((c==(char)11)) {
return 1;
}
if ((c==(char)13)) {
return 1;
}
return 0;
};
struct string {
char * content;
long int length;
void(*set)(struct string* this,char * s);
void(*append)(struct string* this,char * s);
void(*prepend)(struct string* this,char * s);
char(*charAt)(struct string* this,long int i);
long int(*compare)(struct string* this,char * s);
char *(*str)(struct string* this);
void(*replace)(struct string* this,char * nd,char * rl);
long int(*count)(struct string* this,char * need);
long int(*hasPrefix)(struct string* this,char * need);
long int(*hasSuffix)(struct string* this,char * need);
void(*trim)(struct string* this);
void(*trimLeft)(struct string* this,long int s);
void(*trimRight)(struct string* this,long int s);
};
void string__set(struct string* this,char * s){
this->length =  strlen(s);
;
this->content =  (char *)memoryAlloc(this->length + 1);
;
strcpy(this->content,s);
};
void string__append(struct string* this,char * s){
this->length =  this->length + strlen(s);
;
char * tmpS =  (char *)memoryRealloc((void *)this->content,this->length);
;
if (((long int)tmpS==0)) {
tmpS =  (char *)memoryAlloc(this->length);
;
strncpy(tmpS,this->content,this->length);
}
strcat(tmpS,s);
this->content =  tmpS;
;
};
void string__prepend(struct string* this,char * s){
char * tmpS =  memoryAlloc(this->length + 1);
;
strcpy(tmpS,this->content);
this->length =  this->length + strlen(s);
;
this->content =  (char *)memoryAlloc(this->length + 1);
;
strcpy(this->content,s);
strcat(this->content,tmpS);
};
char string__charAt(struct string* this,long int i){
char c =  (char)0;
;
if ((i<this->length)) {
noCheck( c = this -> content [ i ] );
return c;
}
return c;
};
long int string__compare(struct string* this,char * s){
long int r =  strcmp(this->content,s);
;
if ((r==0)) {
return 1;
}
return 0;
};
char * string__str(struct string* this){
char * r =  this->content;
;
return r;
};
void string__replace(struct string* this,char * nd,char * rl){
struct string needle =  {};
;
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.set(&needle,nd);
struct string repl =  {};
;
repl.set = string__set;
repl.append = string__append;
repl.prepend = string__prepend;
repl.charAt = string__charAt;
repl.compare = string__compare;
repl.str = string__str;
repl.set(&repl,rl);
long int i =  0;
;
long int si =  0;
;
array(char)* replcBuff = memoryAlloc(sizeof(array(char)));;

replcBuff->length = 0;
replcBuff->elemSize = sizeof(char);
array(char)* buff = memoryAlloc(sizeof(array(char)));;

buff->length = 0;
buff->elemSize = sizeof(char);
while ((i<this->length)) {
char c =  this->charAt(this,i);
;
char rc =  needle.charAt(&needle,si);
;
if ((c==rc)) {
si =  si + 1;
;

{
long nLength = len(replcBuff);
if (replcBuff->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(replcBuff->data, (nLength+50)*sizeof(char));
replcBuff->data = newPtr;
}
replcBuff->data[len(replcBuff)] =  c;

replcBuff->length = nLength+1;
} else {
replcBuff->data[len(replcBuff)] =  c;

};
};
;
}
else {
if ((len(replcBuff)>0)) {
si =  0;
;
append(buff,replcBuff);
clear(replcBuff);
}

{
long nLength = len(buff);
if (buff->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(buff->data, (nLength+50)*sizeof(char));
buff->data = newPtr;
}
buff->data[len(buff)] =  c;

buff->length = nLength+1;
} else {
buff->data[len(buff)] =  c;

};
};
;
}
if ((si==needle.length)) {
clear(replcBuff);
long int ii =  0;
;
while ((ii<repl.length)) {
long int a =  ii;
;

{
long nLength = len(buff);
if (buff->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(buff->data, (nLength+50)*sizeof(char));
buff->data = newPtr;
}
buff->data[len(buff)] =  repl.charAt(&repl,ii);

buff->length = nLength+1;
} else {
buff->data[len(buff)] =  repl.charAt(&repl,ii);

};
};
;
ii =  ii + 1;
;
};
si =  0;
;
}
i =  i + 1;
;
};
char * r =  "";
;
noCheck( r = buff -> data );
if ((len(replcBuff)>0)) {
char * replbuffStr;
noCheck( replbuffStr = replcBuff -> data );
r =  concatCPSTRING(r,replbuffStr);
;
}
this->set(this,r);
};
long int string__count(struct string* this,char * need){
long int i =  0;
;
long int count =  0;
;
struct string needle =  {};
;
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.replace = string__replace;
needle.set(&needle,need);
long int countIndex =  0;
;
while ((i<this->length)) {
char c =  this->charAt(this,i);
;
char sc =  needle.charAt(&needle,countIndex);
;
if ((c==sc)) {
countIndex =  countIndex + 1;
;
}
else {
countIndex =  0;
;
}
if ((countIndex==needle.length)) {
count =  count + 1;
;
countIndex =  0;
;
}
i =  i + 1;
;
};
return count;
};
long int string__hasPrefix(struct string* this,char * need){
long int i =  0;
;
struct string needle =  {};
;
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.replace = string__replace;
needle.count = string__count;
needle.set(&needle,need);
if ((this->length<needle.length)) {
return 0;
}
while ((i<needle.length)) {
char c =  this->charAt(this,i);
;
char sc =  needle.charAt(&needle,i);
;
if ((c!=sc)) {
return 0;
}
i =  i + 1;
;
};
return 1;
};
long int string__hasSuffix(struct string* this,char * need){
struct string needle =  {};
;
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.replace = string__replace;
needle.count = string__count;
needle.hasPrefix = string__hasPrefix;
needle.set(&needle,need);
if ((this->length<needle.length)) {
return 0;
}
long int i =  this->length - needle.length;
;
long int needleIndex =  0;
;
while ((i<this->length)) {
char c =  this->charAt(this,i);
;
char sc =  needle.charAt(&needle,needleIndex);
;
if ((c!=sc)) {
return 0;
}
needleIndex =  needleIndex + 1;
;
i =  i + 1;
;
};
return 1;
};
void string__trim(struct string* this){
if ((this->length==0)) {
return ;
}
char fc =  this->charAt(this,0);
;
if ((isSpace(fc)==0)) {
return ;
}
long int i =  0;
;
while ((i<this->length)) {
char c =  this->charAt(this,i);
;
if ((isSpace(c)==0)) {
break;
}
i =  i + 1;
;
};
if ((i>0)) {
this->length =  this->length - i;
;
char * tmpS =  memoryAlloc(this->length + 1);
;
memcpy(tmpS,noCheck( this->content + i ),this->length + 1);
this->content =  tmpS;
;
}
};
void string__trimLeft(struct string* this,long int s){
long int nSize =  this->length - s;
;
void * tmpS =  memoryAlloc(nSize);
;
memcpy(tmpS,noCheck( this->content + s ),nSize);
this->content =  tmpS;
;
this->length =  nSize;
;
};
void string__trimRight(struct string* this,long int s){
long int nSize =  this->length - s;
;
void * tmpS =  memoryAlloc(nSize);
;
memcpy(tmpS,this->content,nSize);
this->content =  tmpS;
;
this->length =  nSize;
;
};
struct string string(char * s){
struct string a =  {};
;
a.set = string__set;
a.append = string__append;
a.prepend = string__prepend;
a.charAt = string__charAt;
a.compare = string__compare;
a.str = string__str;
a.replace = string__replace;
a.count = string__count;
a.hasPrefix = string__hasPrefix;
a.hasSuffix = string__hasSuffix;
a.trim = string__trim;
a.trimLeft = string__trimLeft;
a.trimRight = string__trimRight;
a.content =  (char *)0;
;
a.length =  0;
;
a.set(&a,s);
return a;
};
typedef array(char)* __BAH_ARR_TYPE_char;
char * arrToStr(__BAH_ARR_TYPE_char arr){
long int strLen =  len(arr);
;
char * str =  memoryAlloc(strLen + 1);
;
noCheck( memcpy ( str , arr -> data , strLen ) );
return str;
};
__BAH_ARR_TYPE_char strToArr(char * str){
long int strLen =  strlen(str);
;
array(char)* arr = memoryAlloc(sizeof(array(char)));;

arr->length = 0;
arr->elemSize = sizeof(char);
noCheck( arr -> data = memoryAlloc ( strLen + 1 ) );
noCheck( memcpy ( arr -> data , str , strLen ) );
noCheck( arr -> length = strLen );
return arr;
};
char * arrAsStr(__BAH_ARR_TYPE_char arr){
char * r =  "";
;
noCheck( r = arr -> data );
return r;
};
struct string intToString(long int i){
char * buff =  memoryAlloc(65);
;
void * ptri =  (void *)i;
;
sprintf(buff,"%d",ptri);
struct string r =  string(buff);
;
return r;
};
char * intToStr(long int i){
char * buff =  memoryAlloc(65);
;
sprintf(buff,"%ld",(void *)i);
return buff;
};
long int stringToInt(struct string s){
long int i =  atoi(s.content);
;
return i;
};
typedef array(struct string)* __BAH_ARR_TYPE_string;
__BAH_ARR_TYPE_string splitString(struct string s,char * sp){
struct string sep =  string(sp);
;
array(struct string)* res = memoryAlloc(sizeof(array(struct string)));;

res->length = 0;
res->elemSize = sizeof(struct string);
struct string sepBuffer =  string("");
;
long int sepIndex =  0;
;
long int i =  0;
;
struct string replcBuff =  string("");
;
array(char)* tmpString = memoryAlloc(sizeof(array(char)));;

tmpString->length = 0;
tmpString->elemSize = sizeof(char);
while ((i<s.length)) {
char c =  s.charAt(&s,i);
;
char sepc =  sep.charAt(&sep,sepIndex);
;
if ((c==sepc)) {
sepIndex =  sepIndex + 1;
;
replcBuff.append(&replcBuff,charToString(c));
}
else {
if ((sepIndex>0)) {
sepIndex =  0;
;
replcBuff.append(&replcBuff,charToString(c));
long int ii =  0;
;
while ((ii<replcBuff.length)) {

{
long nLength = len(tmpString);
if (tmpString->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(tmpString->data, (nLength+50)*sizeof(char));
tmpString->data = newPtr;
}
tmpString->data[len(tmpString)] =  replcBuff.charAt(&replcBuff,ii);

tmpString->length = nLength+1;
} else {
tmpString->data[len(tmpString)] =  replcBuff.charAt(&replcBuff,ii);

};
};
;
ii =  ii + 1;
;
};
replcBuff.set(&replcBuff,"");
}
else {

{
long nLength = len(tmpString);
if (tmpString->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(tmpString->data, (nLength+50)*sizeof(char));
tmpString->data = newPtr;
}
tmpString->data[len(tmpString)] =  c;

tmpString->length = nLength+1;
} else {
tmpString->data[len(tmpString)] =  c;

};
};
;
}
}
if ((sepIndex==sep.length)) {
replcBuff.set(&replcBuff,"");
struct string* elem = memoryAlloc(sizeof(struct string));
;
elem->set = string__set;
elem->append = string__append;
elem->prepend = string__prepend;
elem->charAt = string__charAt;
elem->compare = string__compare;
elem->str = string__str;
elem->replace = string__replace;
elem->count = string__count;
elem->hasPrefix = string__hasPrefix;
elem->hasSuffix = string__hasSuffix;
elem->trim = string__trim;
elem->trimLeft = string__trimLeft;
elem->trimRight = string__trimRight;
elem->set(elem,arrToStr(tmpString));
long int lenRes =  len(res);
;

{
long nLength = lenRes;
if (res->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(res->data, (nLength+50)*sizeof(struct string));
res->data = newPtr;
}
res->data[lenRes] =  *elem;

res->length = nLength+1;
} else {
res->data[lenRes] =  *elem;

};
};
;
clear(tmpString);
sepIndex =  0;
;
}
i =  i + 1;
;
};
if ((replcBuff.length>0)) {
long int ii =  0;
;
while ((ii<replcBuff.length)) {

{
long nLength = len(tmpString);
if (tmpString->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(tmpString->data, (nLength+50)*sizeof(char));
tmpString->data = newPtr;
}
tmpString->data[len(tmpString)] =  replcBuff.charAt(&replcBuff,ii);

tmpString->length = nLength+1;
} else {
tmpString->data[len(tmpString)] =  replcBuff.charAt(&replcBuff,ii);

};
};
;
ii =  ii + 1;
;
};
}
if ((len(tmpString)>0)) {
struct string* elem = memoryAlloc(sizeof(struct string));
;
elem->set = string__set;
elem->append = string__append;
elem->prepend = string__prepend;
elem->charAt = string__charAt;
elem->compare = string__compare;
elem->str = string__str;
elem->replace = string__replace;
elem->count = string__count;
elem->hasPrefix = string__hasPrefix;
elem->hasSuffix = string__hasSuffix;
elem->trim = string__trim;
elem->trimLeft = string__trimLeft;
elem->trimRight = string__trimRight;
elem->set(elem,arrToStr(tmpString));
long int lenRes =  len(res);
;

{
long nLength = lenRes;
if (res->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(res->data, (nLength+50)*sizeof(struct string));
res->data = newPtr;
}
res->data[lenRes] =  *elem;

res->length = nLength+1;
} else {
res->data[lenRes] =  *elem;

};
};
;
}
return res;
};
struct string joinString(__BAH_ARR_TYPE_string a,char * sep){
long int i =  0;
;
struct string s =  string("");
;
long int max =  len(a) - 1;
;
while ((i<len(a))) {
struct string e =  a->data[i];
;
if ((e.length==0)) {
i =  i + 1;
;
continue;
}
struct string tmpS =  string(e.str(&e));
;
if ((i!=max)) {
tmpS.append(&tmpS,sep);
}
s.append(&s,tmpS.str(&tmpS));
i =  i + 1;
;
};
return s;
};
char * splitStringBefore(struct string s,char * sp){
struct string sep =  string(sp);
;
if ((sep.length>=s.length)) {
return "";
}
long int sepIndex =  0;
;
long int foundIndex =  0;
;
long int i =  0;
;
while ((i<s.length)) {
char c =  s.charAt(&s,i);
;
char sc =  sep.charAt(&sep,sepIndex);
;
if ((c==sc)) {
if ((sepIndex==0)) {
foundIndex =  i - 1;
;
}
sepIndex =  sepIndex + 1;
;
if ((sepIndex==sep.length)) {
long int max =  s.length - foundIndex - 1;
;
s.trimRight(&s,max);
return s.str(&s);
}
}
else {
foundIndex =  0;
;
sepIndex =  0;
;
}
i =  i + 1;
;
};
return "";
};
struct string toLower(struct string s){
array(char)* ns = memoryAlloc(sizeof(array(char)));;

ns->length = 0;
ns->elemSize = sizeof(char);
long int i =  0;
;
while ((i<s.length)) {
char c =  s.charAt(&s,i);
;
if (isUpper(c)) {
c =  c + (char)32;
;
}

{
long nLength = len(ns);
if (ns->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(ns->data, (nLength+50)*sizeof(char));
ns->data = newPtr;
}
ns->data[len(ns)] =  c;

ns->length = nLength+1;
} else {
ns->data[len(ns)] =  c;

};
};
;
i =  i + 1;
;
};
return string(arrToStr(ns));
};
char * stdinput(long int len){
char * buff =  memoryAlloc(len);
;
fgets(buff,len,noCheck( stdin ));
return buff;
};
void print(char * s){
write(1,s,strlen(s));
};
void println(char * s){
write(1,s,strlen(s));
write(1,"\n",1);
};
void panic(char * e){
if (strlen(e)) {
println(e);
exit(1);
}
};
struct fileStream {
FILE* handle;
long int(*isValid)(struct fileStream* this);
void(*open)(struct fileStream* this,char * path,char * mode);
void(*close)(struct fileStream* this);
long int(*getSize)(struct fileStream* this);
char *(*readContent)(struct fileStream* this);
void(*rewind)(struct fileStream* this);
char(*getChar)(struct fileStream* this);
void(*createFile)(struct fileStream* this,char * path);
long int(*writeFile)(struct fileStream* this,char * content);
};
long int fileStream__isValid(struct fileStream* this){
if ((this->handle==null)) {
return 0;
}
return 1;
};
void fileStream__open(struct fileStream* this,char * path,char * mode){
this->handle =  fopen(path,mode);
;
};
void fileStream__close(struct fileStream* this){
if ((this->isValid(this)==0)) {
return ;
}
fclose(this->handle);
};
long int fileStream__getSize(struct fileStream* this){
if ((this->isValid(this)==0)) {
return -1;
}
fseek(this->handle,0,2);
long int size =  ftell(this->handle);
;
fclose(this->handle);
return size;
};
char * fileStream__readContent(struct fileStream* this){
if ((this->isValid(this)==0)) {
return "invalid";
}
fseek(this->handle,0,2);
long int size =  ftell(this->handle);
;
rewind(this->handle);
char c =  getc(this->handle);
;
long int i =  0;
;
array(char)* s = memoryAlloc(sizeof(array(char)));;

s->length = 0;
s->elemSize = sizeof(char);
while ((c!=(char)noCheck( EOF ))) {

{
long nLength = len(s);
if (s->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(s->data, (nLength+50)*sizeof(char));
s->data = newPtr;
}
s->data[len(s)] =  c;

s->length = nLength+1;
} else {
s->data[len(s)] =  c;

};
};
;
i =  i + 1;
;
c =  getc(this->handle);
;
};

{
long nLength = len(s);
if (s->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(s->data, (nLength+50)*sizeof(char));
s->data = newPtr;
}
s->data[len(s)] =  (char)0;

s->length = nLength+1;
} else {
s->data[len(s)] =  (char)0;

};
};
;
long int ls =  len(s);
;
char * r =  "";
;
noCheck( r = s -> data );
return r;
};
void fileStream__rewind(struct fileStream* this){
rewind(this->handle);
};
char fileStream__getChar(struct fileStream* this){
char c =  getc(this->handle);
;
return c;
};
void fileStream__createFile(struct fileStream* this,char * path){
this->open(this,path,"w");
this->close(this);
};
long int fileStream__writeFile(struct fileStream* this,char * content){
if ((this->isValid(this)==0)) {
return -1;
}
fputs(content,this->handle);
return 1;
};
struct fileMap {
long int handle;
char *(*open)(struct fileMap* this,char * fileName);
long int(*isValid)(struct fileMap* this);
void(*close)(struct fileMap* this);
};
char * fileMap__open(struct fileMap* this,char * fileName){
this->handle =  open(fileName,noCheck( O_RDWR ),noCheck( S_IRUSR | S_IWUSR ));
;
struct stat sb =  {};
;
fstat(this->handle,&sb);
char * file =  mmap(0,sb.st_size,noCheck( PROT_READ | PROT_WRITE ),noCheck( MAP_SHARED ),this->handle,0);
;
return file;
};
long int fileMap__isValid(struct fileMap* this){
if ((this->handle<0)) {
return 0;
}
return 1;
};
void fileMap__close(struct fileMap* this){
close(this->handle);
};
typedef array(char *)* __BAH_ARR_TYPE_cpstring;
__BAH_ARR_TYPE_cpstring listFiles(char * dir){
array(char *)* files = memoryAlloc(sizeof(array(char *)));;

files->length = 0;
files->elemSize = sizeof(char *);
DIR* d =  opendir(dir);
;
struct dirent* file =  readdir(d);
;
while ((file!=null)) {
long int lf =  len(files);
;
if ((strcmp(file->d_name,".")==0)) {
file =  readdir(d);
;
continue;
}
if ((strcmp(file->d_name,"..")==0)) {
file =  readdir(d);
;
continue;
}

{
long nLength = lf;
if (files->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(files->data, (nLength+50)*sizeof(char *));
files->data = newPtr;
}
files->data[lf] =  file->d_name;

files->length = nLength+1;
} else {
files->data[lf] =  file->d_name;

};
};
;
file =  readdir(d);
;
};
closedir(d);
return files;
};
long int fileExists(char * path){
long int is =  access(path,0);
;
if ((is==0)) {
return 1;
}
return 0;
};
int removeFile(char * name){
if ((remove(name)==0)) {
return true;
}
return false;
};
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
struct command {
char * command;
char *(*run)(struct command* this);
};
char * command__run(struct command* this){
FILE* handle =  popen(this->command,"r");
;
if ((handle==null)) {
return "";
}
char * buff =  memoryAlloc(1025);
;
struct string res =  string("");
;
long int more =  1;
;
while ((more==1)) {
more =  fgets(buff,1024,handle);
;
res.append(&res,buff);
};
pclose(handle);
return res.str(&res);
};
struct command command(char * s){
struct command cmd =  {};
;
cmd.run = command__run;
cmd.command =  s;
;
return cmd;
};
long int exec(char * s,__BAH_ARR_TYPE_cpstring args){
long int r;
array(char *)* nArgs = memoryAlloc(sizeof(array(char *)));;

nArgs->length = 0;
nArgs->elemSize = sizeof(char *);

{
long nLength = 0;
if (nArgs->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(nArgs->data, (nLength+50)*sizeof(char *));
nArgs->data = newPtr;
}
nArgs->data[0] =  s;

nArgs->length = nLength+1;
} else {
nArgs->data[0] =  s;

};
};
;
long int i =  0;
;
while ((i<len(args))) {

{
long nLength = i + 1;
if (nArgs->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(nArgs->data, (nLength+50)*sizeof(char *));
nArgs->data = newPtr;
}
nArgs->data[i + 1] =  args->data[i];

nArgs->length = nLength+1;
} else {
nArgs->data[i + 1] =  args->data[i];

};
};
;
i =  i + 1;
;
};

{
long nLength = i + 2;
if (nArgs->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(nArgs->data, (nLength+50)*sizeof(char *));
nArgs->data = newPtr;
}
nArgs->data[i + 2] =  (char *)0;

nArgs->length = nLength+1;
} else {
nArgs->data[i + 2] =  (char *)0;

};
};
;
noCheck( r = execvp ( s , nArgs -> data ) );
return r;
};
struct http_url {
struct string path;
struct string host;
struct string proto;
};
struct http_url parseUrl(char * cps){
struct http_url* u = memoryAlloc(sizeof(struct http_url));
;
struct string s =  string(cps);
;
long int i =  0;
;
long int max =  s.length - 1;
;
long int hasProto =  0;
;
while ((i<s.length)) {
char c =  s.charAt(&s,i);
;
if ((c==58)) {
hasProto =  1;
;
break;
}
i =  i + 1;
;
};
if ((hasProto==1)) {
struct string proto =  string("");
;
i =  0;
;
while ((s.charAt(&s,i)!=58)) {
char c =  s.charAt(&s,i);
;
proto.append(&proto,charToString(c));
i =  i + 1;
;
};
i =  i + 1;
;
u->proto =  proto;
;
}
else {
u->proto =  string("http");
;
i =  0;
;
}
while ((s.charAt(&s,i)==47)) {
if ((i==max)) {
break;
}
i =  i + 1;
;
};
struct string hn =  string("");
;
while ((s.charAt(&s,i)!=47)) {
char c =  s.charAt(&s,i);
;
hn.append(&hn,charToString(c));
if ((i==max)) {
break;
}
i =  i + 1;
;
};
u->host =  hn;
;
if ((i==max)) {
u->path =  string("/");
;
return *u;
}
struct string path =  string("");
;
while ((i<=max)) {
char c =  s.charAt(&s,i);
;
path.append(&path,charToString(c));
i =  i + 1;
;
};
u->path =  path;
;
return *u;
};
void sigchld_handler(long int signo){
long int status;
long int pid;
pid =  waitpid(-1,&status,1);
;
while ((pid>0)) {
pid =  waitpid(-1,&status,1);
;
};
};
struct http_server {
long int port;
long int running;
long int sockfd;
void (*handle)(struct http_server*,long int);
void(*listenAndServe)(struct http_server* this);
void(*stop)(struct http_server* this);
};
void http_server__listenAndServe(struct http_server* this){
long int port =  this->port;
;
struct sockaddr_in servaddr;
struct sockaddr_in cliaddr;
struct sigaction sa;
long int sockfd =  socket(2,1,0);
;
this->sockfd =  sockfd;
;
if ((sockfd<0)) {
panic("http: error opening socket");
}
servaddr.sin_family =  2;
;
struct in_addr saddr =  {};
;
saddr.s_addr =  htonl(0);
;
servaddr.sin_addr =  saddr;
;
servaddr.sin_port =  htons(port);
;
long int isBind =  bind(sockfd,&servaddr,16);
;
if ((isBind!=0)) {
close(sockfd);
struct string err =  string("http: failed to bind port: ");
;
struct string p =  intToString(port);
;
err.append(&err,p.content);
panic(err.content);
}
long int isListening =  listen(sockfd,1024);
;
if ((isListening<0)) {
close(sockfd);
panic("http: failed to start listening");
}
memset((void *)&sa,0,152);
sa.sa_handler =  sigchld_handler;
;
sigaction(17,&sa,0);
while ((this->running==1)) {
long int clilen =  16;
;
long int connfd =  accept(sockfd,&cliaddr,&clilen);
;
if ((connfd<0)) {
continue;
}
long int childpid =  fork();
;
if ((childpid<0)) {
println("http: failed to fork client handler");
close(connfd);
continue;
}
if ((childpid==0)) {
close(sockfd);
this->handle(this,connfd);
exit(0);
}
close(connfd);
};
close(sockfd);
};
void http_server__stop(struct http_server* this){
if ((this->sockfd==-1)) {
println("cannot stop http_server, not running");
return ;
}
this->running =  0;
;
close(this->sockfd);
};
void http_send(long int connfd,char * s){
send(connfd,s,strlen(s),0);
};
char * http_receive(long int connfd){
char * buffer =  memoryAlloc(1024);
;
recv(connfd,buffer,1024,0);
return buffer;
};
struct http_request {
long int connfd;
char * request;
long int headersIndex;
char * cookies;
char * method;
char * path;
char *(*getHeader)(struct http_request* this,char * name);
};
char * http_request__getHeader(struct http_request* this,char * name){
struct string nameMemory =  string("");
;
struct string valueMemory =  string("");
;
long int isValue =  0;
;
long int found =  0;
;
struct string req =  string(this->request);
;
long int i =  this->headersIndex;
;
while ((i<req.length)) {
char c =  req.charAt(&req,i);
;
if ((found==0)) {
if ((isValue==1)) {
if ((c==(char)10)) {
isValue =  0;
;
}
}
else {
if ((c==58)) {
isValue =  1;
;
if ((strcmp(name,nameMemory.content)==0)) {
found =  1;
;
}
else {
nameMemory.set(&nameMemory,"");
}
}
else {
char * cs =  charToString(c);
;
nameMemory.append(&nameMemory,cs);
}
}
}
else {
if ((c==(char)13)) {
break;
}
char * cs =  charToString(c);
;
valueMemory.append(&valueMemory,cs);
}
i =  i + 1;
;
};
char * r =  valueMemory.str(&valueMemory);
;
return r;
};
struct http_request http_request(long int connfd){
struct http_request r =  {};
;
r.getHeader = http_request__getHeader;
r.connfd =  connfd;
;
char * reqcps =  http_receive(connfd);
;
struct string req =  string(reqcps);
;
long int i =  0;
;
struct string method =  string("");
;
while ((i<req.length)) {
char c =  req.charAt(&req,i);
;
if ((c==32)) {
break;
}
char * cs =  charToString(c);
;
method.append(&method,cs);
i =  i + 1;
;
};
r.method =  method.str(&method);
;
struct string path =  string("");
;
i =  i + 1;
;
while ((i<req.length)) {
char c =  req.charAt(&req,i);
;
if ((c==32)) {
break;
}
char * cs =  charToString(c);
;
path.append(&path,cs);
i =  i + 1;
;
};
r.path =  path.str(&path);
;
while ((i<req.length)) {
char c =  req.charAt(&req,i);
;
i =  i + 1;
;
if ((c==(char)10)) {
break;
}
};
r.headersIndex =  i;
;
r.request =  reqcps;
;
return r;
};
#define HTTP_OK 200
#define HTTP_NOT_FOUND 404
#define HTTP_FORBIDDEN 400
#define HTTP_ERROR 500
#define HTTP_REDIRECT 301
struct http_response {
long int connfd;
array(struct string*)* headers;
long int code;
struct string* body;
void(*send)(struct http_response* this);
void(*setHeader)(struct http_response* this,char * name,char * value);
char *(*getHeader)(struct http_response* this,char * name);
void(*write)(struct http_response* this,char * content);
};
void http_response__send(struct http_response* this){
struct string s =  string("HTTP/1.0 ");
;
if ((this->code==HTTP_OK)) {
s.append(&s,"200 OK");
}
else if ((this->code==HTTP_NOT_FOUND)) {
s.append(&s,"404 Not Found");
}
else if ((this->code==HTTP_FORBIDDEN)) {
s.append(&s,"400 Bad Request");
}
else if ((this->code==HTTP_ERROR)) {
s.append(&s,"500 Internal Server Error");
}
else if ((this->code==HTTP_REDIRECT)) {
s.append(&s,"301 Moved Permanently");
}
else {
s.append(&s,intToStr(this->code));
}
s.append(&s,"\r\n");
long int i =  0;
;
while ((i<len(this->headers))) {
struct string* e =  this->headers->data[i];
;
s.append(&s,e->content);
s.append(&s,"\r\n");
i =  i + 1;
;
};
s.append(&s,"\r\n");
struct string* body =  this->body;
;
s.append(&s,body->content);
http_send(this->connfd,s.content);
};
void http_response__setHeader(struct http_response* this,char * name,char * value){
struct string* h = memoryAlloc(sizeof(struct string));
;
h->set = string__set;
h->append = string__append;
h->prepend = string__prepend;
h->charAt = string__charAt;
h->compare = string__compare;
h->str = string__str;
h->replace = string__replace;
h->count = string__count;
h->hasPrefix = string__hasPrefix;
h->hasSuffix = string__hasSuffix;
h->trim = string__trim;
h->trimLeft = string__trimLeft;
h->trimRight = string__trimRight;
h->set(h,name);
h->append(h,": ");
h->append(h,value);
long int lhs =  len(this->headers);
;

{
long nLength = lhs;
if (this->headers->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(this->headers->data, (nLength+50)*sizeof(struct string*));
this->headers->data = newPtr;
}
this->headers->data[lhs] =  h;

this->headers->length = nLength+1;
} else {
this->headers->data[lhs] =  h;

};
};
;
};
char * http_response__getHeader(struct http_response* this,char * name){
struct string headerName =  string(name);
;
headerName =  toLower(headerName);
;
headerName.append(&headerName,":");
long int i =  0;
;
while ((i<len(this->headers))) {
struct string* currentHeader =  this->headers->data[i];
;
if (currentHeader->hasPrefix(currentHeader,headerName.str(&headerName))) {
struct string header =  string(currentHeader->str(currentHeader));
;
long int space =  0;
;
char c =  header.charAt(&header,headerName.length);
;
if (isSpace(c)) {
space =  1;
;
}
header.trimLeft(&header,headerName.length + space);
return header.str(&header);
}
i =  i + 1;
;
};
return "";
};
void http_response__write(struct http_response* this,char * content){
struct string* body =  this->body;
;
body->append(body,content);
};
struct http_response http_response(long int connfd){
struct http_response resp =  {};
;
resp.headers = memoryAlloc(sizeof(array(struct string*)));
            resp.headers->length = 0;
            resp.headers->elemSize = sizeof(struct string*);
            resp.code = HTTP_OK;
resp.send = http_response__send;
resp.setHeader = http_response__setHeader;
resp.getHeader = http_response__getHeader;
resp.write = http_response__write;
resp.connfd =  connfd;
;
resp.setHeader(&resp,"Server","bah-http-framework");
resp.setHeader(&resp,"Connection","close");
struct string* body = memoryAlloc(sizeof(struct string));
;
body->set = string__set;
body->append = string__append;
body->prepend = string__prepend;
body->charAt = string__charAt;
body->compare = string__compare;
body->str = string__str;
body->replace = string__replace;
body->count = string__count;
body->hasPrefix = string__hasPrefix;
body->hasSuffix = string__hasSuffix;
body->trim = string__trim;
body->trimLeft = string__trimLeft;
body->trimRight = string__trimRight;
body->set(body,"");
resp.body =  body;
;
return resp;
};
char * makeRawHttpsRequest(char * host,char * message){
SSL_library_init();
SSL* ssl;
SSL_CTX* ctx =  SSL_CTX_new(SSLv23_client_method());
;
if ((ctx==null)) {
panic("http: cannot initialize ssl context");
}
BIO* bio =  BIO_new_ssl_connect(ctx);
;
BIO_get_ssl(bio,&ssl);
SSL_set_mode(ssl,4);
BIO_set_conn_hostname(bio,host);
if ((BIO_do_connect(bio)<=0)) {
panic("http: error connecting through ssl");
}
long int success =  BIO_write(bio,message,strlen(message));
;
if ((success<=0)) {
if ((BIO_should_retry(bio)==0)) {
panic("http: failed sending request");
}
}
char * buff =  memoryAlloc(1025);
;
struct string resp =  string("");
;
while ((true==true)) {
memset((void *)buff,0,1025);
long int size =  BIO_read(bio,buff,1025);
;
if ((size<=0)) {
break;
}
resp.append(&resp,buff);
};
BIO_free_all(bio);
SSL_CTX_free(ctx);
return resp.str(&resp);
};
struct http_response makeRawRequest(char * method,struct http_url u,__BAH_ARR_TYPE_cpstring args){
struct string proto =  u.proto;
;
struct string host =  u.host;
;
struct string path =  u.path;
;
struct sockaddr_in serv_addr;
long int portno =  80;
;
struct string response =  string("");
;
struct string message =  string(" ");
;
message.prepend(&message,method);
message.append(&message,path.str(&path));
struct string serialArgs =  string("?");
;
long int largs =  len(args);
;
long int max =  largs - 1;
;
long int i =  0;
;
while ((i<largs)) {
serialArgs.append(&serialArgs,args->data[i]);
if ((i<max)) {
serialArgs.append(&serialArgs,"&");
}
i =  i + 1;
;
};
if ((largs>0)) {
message.append(&message,serialArgs.str(&serialArgs));
}
message.append(&message," HTTP/1.0\r\nHost: ");
if (proto.compare(&proto,"https")) {
host.append(&host,":443");
}
message.append(&message,host.str(&host));
message.append(&message,"\r\nConnection: close\r\n\r\n");
if (proto.compare(&proto,"https")) {
char * resp =  makeRawHttpsRequest(host.str(&host),message.str(&message));
;
response.set(&response,resp);
}
else {
long int sockfd =  socket(2,1,0);
;
if ((sockfd<0)) {
panic("http: error opening socket");
}
struct hostent* server =  gethostbyname(host.content);
;
if ((server==null)) {
panic("http: error resolving host");
}
serv_addr.sin_port =  htons(portno);
;
serv_addr.sin_family =  2;
;
unsigned long int* ha =  server->h_addr;
;
struct in_addr saddr =  {};
;
saddr.s_addr =  *ha;
;
serv_addr.sin_addr =  saddr;
;
long int canConnect =  connect(sockfd,&serv_addr,16);
;
if ((canConnect<0)) {
panic("error: error connecting socket");
}
long int isSend =  send(sockfd,message.content,message.length,0);
;
if ((isSend<=0)) {
panic("http: error sending trought socket");
}
char * buffer =  memoryAlloc(1025);
;
long int nDataLength =  recv(sockfd,buffer,1024,0);
;
while ((nDataLength>0)) {
response.append(&response,buffer);
if ((nDataLength<1024)) {
long int trimAmm =  1024 - nDataLength;
;
response.trimRight(&response,trimAmm);
}
nDataLength =  recv(sockfd,buffer,1024,0);
;
};
close(sockfd);
}
struct http_response resp =  {};
;
resp.headers = memoryAlloc(sizeof(array(struct string*)));
            resp.headers->length = 0;
            resp.headers->elemSize = sizeof(struct string*);
            resp.code = HTTP_OK;
resp.send = http_response__send;
resp.setHeader = http_response__setHeader;
resp.getHeader = http_response__getHeader;
resp.write = http_response__write;
resp.body = memoryAlloc(sizeof(struct string));
;
resp.body->set = string__set;
resp.body->append = string__append;
resp.body->prepend = string__prepend;
resp.body->charAt = string__charAt;
resp.body->compare = string__compare;
resp.body->str = string__str;
resp.body->replace = string__replace;
resp.body->count = string__count;
resp.body->hasPrefix = string__hasPrefix;
resp.body->hasSuffix = string__hasSuffix;
resp.body->trim = string__trim;
resp.body->trimLeft = string__trimLeft;
resp.body->trimRight = string__trimRight;
array(struct string)* lines =  splitString(response,"\r\n");
;
if ((len(lines)==0)) {
return resp;
}
i =  0;
;
struct string head =  lines->data[0];
;
while ((i<head.length)) {
char c =  head.charAt(&head,i);
;
if ((c==32)) {
i =  i + 1;
;
break;
}
i =  i + 1;
;
};
struct string httpCode =  string("");
;
while ((i<head.length)) {
char c =  head.charAt(&head,i);
;
httpCode.append(&httpCode,charToString(c));
if ((c==32)) {
break;
}
i =  i + 1;
;
};
long int httpCodeInt =  stringToInt(httpCode);
;
resp.code =  httpCodeInt;
;
long int isBody =  0;
;
max =  len(lines) - 1;
;
struct string body =  string("");
;
i =  1;
;
while ((i<len(lines))) {
struct string line =  lines->data[i];
;
if ((isBody==1)) {
struct string s =  string(line.str(&line));
;
if ((i<max)) {
s.append(&s,"\r\n");
}
body.append(&body,s.str(&s));
i =  i + 1;
;
continue;
}
if ((i>0)) {
struct string pl =  lines->data[i-1];
;
if ((strlen(pl.str(&pl))==0)) {
isBody =  1;
;
line.trimLeft(&line,2);
continue;
}
}
struct string* header = memoryAlloc(sizeof(struct string));
;
header->set = string__set;
header->append = string__append;
header->prepend = string__prepend;
header->charAt = string__charAt;
header->compare = string__compare;
header->str = string__str;
header->replace = string__replace;
header->count = string__count;
header->hasPrefix = string__hasPrefix;
header->hasSuffix = string__hasSuffix;
header->trim = string__trim;
header->trimLeft = string__trimLeft;
header->trimRight = string__trimRight;
struct string headerName =  string(splitStringBefore(line,":"));
;
if ((headerName.length>0)) {
headerName =  toLower(headerName);
;
line.trimLeft(&line,headerName.length);
line.prepend(&line,headerName.str(&headerName));
}
header->set(header,line.str(&line));
long int lrh =  len(resp.headers);
;

{
long nLength = lrh;
if (resp.headers->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(resp.headers->data, (nLength+50)*sizeof(struct string*));
resp.headers->data = newPtr;
}
resp.headers->data[lrh] =  header;

resp.headers->length = nLength+1;
} else {
resp.headers->data[lrh] =  header;

};
};
;
i =  i + 1;
;
};
char * transferEncoding =  resp.getHeader(&resp,"Transfer-Encoding");
;
if ((strcmp(transferEncoding,"chunked")==0)) {
resp.body->set(resp.body,"");
while ((true==true)) {
char * chunkLen =  splitStringBefore(body,"\r\n");
;
if ((strcmp(chunkLen,"0")==0)) {
break;
}
long int l =  strtol(chunkLen,noCheck( 0 ),16);
;
l =  l;
;
body.trimLeft(&body,strlen(chunkLen) + 2);
char * chunk =  memoryAlloc(l + 1);
;
memcpy(chunk,body.content,l);
resp.body->append(resp.body,chunk);
body.trimLeft(&body,l + 2);
};
}
else {
resp.body->set(resp.body,body.str(&body));
}
return resp;
};
struct http_response get(char * url){
array(char *)* args = memoryAlloc(sizeof(array(char *)));;

args->length = 0;
args->elemSize = sizeof(char *);
struct http_response r =  makeRawRequest("GET",parseUrl(url),args);
;
return r;
};
struct http_response post(char * url,__BAH_ARR_TYPE_cpstring args){
struct http_response r =  makeRawRequest("POST",parseUrl(url),args);
;
return r;
};
long int isPortAvailable(long int port){
struct string cmdS =  intToString(port);
;
cmdS.prepend(&cmdS,"netstat -antu | grep :");
struct command cmd =  command(cmdS.str(&cmdS));
;
char * s =  cmd.run(&cmd);
;
if ((strlen(s)>0)) {
return 0;
}
return 1;
};
#include <stdlib.h>
char * absPath(char * path){
char * z =  (char *)0;
;
char * p =  realpath(path,z);
;
return p;
};
char * getCurrentPath(){
char * cwd =  memoryAlloc(4096);
;
getcwd(cwd,4096);
return cwd;
};
void appendCharArr(__BAH_ARR_TYPE_char a,__BAH_ARR_TYPE_char b){
long int offset =  len(a);
;
long int lenB =  len(b);
;
long int i =  0;
;
while ((i<lenB)) {

{
long nLength = offset + i;
if (a->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(a->data, (nLength+50)*sizeof(char));
a->data = newPtr;
}
a->data[offset + i] =  b->data[i];

a->length = nLength+1;
} else {
a->data[offset + i] =  b->data[i];

};
};
;
i =  i + 1;
;
};
};
struct markdownLine {
struct string* line;
long int type;
struct string rel;
};
struct markdown {
array(struct markdownLine*)* lines;
char *(*str)(struct markdown* this);
char *(*html)(struct markdown* this);
};
char * markdown__str(struct markdown* this){
char * s =  "";
;
long int i =  0;
;
while ((i<len(this->lines))) {
struct markdownLine* mdl =  this->lines->data[i];
;
char * si =  intToStr(i);
;
char * l =  mdl->line->str(mdl->line);
;
s =  concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(s,si),": "),l),"\n");
;
i =  i + 1;
;
};
return s;
};
char * markdown__html(struct markdown* this){
char * html =  "<p>";
;
long int i =  0;
;
while ((i<len(this->lines))) {
struct markdownLine* mdl =  this->lines->data[i];
;
char * l =  mdl->line->str(mdl->line);
;
if ((mdl->type==1)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h1>"),l),"</h1><hr>");
;
}
else if ((mdl->type==2)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h2>"),l),"</h2><hr>");
;
}
else if ((mdl->type==3)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h3>"),l),"</h3>");
;
}
else if ((mdl->type==4)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h4>"),l),"</h4>");
;
}
else if ((mdl->type==5)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h5>"),l),"</h5>");
;
}
else if ((mdl->type==6)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h3>"),l),"</h3>");
;
}
else if ((mdl->type==7)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"&nbsp;• "),l),"<br>");
;
}
else if ((mdl->type==8)) {
html =  concatCPSTRING(concatCPSTRING(html,"\t"),l);
;
}
else if ((mdl->type==9)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<blockquote>"),l),"</blockquote>");
;
}
else if ((mdl->type==10)) {
char * rel =  mdl->rel.str(&mdl->rel);
;
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<pre class=\"highlight highlight-source-"),rel),"\">"),l),"</pre>");
;
}
else {
html =  concatCPSTRING(concatCPSTRING(html,l),"<br>");
;
}
html =  concatCPSTRING(html,"\n");
;
i =  i + 1;
;
};
html =  concatCPSTRING(html,"</p>");
;
return html;
};
struct string parseMarkdownInline(struct string l){
if ((l.length==0)) {
return l;
}
array(char)* nl = memoryAlloc(sizeof(array(char)));;

nl->length = 0;
nl->elemSize = sizeof(char);
long int isBold =  0;
;
long int isItal =  0;
;
long int isUline =  0;
;
long int isImage =  0;
;
long int isLink =  0;
;
array(char)* linkName = memoryAlloc(sizeof(array(char)));;

linkName->length = 0;
linkName->elemSize = sizeof(char);
array(char)* linkUrl = memoryAlloc(sizeof(array(char)));;

linkUrl->length = 0;
linkUrl->elemSize = sizeof(char);
long int i =  0;
;
while ((i<l.length)) {
char c =  l.charAt(&l,i);
;
if ((isLink==1)) {
if ((c==93)) {
isLink =  2;
;
}
else {

{
long nLength = len(linkName);
if (linkName->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(linkName->data, (nLength+50)*sizeof(char));
linkName->data = newPtr;
}
linkName->data[len(linkName)] =  c;

linkName->length = nLength+1;
} else {
linkName->data[len(linkName)] =  c;

};
};
;
}
i =  i + 1;
;
continue;
}
if ((isLink==2)) {
if ((c==40)) {
isLink =  3;
;
}
i =  i + 1;
;
continue;
}
if ((isLink==3)) {
if ((c==41)) {
if ((isImage==1)) {
appendCharArr(nl,strToArr("<img src=\""));
appendCharArr(nl,linkUrl);
appendCharArr(nl,strToArr("\" alt=\""));
appendCharArr(nl,linkName);
appendCharArr(nl,strToArr("\">"));
isImage =  0;
;
}
else {
appendCharArr(nl,strToArr("<a href=\""));
appendCharArr(nl,linkUrl);
appendCharArr(nl,strToArr("\">"));
appendCharArr(nl,linkName);
appendCharArr(nl,strToArr("</a>"));
}
isLink =  0;
;
clear(linkName);
clear(linkUrl);
}
else {

{
long nLength = len(linkUrl);
if (linkUrl->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(linkUrl->data, (nLength+50)*sizeof(char));
linkUrl->data = newPtr;
}
linkUrl->data[len(linkUrl)] =  c;

linkUrl->length = nLength+1;
} else {
linkUrl->data[len(linkUrl)] =  c;

};
};
;
}
i =  i + 1;
;
continue;
}
if ((c==91)) {
long int validateState =  0;
;
long int ii =  i;
;
while ((ii<l.length)) {
char vc =  l.charAt(&l,ii);
;
if ((validateState==0)) {
if ((vc==93)) {
validateState =  1;
;
}
}
else if ((validateState==1)) {
if ((vc==40)) {
validateState =  2;
;
ii =  ii + 1;
;
continue;
}
if ((isSpace(vc)==0)) {
validateState =  0;
;
}
}
else if ((validateState==2)) {
if ((vc==41)) {
validateState =  3;
;
break;
}
}
ii =  ii + 1;
;
};
if ((validateState==3)) {
isLink =  1;
;
i =  i + 1;
;
continue;
}
else if ((isImage==1)) {
isImage =  0;
;

{
long nLength = len(nl);
if (nl->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(nl->data, (nLength+50)*sizeof(char));
nl->data = newPtr;
}
nl->data[len(nl)] =  33;

nl->length = nLength+1;
} else {
nl->data[len(nl)] =  33;

};
};
;
}
}
if ((c==33)) {
char nc =  l.charAt(&l,i + 1);
;
if ((nc==91)) {
isImage =  1;
;
}
i =  i + 1;
;
continue;
}
if ((c==42)) {
if ((l.charAt(&l,i + 1)==42)) {
if ((isBold==1)) {
appendCharArr(nl,strToArr("</strong>"));
isBold =  0;
;
}
else {
appendCharArr(nl,strToArr("<strong>"));
isBold =  1;
;
}
i =  i + 2;
;
continue;
}
else {
if ((isItal==1)) {
appendCharArr(nl,strToArr("</em>"));
isItal =  0;
;
}
else {
appendCharArr(nl,strToArr("<em>"));
isItal =  1;
;
}
i =  i + 1;
;
continue;
}
}
if ((c==95)) {
if ((l.charAt(&l,i + 1)==95)) {
if ((isUline==1)) {
appendCharArr(nl,strToArr("</u>"));
isUline =  0;
;
}
else {
appendCharArr(nl,strToArr("<u>"));
isUline =  1;
;
}
i =  i + 2;
;
continue;
}
}

{
long nLength = len(nl);
if (nl->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(nl->data, (nLength+50)*sizeof(char));
nl->data = newPtr;
}
nl->data[len(nl)] =  c;

nl->length = nLength+1;
} else {
nl->data[len(nl)] =  c;

};
};
;
i =  i + 1;
;
};
struct string r =  string(arrToStr(nl));
;
return r;
};
struct markdown parseMarkdown(char * a){
struct string md =  string(a);
;
array(struct string)* lines =  splitString(md,"\n");
;
struct markdown m =  {};
;
m.lines = memoryAlloc(sizeof(array(struct markdownLine*)));
            m.lines->length = 0;
            m.lines->elemSize = sizeof(struct markdownLine*);
            m.str = markdown__str;
m.html = markdown__html;
long int i =  0;
;
while ((i<len(lines))) {
struct string l =  lines->data[i];
;
struct string* nl = memoryAlloc(sizeof(struct string));
;
nl->set = string__set;
nl->append = string__append;
nl->prepend = string__prepend;
nl->charAt = string__charAt;
nl->compare = string__compare;
nl->str = string__str;
nl->replace = string__replace;
nl->count = string__count;
nl->hasPrefix = string__hasPrefix;
nl->hasSuffix = string__hasSuffix;
nl->trim = string__trim;
nl->trimLeft = string__trimLeft;
nl->trimRight = string__trimRight;
struct markdownLine* ml = memoryAlloc(sizeof(struct markdownLine));
;
ml->type = 0;
if ((l.count(&l,"```")>0)) {
long int starts =  1;
;
array(struct string)* lineParts =  splitString(l,"```");
;
if ((len(lineParts)>0)) {
ml->rel =  lineParts->data[1];
;
}
else {
ml->rel =  string("");
;
}
ml->type =  10;
;
nl->set(nl,"");
i =  i + 1;
;
while ((i<len(lines))) {
struct string ll =  lines->data[i];
;
if ((ll.count(&ll,"```")>0)) {
break;
}
ll.append(&ll,"\n");
nl->append(nl,ll.str(&ll));
i =  i + 1;
;
};
ml->line =  nl;
;

{
long nLength = len(m.lines);
if (m.lines->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(m.lines->data, (nLength+50)*sizeof(struct markdownLine*));
m.lines->data = newPtr;
}
m.lines->data[len(m.lines)] =  ml;

m.lines->length = nLength+1;
} else {
m.lines->data[len(m.lines)] =  ml;

};
};
;
i =  i + 1;
;
continue;
}
l.trim(&l);
l =  parseMarkdownInline(l);
;
if (l.hasPrefix(&l,"# ")) {
ml->type =  1;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else if (l.hasPrefix(&l,"## ")) {
ml->type =  2;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,3);
}
else if (l.hasPrefix(&l,"### ")) {
ml->type =  3;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,4);
}
else if (l.hasPrefix(&l,"#### ")) {
ml->type =  4;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,5);
}
else if (l.hasPrefix(&l,"##### ")) {
ml->type =  5;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,6);
}
else if (l.hasPrefix(&l,"###### ")) {
ml->type =  6;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,7);
}
else if (l.hasPrefix(&l,"- ")) {
ml->type =  7;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else if (l.hasPrefix(&l,"> ")) {
ml->type =  9;
;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else {
if ((l.length>0)) {
char fc =  l.charAt(&l,0);
;
if (isNumber(fc)) {
ml->type =  8;
;
}
}
nl->set(nl,l.str(&l));
}
ml->line =  nl;
;

{
long nLength = len(m.lines);
if (m.lines->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(m.lines->data, (nLength+50)*sizeof(struct markdownLine*));
m.lines->data = newPtr;
}
m.lines->data[len(m.lines)] =  ml;

m.lines->length = nLength+1;
} else {
m.lines->data[len(m.lines)] =  ml;

};
};
;
i =  i + 1;
;
};
return m;
};
void escapeMarkdownHTML(struct string* s){
s->replace(s,"*","&ast;");
s->replace(s,">","&gt;");
s->replace(s,"<","&lt;");
s->replace(s,"__","&lowbar;&lowbar;");
s->replace(s,"-","&minus;");
s->replace(s,"#","&num;");
};
#include <pthread.h>
struct mutex {
pthread_mutex_t id;
void(*init)(struct mutex* this);
void(*lock)(struct mutex* this);
void(*unlock)(struct mutex* this);
void(*destroy)(struct mutex* this);
};
void mutex__init(struct mutex* this){
pthread_mutex_init(&this->id,0);
};
void mutex__lock(struct mutex* this){
pthread_mutex_lock(&this->id);
};
void mutex__unlock(struct mutex* this){
pthread_mutex_unlock(&this->id);
};
void mutex__destroy(struct mutex* this){
pthread_mutex_destroy(&this->id);
};
struct thread {
long int id;
void (*handle)(long int);
void(*create)(struct thread* this);
void(*createWithArg)(struct thread* this,void * arg);
void(*wait)(struct thread* this);
};
void thread__create(struct thread* this){
void * z0 =  (void *)0;
;
GC_pthread_create(&this->id,z0,this->handle,z0);
};
void thread__createWithArg(struct thread* this,void * arg){
void * z0 =  (void *)0;
;
GC_pthread_create(&this->id,z0,this->handle,arg);
};
void thread__wait(struct thread* this){
void * z0 =  (void *)0;
;
GC_pthread_join(this->id,z0);
};
struct mutex mutex(){
struct mutex m =  {};
;
m.init = mutex__init;
m.lock = mutex__lock;
m.unlock = mutex__unlock;
m.destroy = mutex__destroy;
m.init(&m);
return m;
};
#define BASE_PATH "./pages"
long int* COOLDOWN;
struct string parsePath(char * p){
struct string path =  string(p);
;
if (path.compare(&path,"/")) {
path.append(&path,"index.html");
}
path.prepend(&path,BASE_PATH);
return path;
};
void server(struct http_server* serv,long int connfd){
struct http_request req =  http_request(connfd);
;
struct http_response resp =  http_response(connfd);
;
resp.setHeader(&resp,"Content-Type","text/html");
struct string path =  parsePath(req.path);
;
*COOLDOWN =  time(0);
;
if (path.compare(&path,"/ping")) {
resp.write(&resp,"ok");
resp.send(&resp);
return ;
}
struct fileMap fs =  {};
;
fs.open = fileMap__open;
fs.isValid = fileMap__isValid;
fs.close = fileMap__close;
char * page;
if (path.hasPrefix(&path,"./pages/doc/")) {
char * header =  fs.open(&fs,"./pages/doc/header.html");
;
fs.close(&fs);
resp.write(&resp,header);
path.append(&path,".md");
char * mdf =  fs.open(&fs,path.str(&path));
;
if ((fs.isValid(&fs)==0)) {
mdf =  "\n# 404\n## Page not found.\nYou can go to the [syntax](/doc/syntax) page to access the documentation.           \n";
;
}
struct markdown md =  parseMarkdown(mdf);
;
char * mdhtml =  md.html(&md);
;
resp.write(&resp,mdhtml);
fs.close(&fs);
char * footer =  fs.open(&fs,"./pages/doc/footer.html");
;
struct string footerS =  string(footer);
;
footerS.replace(&footerS,"{isapp}","true");
fs.close(&fs);
resp.write(&resp,footerS.str(&footerS));
}
else {
page =  fs.open(&fs,path.str(&path));
;
fs.close(&fs);
resp.write(&resp,page);
}
resp.send(&resp);
};
char * locateChrome(){
array(char *)* paths = memoryAlloc(sizeof(array(char *)));;

paths->length = 5;
paths->elemSize = sizeof(char *);
paths->data = memoryAlloc(sizeof(char *) * 50);paths->data[0] = __STR("/usr/bin/google-chrome-stable");
paths->data[1] = __STR("/usr/bin/google-chrome");
paths->data[2] = __STR("/usr/bin/chromium");
paths->data[3] = __STR("/usr/bin/chromium-browser");
paths->data[4] = __STR("/snap/bin/chromium");
long int i =  0;
;
while ((i<len(paths))) {
char * p =  paths->data[i];
;
if (fileExists(p)) {
return p;
}
i =  i + 1;
;
};
struct command cmd =  command("zenity --error --title \"Missing chromium\" --text \"Could not find chrome/chromium on this machine.\"");
;
cmd.run(&cmd);
return "";
};
void createChrome(long int port){
char * cmdS =  concatCPSTRING(concatCPSTRING(concatCPSTRING(locateChrome()," --app=http://localhost:"),intToStr(port)),"/doc/syntax");
;
struct command cmd =  command(cmdS);
;
cmd.run(&cmd);
};
void checkCooldown(long int id){
while ((1==1)) {
sleep(1);
long int s =  time(0) - *COOLDOWN;
;
if ((s>2)) {
exit(0);
}
};
};
void main(__BAH_ARR_TYPE_cpstring args){
println("launching");
COOLDOWN =  sharedMemory(0);
;
*COOLDOWN =  time(0);
;
println("made cooldown");
struct thread tcd =  {};
;
tcd.create = thread__create;
tcd.createWithArg = thread__createWithArg;
tcd.wait = thread__wait;
tcd.handle =  checkCooldown;
;
tcd.create(&tcd);
println("created cooldown thread");
long int port =  49152;
;
while ((port<=65535)) {
if (isPortAvailable(port)) {
break;
}
else if ((port==65535)) {
panic("webapp: no available port.");
}
port =  port + 1;
;
};
println("found port");
struct http_server s =  {};
;
s.running = 1;
s.sockfd = -1;
s.listenAndServe = http_server__listenAndServe;
s.stop = http_server__stop;
s.port =  port;
;
s.handle =  server;
;
createChrome(port);
println("created chrome");
println("launching server");
s.listenAndServe(&s);
};
