//COMPILE WITH: 'gcc ./build_doc.c -w  -static -w /opt/bah/libs/libgc.a -lpthread -lm -g'

#include "/opt/bah/libs/include/gc.h"

#define noCheck(v) v
#define array(type)	struct{	type *data; long int length; long int elemSize; }
typedef array(char*)* __BAH_ARR_TYPE_cpstring;
long int __BAH__main(__BAH_ARR_TYPE_cpstring);

int main(int argc, char ** argv) {
GC_INIT();
array(char*) * args = GC_MALLOC(sizeof(array(char*)));
args->data = GC_MALLOC(sizeof(char*)*argc);
memcpy(args->data, argv, sizeof(char*)*argc);
args->elemSize = sizeof(char*);
args->length = argc;
return __BAH__main((__BAH_ARR_TYPE_cpstring)args);
};
#define main(v) __BAH__main(v)
#include <signal.h>
#include <string.h>
#define null (void *)0
#define true (int)1
#define false (int)0
#include </opt/bah/libs/include/gc.h>
#include <sys/mman.h>
#define SIZE_OF_INT 8
#define SIZE_OF_CHAR 1
#define SIZE_OF_INT32 4
#define SIZE_OF_FLOAT32 4
#define SIZE_OF_FLOAT 8
long int len(void * a){
long int i =  0;
noCheck( array ( void* ) *arr = a );
noCheck( i = arr -> length );
return i;
};
void * memoryAlloc(long int s){
void * p =  GC_MALLOC(s);
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
long int lenB =  0;
long int realSizeA =  0;
long int realSizeB =  0;
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
noCheck( memcpy ( buff , arrA -> data , realSizeA ) );
noCheck( memcpy ( buff + lenA , arrB -> data , realSizeB ) );
noCheck( arrA -> length = lenA + lenB );
noCheck( arrA -> data = buff );
};
void copy(void * a,void * b){
noCheck( array ( void* ) *arrA = a );
noCheck( array ( void* ) *arrB = b );
long int lenB =  0;
long int realSizeB =  0;
noCheck( lenB = len ( arrB ) );
noCheck( realSizeB = lenB * arrB -> elemSize );
noCheck( arrA -> data = memoryAlloc ( realSizeB ) );
noCheck( memcpy ( arrA -> data , arrB -> data , realSizeB ) );
noCheck( arrA -> length = arrB -> length );
};
void * memoryRealloc(void * p,long int s){
void * np =  GC_REALLOC(p,s);
return np;
};
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_READWRITE 3
#define MAP_SHARED 1
#define MAP_ANONYMOUS 32
void * sharedMemory(long int size){
if ((size==0)) {
size =  4096;
}
void * r =  mmap(0,size,PROT_READ + PROT_WRITE,MAP_SHARED + MAP_ANONYMOUS,-1,0);
return r;
};
char * concatCPSTRING(char * a,char * b){
long int lenA =  strlen(a);
long int lenB =  strlen(b);
char * r =  memoryAlloc(lenA + lenB + 1);
strncpy(r,a,lenA);
strcat(r,b);
return r;
};
char * __STR(char * a){
long int lenA =  strlen(a);
char * r =  memoryAlloc(lenA + 1);
strncpy(r,a,lenA);
return r;
};
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
char cpstringCharAt(char * s,long int i){
char c =  (char)0;
noCheck( c = s [ i ] );
return c;
};
char * charToString(char c){
char * s =  memoryAlloc(2);
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
this->content =  (char *)memoryAlloc(this->length + 1);
strcpy(this->content,s);
};
void string__append(struct string* this,char * s){
this->length =  this->length + strlen(s);
char * tmpS =  (char *)memoryRealloc((void *)this->content,this->length);
if (((long int)tmpS==0)) {
tmpS =  (char *)memoryAlloc(this->length);
strncpy(tmpS,this->content,this->length);
}
strcat(tmpS,s);
this->content =  tmpS;
};
void string__prepend(struct string* this,char * s){
char * tmpS =  memoryAlloc(this->length + 1);
strcpy(tmpS,this->content);
this->length =  this->length + strlen(s);
this->content =  (char *)memoryAlloc(this->length + 1);
strcpy(this->content,s);
strcat(this->content,tmpS);
};
char string__charAt(struct string* this,long int i){
char c =  (char)0;
if ((i<this->length)) {
noCheck( c = this -> content [ i ] );
return c;
}
return c;
};
long int string__compare(struct string* this,char * s){
long int r =  strcmp(this->content,s);
if ((r==0)) {
return 1;
}
return 0;
};
char * string__str(struct string* this){
char * r =  this->content;
return r;
};
void string__replace(struct string* this,char * nd,char * rl){
struct string needle =  {};
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.replace = string__replace;
needle.set(&needle,nd);
struct string repl =  {};
repl.set = string__set;
repl.append = string__append;
repl.prepend = string__prepend;
repl.charAt = string__charAt;
repl.compare = string__compare;
repl.str = string__str;
repl.replace = string__replace;
repl.set(&repl,rl);
long int i =  0;
long int si =  0;
array(char)* replcBuff = memoryAlloc(sizeof(array(char)));

replcBuff->length = 0;
replcBuff->elemSize = sizeof(char);
array(char)* buff = memoryAlloc(sizeof(array(char)));

buff->length = 0;
buff->elemSize = sizeof(char);
while ((i<this->length)) {
char c =  this->charAt(this,i);
char rc =  needle.charAt(&needle,si);
if ((c==rc)) {
si =  si + 1;

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
}
else {
if ((len(replcBuff)>0)) {
si =  0;
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
}
if ((si==needle.length)) {
clear(replcBuff);
long int ii =  0;
while ((ii<repl.length)) {
long int a =  ii;

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
ii =  ii + 1;
};
si =  0;
}
i =  i + 1;
};
char * r =  "";
noCheck( r = buff -> data );
if ((len(replcBuff)>0)) {
char * replbuffStr;
noCheck( replbuffStr = replcBuff -> data );
r =  concatCPSTRING(r,replbuffStr);
}
this->set(this,r);
};
long int string__count(struct string* this,char * need){
long int i =  0;
long int count =  0;
struct string needle =  {};
needle.set = string__set;
needle.append = string__append;
needle.prepend = string__prepend;
needle.charAt = string__charAt;
needle.compare = string__compare;
needle.str = string__str;
needle.replace = string__replace;
needle.count = string__count;
needle.set(&needle,need);
long int countIndex =  0;
while ((i<this->length)) {
char c =  this->charAt(this,i);
char sc =  needle.charAt(&needle,countIndex);
if ((c==sc)) {
countIndex =  countIndex + 1;
}
else {
countIndex =  0;
}
if ((countIndex==needle.length)) {
count =  count + 1;
countIndex =  0;
}
i =  i + 1;
};
return count;
};
long int string__hasPrefix(struct string* this,char * need){
long int i =  0;
long int nl =  strlen(need);
if ((this->length<nl)) {
return 0;
}
while ((i<nl)) {
char c =  this->charAt(this,i);
char sc =  cpstringCharAt(need,i);
if ((c!=sc)) {
return 0;
}
i =  i + 1;
};
return 1;
};
long int string__hasSuffix(struct string* this,char * need){
long int nl =  strlen(need);
if ((this->length<nl)) {
return 0;
}
long int i =  this->length - nl;
long int needleIndex =  0;
while ((i<this->length)) {
char c =  this->charAt(this,i);
char sc =  cpstringCharAt(need,needleIndex);
if ((c!=sc)) {
return 0;
}
needleIndex =  needleIndex + 1;
i =  i + 1;
};
return 1;
};
void string__trim(struct string* this){
if ((this->length==0)) {
return ;
}
char fc =  this->charAt(this,0);
if ((isSpace(fc)==0)) {
return ;
}
long int i =  0;
while ((i<this->length)) {
char c =  this->charAt(this,i);
if ((isSpace(c)==0)) {
break;
}
i =  i + 1;
};
if ((i>0)) {
this->length =  this->length - i;
char * tmpS =  memoryAlloc(this->length + 1);
memcpy(tmpS,noCheck( this->content + i ),this->length + 1);
this->content =  tmpS;
}
};
void string__trimLeft(struct string* this,long int s){
long int nSize =  this->length - s;
void * tmpS =  memoryAlloc(nSize);
memcpy(tmpS,noCheck( this->content + s ),nSize);
this->content =  tmpS;
this->length =  nSize;
};
void string__trimRight(struct string* this,long int s){
long int nSize =  this->length - s;
void * tmpS =  memoryAlloc(nSize);
memcpy(tmpS,this->content,nSize);
this->content =  tmpS;
this->length =  nSize;
};
struct string string(char * s){
struct string a =  {};
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
a.length =  0;
a.set(&a,s);
return a;
};
typedef array(char)* __BAH_ARR_TYPE_char;
char * arrToStr(__BAH_ARR_TYPE_char arr){
long int strLen =  len(arr);
char * str =  memoryAlloc(strLen + 1);
noCheck( memcpy ( str , arr -> data , strLen ) );
return str;
};
__BAH_ARR_TYPE_char strToArr(char * str){
long int strLen =  strlen(str);
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
noCheck( arr -> data = memoryAlloc ( strLen + 1 ) );
noCheck( memcpy ( arr -> data , str , strLen ) );
noCheck( arr -> length = strLen );
return arr;
};
char * arrAsStr(__BAH_ARR_TYPE_char arr){
char * r =  "";
noCheck( r = arr -> data );
return r;
};
struct string intToString(long int i){
char * buff =  memoryAlloc(65);
void * ptri =  (void *)i;
sprintf(buff,"%d",ptri);
struct string r =  string(buff);
return r;
};
char * intToStr(long int i){
char * buff =  memoryAlloc(65);
sprintf(buff,"%ld",(void *)i);
return buff;
};
long int stringToInt(struct string s){
long int i =  atoi(s.content);
return i;
};
typedef array(struct string)* __BAH_ARR_TYPE_string;
__BAH_ARR_TYPE_string splitString(struct string s,char * sp){
struct string sep =  string(sp);
array(struct string)* res = memoryAlloc(sizeof(array(struct string)));

res->length = 0;
res->elemSize = sizeof(struct string);
struct string sepBuffer =  string("");
long int sepIndex =  0;
long int i =  0;
struct string replcBuff =  string("");
array(char)* tmpString = memoryAlloc(sizeof(array(char)));

tmpString->length = 0;
tmpString->elemSize = sizeof(char);
while ((i<s.length)) {
char c =  s.charAt(&s,i);
char sepc =  sep.charAt(&sep,sepIndex);
if ((c==sepc)) {
sepIndex =  sepIndex + 1;
replcBuff.append(&replcBuff,charToString(c));
}
else {
if ((sepIndex>0)) {
sepIndex =  0;
replcBuff.append(&replcBuff,charToString(c));
long int ii =  0;
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
ii =  ii + 1;
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
}
}
if ((sepIndex==sep.length)) {
replcBuff.set(&replcBuff,"");
struct string* elem = memoryAlloc(sizeof(struct string));
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
clear(tmpString);
sepIndex =  0;
}
i =  i + 1;
};
if ((replcBuff.length>0)) {
long int ii =  0;
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
ii =  ii + 1;
};
}
if ((len(tmpString)>0)) {
struct string* elem = memoryAlloc(sizeof(struct string));
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
}
return res;
};
struct string joinString(__BAH_ARR_TYPE_string a,char * sep){
long int i =  0;
struct string s =  string("");
long int max =  len(a) - 1;
while ((i<len(a))) {
struct string e =  a->data[i];
if ((e.length==0)) {
i =  i + 1;
continue;
}
struct string tmpS =  string(e.str(&e));
if ((i!=max)) {
tmpS.append(&tmpS,sep);
}
s.append(&s,tmpS.str(&tmpS));
i =  i + 1;
};
return s;
};
char * splitStringBefore(struct string s,char * sp){
struct string sep =  string(sp);
if ((sep.length>=s.length)) {
return "";
}
long int sepIndex =  0;
long int foundIndex =  0;
long int i =  0;
while ((i<s.length)) {
char c =  s.charAt(&s,i);
char sc =  sep.charAt(&sep,sepIndex);
if ((c==sc)) {
if ((sepIndex==0)) {
foundIndex =  i - 1;
}
sepIndex =  sepIndex + 1;
if ((sepIndex==sep.length)) {
long int max =  s.length - foundIndex - 1;
s.trimRight(&s,max);
return s.str(&s);
}
}
else {
foundIndex =  0;
sepIndex =  0;
}
i =  i + 1;
};
return "";
};
struct string toLower(struct string s){
array(char)* ns = memoryAlloc(sizeof(array(char)));

ns->length = 0;
ns->elemSize = sizeof(char);
long int i =  0;
while ((i<s.length)) {
char c =  s.charAt(&s,i);
if (isUpper(c)) {
c =  c + (char)32;
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
i =  i + 1;
};
return string(arrToStr(ns));
};
int strHasPrefix(char * s,char * need){
long int i =  0;
long int nl =  strlen(need);
long int sl =  strlen(s);
if ((sl<nl)) {
return false;
}
while ((i<nl)) {
char c =  cpstringCharAt(s,i);
char sc =  cpstringCharAt(need,i);
if ((c!=sc)) {
return false;
}
i =  i + 1;
};
return true;
};
char * stdinput(long int len){
char * buff =  memoryAlloc(len);
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
fclose(this->handle);
return size;
};
char * fileStream__readContent(struct fileStream* this){
if ((this->isValid(this)==0)) {
return "invalid";
}
fseek(this->handle,0,2);
long int size =  ftell(this->handle);
rewind(this->handle);
char c =  getc(this->handle);
long int i =  0;
array(char)* s = memoryAlloc(sizeof(array(char)));

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
i =  i + 1;
c =  getc(this->handle);
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
long int ls =  len(s);
char * r =  "";
noCheck( r = s -> data );
return r;
};
void fileStream__rewind(struct fileStream* this){
rewind(this->handle);
};
char fileStream__getChar(struct fileStream* this){
char c =  getc(this->handle);
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
struct stat sb =  {};
fstat(this->handle,&sb);
char * file =  mmap(0,sb.st_size,noCheck( PROT_READ | PROT_WRITE ),noCheck( MAP_SHARED ),this->handle,0);
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
__BAH_ARR_TYPE_cpstring listFiles(char * dir){
array(char *)* files = memoryAlloc(sizeof(array(char *)));

files->length = 0;
files->elemSize = sizeof(char *);
DIR* d =  opendir(dir);
struct dirent* file =  readdir(d);
while ((file!=null)) {
long int lf =  len(files);
if ((strcmp(file->d_name,".")==0)) {
file =  readdir(d);
continue;
}
if ((strcmp(file->d_name,"..")==0)) {
file =  readdir(d);
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
file =  readdir(d);
};
closedir(d);
return files;
};
long int fileExists(char * path){
long int is =  access(path,0);
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
#define FLAG_TYPE_CPSTRING 0
#define FLAG_TYPE_INT 1
#define FLAG_TYPE_FLOAT 2
#define FLAG_TYPE_BOOL 3
struct flag {
char * name;
char * help;
char * content;
long int cont_int;
double cont_float;
long int isSet;
long int type;
};
struct flags {
array(struct flag*)* flags;
array(char *)* args;
void(*addString)(struct flags* this,char * name,char * help);
void(*addBool)(struct flags* this,char * name,char * help);
void(*addInt)(struct flags* this,char * name,char * help);
void(*addFloat)(struct flags* this,char * name,char * help);
void(*invalidate)(struct flags* this);
struct flag*(*getFlag)(struct flags* this,struct string name);
char *(*get)(struct flags* this,char * name);
long int(*getInt)(struct flags* this,char * name);
double(*getFloat)(struct flags* this,char * name);
long int(*isSet)(struct flags* this,char * name);
void(*parse)(struct flags* this,array(char *)* args);
};
void flags__addString(struct flags* this,char * name,char * help){
struct flag* f = memoryAlloc(sizeof(struct flag));
f->name =  name;
f->help =  help;
f->type =  FLAG_TYPE_CPSTRING;
long int lf =  len(this->flags);

{
long nLength = lf;
if (this->flags->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(this->flags->data, (nLength+50)*sizeof(struct flag*));
this->flags->data = newPtr;
}
this->flags->data[lf] =  f;
this->flags->length = nLength+1;
} else {
this->flags->data[lf] =  f;
};
};
};
void flags__addBool(struct flags* this,char * name,char * help){
struct flag* f = memoryAlloc(sizeof(struct flag));
f->name =  name;
f->help =  help;
f->type =  FLAG_TYPE_BOOL;
long int lf =  len(this->flags);

{
long nLength = lf;
if (this->flags->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(this->flags->data, (nLength+50)*sizeof(struct flag*));
this->flags->data = newPtr;
}
this->flags->data[lf] =  f;
this->flags->length = nLength+1;
} else {
this->flags->data[lf] =  f;
};
};
};
void flags__addInt(struct flags* this,char * name,char * help){
struct flag* f = memoryAlloc(sizeof(struct flag));
f->name =  name;
f->help =  help;
f->type =  FLAG_TYPE_INT;
long int lf =  len(this->flags);

{
long nLength = lf;
if (this->flags->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(this->flags->data, (nLength+50)*sizeof(struct flag*));
this->flags->data = newPtr;
}
this->flags->data[lf] =  f;
this->flags->length = nLength+1;
} else {
this->flags->data[lf] =  f;
};
};
};
void flags__addFloat(struct flags* this,char * name,char * help){
struct flag* f = memoryAlloc(sizeof(struct flag));
f->name =  name;
f->help =  help;
f->type =  FLAG_TYPE_FLOAT;
long int lf =  len(this->flags);

{
long nLength = lf;
if (this->flags->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(this->flags->data, (nLength+50)*sizeof(struct flag*));
this->flags->data = newPtr;
}
this->flags->data[lf] =  f;
this->flags->length = nLength+1;
} else {
this->flags->data[lf] =  f;
};
};
};
void flags__invalidate(struct flags* this){
print("Usage of ");
print(this->args->data[0]);
println(":");
long int i =  0;
while ((i<len(this->flags))) {
struct flag* flag =  this->flags->data[i];
print("    -");
print(flag->name);
if ((flag->type==FLAG_TYPE_CPSTRING)) {
println(" (string)");
}
else if ((flag->type==FLAG_TYPE_BOOL)) {
println(" (bool)");
}
else if ((flag->type==FLAG_TYPE_INT)) {
println(" (int)");
}
else if ((flag->type==FLAG_TYPE_FLOAT)) {
println(" (float)");
}
print("\t");
println(flag->help);
i =  i + 1;
};
exit(1);
};
struct flag* flags__getFlag(struct flags* this,struct string name){
long int i =  0;
while ((i<len(this->flags))) {
struct flag* flag =  this->flags->data[i];
if (name.compare(&name,flag->name)) {
return flag;
}
i =  i + 1;
};
struct flag* z = memoryAlloc(sizeof(struct flag));
z->isSet =  0;
return z;
};
char * flags__get(struct flags* this,char * name){
struct flag* flag =  this->getFlag(this,string(name));
char * ctn =  flag->content;
return ctn;
};
long int flags__getInt(struct flags* this,char * name){
struct flag* flag =  this->getFlag(this,string(name));
if ((flag->type!=FLAG_TYPE_INT)) {
char * error =  concatCPSTRING(concatCPSTRING("Flag '",flag->name),"' is not int.");
panic(error);
}
long int ctn =  flag->cont_int;
return ctn;
};
double flags__getFloat(struct flags* this,char * name){
struct flag* flag =  this->getFlag(this,string(name));
if ((flag->type!=FLAG_TYPE_FLOAT)) {
char * error =  concatCPSTRING(concatCPSTRING("Flag '",flag->name),"' is not float.");
panic(error);
}
double ctn =  flag->cont_float;
return ctn;
};
long int flags__isSet(struct flags* this,char * name){
struct flag* flag =  this->getFlag(this,string(name));
long int ctn =  flag->isSet;
return ctn;
};
void flags__parse(struct flags* this,__BAH_ARR_TYPE_cpstring args){
struct flag* currentFlag;
int isVal =  false;
this->args =  args;
long int i =  1;
while ((i<len(args))) {
struct string argName =  string(args->data[i]);
if ((isVal==true)) {
currentFlag->content =  argName.str(&argName);
if ((currentFlag->type==FLAG_TYPE_INT)) {
currentFlag->cont_int =  atoi(argName.str(&argName));
}
else if ((currentFlag->type==FLAG_TYPE_FLOAT)) {
currentFlag->cont_float =  strtod(argName.str(&argName),0);
}
isVal =  false;
}
else {
if ((argName.charAt(&argName,0)!=45)) {
i =  i + 1;
continue;
}
argName.trimLeft(&argName,1);
if (argName.compare(&argName,"help")) {
this->invalidate(this);
}
else if (argName.compare(&argName,"h")) {
this->invalidate(this);
}
currentFlag =  this->getFlag(this,argName);
if ((currentFlag==null)) {
this->invalidate(this);
}
currentFlag->isSet =  1;
if ((currentFlag->type!=FLAG_TYPE_BOOL)) {
isVal =  true;
}
}
i =  i + 1;
};
if ((isVal==true)) {
if ((currentFlag->type!=FLAG_TYPE_BOOL)) {
this->invalidate(this);
}
}
};
void appendCharArr(__BAH_ARR_TYPE_char a,__BAH_ARR_TYPE_char b){
long int offset =  len(a);
long int lenB =  len(b);
long int i =  0;
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
i =  i + 1;
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
long int i =  0;
while ((i<len(this->lines))) {
struct markdownLine* mdl =  this->lines->data[i];
char * si =  intToStr(i);
char * l =  mdl->line->str(mdl->line);
s =  concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(s,si),": "),l),"\n");
i =  i + 1;
};
return s;
};
char * markdown__html(struct markdown* this){
char * html =  "<p>";
long int i =  0;
while ((i<len(this->lines))) {
struct markdownLine* mdl =  this->lines->data[i];
char * l =  mdl->line->str(mdl->line);
if ((mdl->type==1)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h1>"),l),"</h1><hr>");
}
else if ((mdl->type==2)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h2>"),l),"</h2><hr>");
}
else if ((mdl->type==3)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h3>"),l),"</h3>");
}
else if ((mdl->type==4)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h4>"),l),"</h4>");
}
else if ((mdl->type==5)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h5>"),l),"</h5>");
}
else if ((mdl->type==6)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<h3>"),l),"</h3>");
}
else if ((mdl->type==7)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"&nbsp;• "),l),"<br>");
}
else if ((mdl->type==8)) {
html =  concatCPSTRING(concatCPSTRING(html,"\t"),l);
}
else if ((mdl->type==9)) {
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<blockquote>"),l),"</blockquote>");
}
else if ((mdl->type==10)) {
char * rel =  mdl->rel.str(&mdl->rel);
html =  concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(concatCPSTRING(html,"<pre class=\"highlight highlight-source-"),rel),"\">"),l),"</pre>");
}
else {
html =  concatCPSTRING(concatCPSTRING(html,l),"<br>");
}
html =  concatCPSTRING(html,"\n");
i =  i + 1;
};
html =  concatCPSTRING(html,"</p>");
return html;
};
struct string parseMarkdownInline(struct string l){
if ((l.length==0)) {
return l;
}
array(char)* nl = memoryAlloc(sizeof(array(char)));

nl->length = 0;
nl->elemSize = sizeof(char);
long int isBold =  0;
long int isItal =  0;
long int isUline =  0;
long int isImage =  0;
long int isLink =  0;
array(char)* linkName = memoryAlloc(sizeof(array(char)));

linkName->length = 0;
linkName->elemSize = sizeof(char);
array(char)* linkUrl = memoryAlloc(sizeof(array(char)));

linkUrl->length = 0;
linkUrl->elemSize = sizeof(char);
long int i =  0;
while ((i<l.length)) {
char c =  l.charAt(&l,i);
if ((isLink==1)) {
if ((c==93)) {
isLink =  2;
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
}
i =  i + 1;
continue;
}
if ((isLink==2)) {
if ((c==40)) {
isLink =  3;
}
i =  i + 1;
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
}
else {
appendCharArr(nl,strToArr("<a href=\""));
appendCharArr(nl,linkUrl);
appendCharArr(nl,strToArr("\">"));
appendCharArr(nl,linkName);
appendCharArr(nl,strToArr("</a>"));
}
isLink =  0;
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
}
i =  i + 1;
continue;
}
if ((c==91)) {
long int validateState =  0;
long int ii =  i;
while ((ii<l.length)) {
char vc =  l.charAt(&l,ii);
if ((validateState==0)) {
if ((vc==93)) {
validateState =  1;
}
}
else if ((validateState==1)) {
if ((vc==40)) {
validateState =  2;
ii =  ii + 1;
continue;
}
if ((isSpace(vc)==0)) {
validateState =  0;
}
}
else if ((validateState==2)) {
if ((vc==41)) {
validateState =  3;
break;
}
}
ii =  ii + 1;
};
if ((validateState==3)) {
isLink =  1;
i =  i + 1;
continue;
}
else if ((isImage==1)) {
isImage =  0;

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
}
}
if ((c==33)) {
char nc =  l.charAt(&l,i + 1);
if ((nc==91)) {
isImage =  1;
}
i =  i + 1;
continue;
}
if ((c==42)) {
if ((l.charAt(&l,i + 1)==42)) {
if ((isBold==1)) {
appendCharArr(nl,strToArr("</strong>"));
isBold =  0;
}
else {
appendCharArr(nl,strToArr("<strong>"));
isBold =  1;
}
i =  i + 2;
continue;
}
else {
if ((isItal==1)) {
appendCharArr(nl,strToArr("</em>"));
isItal =  0;
}
else {
appendCharArr(nl,strToArr("<em>"));
isItal =  1;
}
i =  i + 1;
continue;
}
}
if ((c==95)) {
if ((l.charAt(&l,i + 1)==95)) {
if ((isUline==1)) {
appendCharArr(nl,strToArr("</u>"));
isUline =  0;
}
else {
appendCharArr(nl,strToArr("<u>"));
isUline =  1;
}
i =  i + 2;
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
i =  i + 1;
};
struct string r =  string(arrToStr(nl));
return r;
};
struct markdown parseMarkdown(char * a){
struct string md =  string(a);
array(struct string)* lines =  splitString(md,"\n");
struct markdown m =  {};
m.lines = memoryAlloc(sizeof(array(struct markdownLine*)));
            m.lines->length = 0;
            m.lines->elemSize = sizeof(struct markdownLine*);
            m.str = markdown__str;
m.html = markdown__html;
long int i =  0;
while ((i<len(lines))) {
struct string l =  lines->data[i];
struct string* nl = memoryAlloc(sizeof(struct string));
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
ml->type = 0;
if ((l.count(&l,"```")>0)) {
long int starts =  1;
array(struct string)* lineParts =  splitString(l,"```");
if ((len(lineParts)>0)) {
ml->rel =  lineParts->data[1];
}
else {
ml->rel =  string("");
}
ml->type =  10;
nl->set(nl,"");
i =  i + 1;
while ((i<len(lines))) {
struct string ll =  lines->data[i];
if ((ll.count(&ll,"```")>0)) {
break;
}
ll.append(&ll,"\n");
nl->append(nl,ll.str(&ll));
i =  i + 1;
};
ml->line =  nl;

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
i =  i + 1;
continue;
}
l.trim(&l);
l =  parseMarkdownInline(l);
if (l.hasPrefix(&l,"# ")) {
ml->type =  1;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else if (l.hasPrefix(&l,"## ")) {
ml->type =  2;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,3);
}
else if (l.hasPrefix(&l,"### ")) {
ml->type =  3;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,4);
}
else if (l.hasPrefix(&l,"#### ")) {
ml->type =  4;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,5);
}
else if (l.hasPrefix(&l,"##### ")) {
ml->type =  5;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,6);
}
else if (l.hasPrefix(&l,"###### ")) {
ml->type =  6;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,7);
}
else if (l.hasPrefix(&l,"- ")) {
ml->type =  7;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else if (l.hasPrefix(&l,"> ")) {
ml->type =  9;
nl->set(nl,l.str(&l));
nl->trimLeft(nl,2);
}
else {
if ((l.length>0)) {
char fc =  l.charAt(&l,0);
if (isNumber(fc)) {
ml->type =  8;
}
}
nl->set(nl,l.str(&l));
}
ml->line =  nl;

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
i =  i + 1;
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
char * isFuncDecl(struct string line){
array(char)* name = memoryAlloc(sizeof(array(char)));

name->length = 0;
name->elemSize = sizeof(char);
long int foundPar =  0;
long int i =  0;
while ((i<line.length)) {
char c =  line.charAt(&line,i);
if (isSpace(c)) {
if ((len(name)==0)) {
i =  i + 1;
continue;
}
}
if ((isAlphaNumeric(c)==0)) {
if ((c==40)) {
foundPar =  1;
break;
}
else {
return "";
}
}
else {

{
long nLength = len(name);
if (name->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(name->data, (nLength+50)*sizeof(char));
name->data = newPtr;
}
name->data[len(name)] =  c;
name->length = nLength+1;
} else {
name->data[len(name)] =  c;
};
};
}
i =  i + 1;
};
if ((foundPar==0)) {
return "";
}
i =  line.length-1;
while ((i>=0)) {
char c =  line.charAt(&line,i);
if (isSpace(c)) {
i =  i - 1;
continue;
}
if ((c!=123)) {
return "";
}
else {
break;
}
i =  i - 1;
};
return arrAsStr(name);
};
struct elem {
char * type;
char * name;
char * doc;
};
char * getComments(__BAH_ARR_TYPE_string lines,long int i){
struct string doc =  string("");
long int ii =  i-1;
while ((ii>=0)) {
struct string l =  lines->data[ii];
l.trim(&l);
if (l.hasPrefix(&l,"//")) {
struct string dl =  string(l.str(&l));
dl.trimLeft(&dl,2);
dl.append(&dl,"\n");
dl.trim(&dl);
doc.prepend(&doc,dl.str(&dl));
}
else {
break;
}
ii =  ii - 1;
};
return doc.str(&doc);
};
long int main(__BAH_ARR_TYPE_cpstring args){
struct flags flags =  {};
flags.flags = memoryAlloc(sizeof(array(struct flag*)));
            flags.flags->length = 0;
            flags.flags->elemSize = sizeof(struct flag*);
            flags.args = memoryAlloc(sizeof(array(char *)));
            flags.args->length = 0;
            flags.args->elemSize = sizeof(char *);
            flags.addString = flags__addString;
flags.addBool = flags__addBool;
flags.addInt = flags__addInt;
flags.addFloat = flags__addFloat;
flags.invalidate = flags__invalidate;
flags.getFlag = flags__getFlag;
flags.get = flags__get;
flags.getInt = flags__getInt;
flags.getFloat = flags__getFloat;
flags.isSet = flags__isSet;
flags.parse = flags__parse;
flags.addString(&flags,"file","File to parse");
flags.parse(&flags,args);
if ((flags.isSet(&flags,"file")==0)) {
flags.invalidate(&flags);
}
struct fileMap fm =  {};
fm.open = fileMap__open;
fm.isValid = fileMap__isValid;
fm.close = fileMap__close;
char * fn =  flags.get(&flags,"file");
char * content =  fm.open(&fm,fn);
if ((fm.isValid(&fm)==0)) {
panic("File does not exist.");
}
struct string fileName =  string(fn);
if ((fileName.hasSuffix(&fileName,".bah")==0)) {
panic("Cannot open a file that is not bah lang.");
}
struct string example =  string("");
fileName.trimRight(&fileName,4);
array(struct string)* pathElems =  splitString(fileName,"/");
fileName =  pathElems->data[len(pathElems)-1];
fm.close(&fm);
array(struct string)* lines =  splitString(string(content),"\n");
array(struct elem)* elems = memoryAlloc(sizeof(array(struct elem)));

elems->length = 0;
elems->elemSize = sizeof(struct elem);
long int i =  0;
while ((i<len(lines))) {
struct string line =  lines->data[i];
line.trim(&line);
if ((line.length==0)) {
i =  i + 1;
continue;
}
char * name =  isFuncDecl(line);
if ((strlen(name)>0)) {
struct elem elem =  {};
elem.type =  "func";
elem.name =  name;
struct string doc =  string(getComments(lines,i));
line.trimRight(&line,1);
escapeMarkdownHTML(&line);
line.prepend(&line,"<code>");
line.append(&line,"</code>\n");
doc.prepend(&doc,line.str(&line));
elem.doc =  doc.str(&doc);

{
long nLength = len(elems);
if (elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(elems->data, (nLength+50)*sizeof(struct elem));
elems->data = newPtr;
}
elems->data[len(elems)] =  elem;
elems->length = nLength+1;
} else {
elems->data[len(elems)] =  elem;
};
};
}
else {
array(struct string)* words =  splitString(line," ");
struct string fw =  words->data[0];
if (fw.compare(&fw,"struct")) {
long int nbBraces =  0;
struct string doc =  string(getComments(lines,i));
doc.append(&doc,"__Its methods are:__\n");
long int foundMethods =  0;
while ((i<len(lines))) {
struct string l =  lines->data[i];
l.trim(&l);
nbBraces =  nbBraces + l.count(&l,"{");
nbBraces =  nbBraces - l.count(&l,"}");
char * methodName =  isFuncDecl(l);
if ((strlen(methodName)>0)) {
foundMethods =  1;
doc.append(&doc,"- <code>**");
doc.append(&doc,methodName);
doc.append(&doc,"**");
l.trimLeft(&l,strlen(methodName));
l.trimRight(&l,1);
escapeMarkdownHTML(&l);
doc.append(&doc,l.str(&l));
doc.append(&doc,"</code> ");
doc.append(&doc,getComments(lines,i));
doc.trimRight(&doc,1);
doc.append(&doc,"\n");
}
if ((nbBraces==0)) {
break;
}
i =  i + 1;
};
if ((foundMethods==0)) {
doc.trimRight(&doc,21);
}
struct string n =  words->data[1];
struct elem elem =  {};
elem.type =  "struct";
elem.name =  n.str(&n);
elem.doc =  doc.str(&doc);

{
long nLength = len(elems);
if (elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(elems->data, (nLength+50)*sizeof(struct elem));
elems->data = newPtr;
}
elems->data[len(elems)] =  elem;
elems->length = nLength+1;
} else {
elems->data[len(elems)] =  elem;
};
};
}
else if (fw.compare(&fw,"const")) {
struct string n =  words->data[1];
struct elem elem =  {};
elem.type =  "const";
elem.name =  n.str(&n);
elem.doc =  getComments(lines,i);

{
long nLength = len(elems);
if (elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = GC_REALLOC(elems->data, (nLength+50)*sizeof(struct elem));
elems->data = newPtr;
}
elems->data[len(elems)] =  elem;
elems->length = nLength+1;
} else {
elems->data[len(elems)] =  elem;
};
};
}
else if (line.compare(&line,"//Example")) {
i =  i + 1;
while ((i<len(lines))) {
struct string l =  lines->data[i];
l.trim(&l);
if ((l.hasPrefix(&l,"//")==0)) {
break;
}
l.trimLeft(&l,2);
escapeMarkdownHTML(&l);
example.append(&example,l.str(&l));
example.append(&example,"\n");
i =  i + 1;
};
}
}
i =  i + 1;
};
struct string doc =  string("# ");
doc.append(&doc,fileName.str(&fileName));
doc.append(&doc,"\n\n\n");
i =  0;
while ((i<len(elems))) {
struct elem e =  elems->data[i];
doc.append(&doc,"### ");
doc.append(&doc,e.name);
doc.append(&doc," (");
doc.append(&doc,e.type);
doc.append(&doc,")\n");
doc.append(&doc,e.doc);
doc.append(&doc,"\n\n");
i =  i + 1;
};
doc.append(&doc,"## Example\n```bah\n");
doc.append(&doc,example.str(&example));
doc.append(&doc,"```");
fileName.prepend(&fileName,"./pages/doc/libs/");
fileName.append(&fileName,".md");
struct fileStream fs =  {};
fs.isValid = fileStream__isValid;
fs.open = fileStream__open;
fs.close = fileStream__close;
fs.getSize = fileStream__getSize;
fs.readContent = fileStream__readContent;
fs.rewind = fileStream__rewind;
fs.getChar = fileStream__getChar;
fs.createFile = fileStream__createFile;
fs.writeFile = fileStream__writeFile;
fs.open(&fs,fileName.str(&fileName),"w");
fs.writeFile(&fs,doc.str(&doc));
fs.close(&fs);
return 0;
};
