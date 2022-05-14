//COMPILE WITH: 'gcc -I "/opt/bah/libs/linux/include/" -L "/opt/bah/libs/linux/" tmp/DnYhHhZzBdRuXhDpSzJb/main.c -static -O1 -w  -lpthread -lm'

    void __BAH_init();
    #define noCheck(v) v
    #define array(type)	    struct{	    type *data;     long int length;     long int elemSize;     }
    typedef array(char*)* __BAH_ARR_TYPE_cpstring;
    long int __BAH__main(__BAH_ARR_TYPE_cpstring);
    
            void RCP_init();
            void RCP_shutdown();
            void free(void*);
            int main(int argc, char ** argv) {
            RCP_init();
            array(char*) * args = malloc(sizeof(array(char*)));
            args->data = malloc(sizeof(char*)*argc);
            memcpy(args->data, argv, sizeof(char*)*argc);
            args->elemSize = sizeof(char*);
            args->length = argc;
            __BAH_init();
            long int r =  __BAH__main((__BAH_ARR_TYPE_cpstring)args);
            free(args->data);
            free(args);
            RCP_shutdown();
            return r;
            };
            #define main(v) __BAH__main(v)
            #include <signal.h>
#include <string.h>
void RCP_decr(void * p);
void __BAH_panic(char * e,char * l);
char * __Bah_safe_string(char * s);
#define null (void *)0
#define true (char)1
#define false (char)0
long int __bah_strcmp(char * a,char * b){
if (((void *)a==null)) {
char * ____BAH_COMPILER_VAR_0 = a; a = "";RCP_decr(____BAH_COMPILER_VAR_0);
;
}
if (((void *)b==null)) {
char * ____BAH_COMPILER_VAR_1 = b; b = "";RCP_decr(____BAH_COMPILER_VAR_1);
;
}
long int ____BAH_COMPILER_VAR_2=strcmp(a,b);
return ____BAH_COMPILER_VAR_2;
};
#define strcmp __bah_strcmp
long int __bah_strlen(char * s){
if (((void *)s==null)) {
return 0;
}
long int ____BAH_COMPILER_VAR_3=strlen(s);
return ____BAH_COMPILER_VAR_3;
};
#define strlen __bah_strlen
#include <sys/mman.h>
#define SIZE_OF_INT 8
#define SIZE_OF_CHAR 1
#define SIZE_OF_INT32 4
#define SIZE_OF_FLOAT32 4
#define SIZE_OF_FLOAT 8
long int len(void * a){
if ((a==null)) {
return 0;
}
long int i = 0;
array(void*)*arr=a;
i=arr->length;
return i;
};
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void RCP_register(void * p,unsigned long int s);
void RCP_remove(void * p);
void RCP_setNewPtr(void * o,void * n);
void destroy(void * a){
RCP_remove(a);
free(a);
};
struct RCP {
void * p;
unsigned int c;
unsigned long int s;
void * e;
char str;
};
int cmp_rcp(void * a,void * b){
struct RCP* ar = a;
struct RCP* br = b;
if ((ar->p<br->p)) {
return -1;
}
else if ((ar->p>br->p)) {
return 1;
}
return 0;
};
struct RCPstate {
struct RCP* RCPs;
unsigned long int len;
unsigned long int size;
pthread_mutex_t lock;
void * heapMax;
void * heapMin;
unsigned long int(*getSize)(struct RCPstate* this,unsigned long int add);
void(*grow)(struct RCPstate* this,unsigned long int i);
void(*sort)(struct RCPstate* this);
unsigned long int(*rcpToIndex)(struct RCPstate* this,struct RCP* r);
void(*add)(struct RCPstate* this,struct RCP* r);
struct RCP*(*get)(struct RCPstate* this,unsigned long int i);
void(*set)(struct RCPstate* this,unsigned long int i,struct RCP* r);
struct RCP*(*getByPtr)(struct RCPstate* this,void * p);
void(*resize)(struct RCPstate* this,unsigned long int ns);
void(*remove)(struct RCPstate* this,unsigned long int i);
void(*lockMut)(struct RCPstate* this);
void(*unlockMut)(struct RCPstate* this);
};
unsigned long int RCPstate__getSize(struct RCPstate* this,unsigned long int add){
unsigned long int l = this->len+add;
return l*sizeof(struct RCP);
};
void RCPstate__grow(struct RCPstate* this,unsigned long int i){
unsigned long int rs = this->getSize(this,i+30);
void * nr = realloc(this->RCPs,rs);
if ((nr==null)) {
return;
}
this->size = rs;
this->RCPs = nr;
this->len = this->len+i;
};
void RCPstate__sort(struct RCPstate* this){
qsort(&this->RCPs[0],this->len,sizeof(struct RCP),cmp_rcp);
};
unsigned long int RCPstate__rcpToIndex(struct RCPstate* this,struct RCP* r){
long int i = (long int)r-(long int)&this->RCPs[0];
i = i/sizeof(struct RCP);
return i;
};
void RCPstate__add(struct RCPstate* this,struct RCP* r){
pthread_mutex_lock(&this->lock);
unsigned long int rs = this->getSize(this,1);
unsigned long int max = this->len-1;
if ((this->size<rs)) {
this->grow(this,1);
}
else {
this->len = this->len+1;
}
char done = false;
unsigned long int i = max;
while ((i>=0)) {
struct RCP* ar = &this->RCPs[i];
if ((ar->p<r->p)) {
unsigned long int j = max;
while ((j>i)) {
this->RCPs[j+1]=this->RCPs[j];
j = j-1;
};
this->RCPs[i+1]=*r;
done = true;
break;
}
i = i-1;
};
if ((done==false)) {
unsigned long int j = max;
while ((j>=0)) {
this->RCPs[j+1]=this->RCPs[j];
j = j-1;
};
this->RCPs[0]=*r;
}
pthread_mutex_unlock(&this->lock);
};
struct RCP* RCPstate__get(struct RCPstate* this,unsigned long int i){
if ((i>=this->len)) {
return null;
}
return &this->RCPs[i];
};
void RCPstate__set(struct RCPstate* this,unsigned long int i,struct RCP* r){
this->RCPs[i]=*r;
};
struct RCP* RCPstate__getByPtr(struct RCPstate* this,void * p){
if ((p<this->heapMin)||(p>this->heapMax)) {
return null;
}
return bsearch(&p,&this->RCPs[0],this->len,sizeof(struct RCP),cmp_rcp);
};
void RCPstate__resize(struct RCPstate* this,unsigned long int ns){
void * nr = realloc(this->RCPs,ns);
if ((nr==null)) {
return;
}
this->RCPs = nr;
this->size = ns;
};
void RCPstate__remove(struct RCPstate* this,unsigned long int i){
this->len = this->len-1;
while ((i<this->len)) {
this->RCPs[i]=this->RCPs[i+1];
i = i+1;
};
unsigned long int s = this->getSize(this,30);
if ((this->size-s>=this->size/2)) {
this->resize(this,s);
}
};
void RCPstate__lockMut(struct RCPstate* this){
pthread_mutex_lock(&this->lock);
};
void RCPstate__unlockMut(struct RCPstate* this){
pthread_mutex_unlock(&this->lock);
};
struct RCPstate RCPstate;
char DEBUG_RCP;
void RCP_init(){
struct RCPstate ____BAH_COMPILER_VAR_4 = {};
____BAH_COMPILER_VAR_4.RCPs = null;
____BAH_COMPILER_VAR_4.len = 0;
____BAH_COMPILER_VAR_4.size = 0;
____BAH_COMPILER_VAR_4.heapMax= null;
____BAH_COMPILER_VAR_4.heapMin= null;
____BAH_COMPILER_VAR_4.getSize = RCPstate__getSize;
____BAH_COMPILER_VAR_4.grow = RCPstate__grow;
____BAH_COMPILER_VAR_4.sort = RCPstate__sort;
____BAH_COMPILER_VAR_4.rcpToIndex = RCPstate__rcpToIndex;
____BAH_COMPILER_VAR_4.add = RCPstate__add;
____BAH_COMPILER_VAR_4.get = RCPstate__get;
____BAH_COMPILER_VAR_4.set = RCPstate__set;
____BAH_COMPILER_VAR_4.getByPtr = RCPstate__getByPtr;
____BAH_COMPILER_VAR_4.resize = RCPstate__resize;
____BAH_COMPILER_VAR_4.remove = RCPstate__remove;
____BAH_COMPILER_VAR_4.lockMut = RCPstate__lockMut;
____BAH_COMPILER_VAR_4.unlockMut = RCPstate__unlockMut;
RCPstate = ____BAH_COMPILER_VAR_4;
RCPstate.heapMin = -1;
RCPstate.heapMax = -1;
pthread_mutex_t l = RCPstate.lock;
pthread_mutex_init(&l,0);
};
void RCP_shutdown(){
pthread_mutex_t l = RCPstate.lock;
pthread_mutex_destroy(&l);
if ((RCPstate.len>0)) {
if ((DEBUG_RCP==true)) {
printf("\n\n[RCP] Leak detected!\n Summary: %d leaks (including global variables that are not freed at the end of the program).\n If your program is using self-referenced object (such as ropes), recompile-it without the '-rcp' flag.\n",RCPstate.len);
struct RCPstate* rcpStatep = &RCPstate;
long int i = 0;
for (; (i<RCPstate.len); i++) {
struct RCP* r = &rcpStatep->RCPs[i];
if ((r->p>=RCPstate.heapMin)&&(r->p<=RCPstate.heapMax)) {
printf("\t%p (%d reference(s))\n",r->p,r->c);
}
};
}
}
};
void cleanShutDown(){
RCP_shutdown();
exit(1);
};
char RCP_selfRef(void * a,void * b){
return (a==b);
};
void RCP_register(void * p,unsigned long int s){
if ((p==null)) {
return;
}
struct RCP ____BAH_COMPILER_VAR_5 = {};
____BAH_COMPILER_VAR_5.p = null;
____BAH_COMPILER_VAR_5.c = 0;
____BAH_COMPILER_VAR_5.s = 0;
____BAH_COMPILER_VAR_5.e = null;
#define r ____BAH_COMPILER_VAR_5
r.c = 1;
r.s = s;
r.p = p;
r.str = false;
RCPstate.add(&RCPstate,&r);

#undef r
};
void RCP_registerSTR(void * p,unsigned long int s){
if ((p==null)) {
return;
}
struct RCP ____BAH_COMPILER_VAR_6 = {};
____BAH_COMPILER_VAR_6.p = null;
____BAH_COMPILER_VAR_6.c = 0;
____BAH_COMPILER_VAR_6.s = 0;
____BAH_COMPILER_VAR_6.e = null;
#define r ____BAH_COMPILER_VAR_6
r.c = 1;
r.s = s;
r.p = p;
r.str = true;
RCPstate.add(&RCPstate,&r);

#undef r
};
void RCP_setNewPtr(void * o,void * n){
if ((o==null)||(n==null)||(o==n)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,o);
if ((r==null)) {
return;
}
r->p = n;
};
void RCP_remove(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
RCPstate.remove(&RCPstate,RCPstate.rcpToIndex(&RCPstate,r));
};
void RCP_scanRegion(void ** curr,void ** end,char decr);
void RCP_incr(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
r->c = r->c+1;
};
unsigned long int RCP_getCount(void * p){
if ((p==null)) {
return 0;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return 0;
}
return r->c;
};
char RCP_isAllocated(void * p){
if ((p==null)) {
return false;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return false;
}
return true;
};
void RCP_decr(void * p);
void RCP_incr(void * p);
void RCP_scanRegion(void ** curr,void ** end,char decr){
void ** from = curr;
while (((long int)curr<(long int)end)) {
void * b = *curr;
if ((b<=RCPstate.heapMax)&&(b>=RCPstate.heapMin)) {
if ((decr==true)) {
RCP_decr(b);
}
else {
RCP_incr(b);
}
}
curr = curr+1;
};
};
void RCP_decr(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
unsigned int orc = r->c;
r->c = r->c-1;
if ((r->c<=0)) {
if ((r->e!=null)) {
char changed = true;
void (*fn)(void *) = r->e;
fn(r->p);
}
struct RCP tmpr = *r;
RCPstate.remove(&RCPstate,RCPstate.rcpToIndex(&RCPstate,r));
if ((tmpr.str==false)&&(tmpr.s>=sizeof(void *))) {
void ** end = (long int)tmpr.p+tmpr.s;
RCP_scanRegion(tmpr.p,end,true);
}
free(tmpr.p);
}
};
void * RCP_incrIL(void ** p){
RCP_incr(*p);
return p;
};
void * RCP_decrIL(void ** p){
RCP_decr(*p);
return p;
};
struct RCP* RCP_request(void * p){
if ((p==null)) {
return null;
}
return RCPstate.getByPtr(&RCPstate,p);
};
void RCP_decrRCP(struct RCP* r){
if ((r==null)) {
return;
}
r = RCPstate.getByPtr(&RCPstate,r->p);
if ((r==null)) {
return;
}
r->c = r->c-1;
if ((r->c<=0)) {
if ((r->e!=null)) {
void (*fn)(void *) = r->e;
fn(r->p);
}
free(r->p);
RCPstate.remove(&RCPstate,RCPstate.rcpToIndex(&RCPstate,r));
}
};
void RCP_scanStack(void * p,unsigned long int s,char decr){
if ((p==null)) {
return;
}
void ** end = (long int)p+s;
RCP_scanRegion(p,end,decr);
};
void RCP_scanHeap(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
if ((r->c==1)) {
void ** end = (long int)p+r->s;
RCP_scanRegion(p,end,true);
}
RCP_decrRCP(r);
};
void * memoryAlloc(unsigned long int s){
void * r = malloc(s);
if ((r<RCPstate.heapMin)||(RCPstate.heapMin==-1)) {
RCPstate.heapMin = r;
}
if ((r>RCPstate.heapMax)) {
RCPstate.heapMax = r;
}
memset(r,0,s);
RCP_register(r,s);
return r;
};
char * memoryAllocSTR(unsigned long int s){
void * r = malloc(s);
if ((r<RCPstate.heapMin)||(RCPstate.heapMin==-1)) {
RCPstate.heapMin = r;
}
if ((r>RCPstate.heapMax)) {
RCPstate.heapMax = r;
}
memset(r,0,s);
RCP_registerSTR(r,s);
return r;
};
void * memoryRealloc(void * p,unsigned long int s){
struct RCP* or = RCP_request(p);
if ((or==null)||(or->c==0)) {
return memoryAlloc(s);
}
void * r = malloc(s);
if ((r<RCPstate.heapMin)||(RCPstate.heapMin==-1)) {
RCPstate.heapMin = r;
}
if ((r>RCPstate.heapMax)) {
RCPstate.heapMax = r;
}
unsigned long int ns = or->s;
if ((s<or->s)) {
ns = s;
}
memcpy(r,p,ns);
RCP_decrRCP(or);
RCP_register(r,s);
return r;
};
void clear(void * a){
if ((RCP_isAllocated(a)==false)) {
return;
}
array(void*)*arr=a;
RCP_decr(arr->data);
arr->data=memoryAlloc(sizeof(0));
arr->length=0;
};
void memoryOnEnd(void * obj,void * fn){
if ((obj==null)) {
return;
}
struct RCP* r = RCPstate.getByPtr(&RCPstate,obj);
if ((r==null)) {
return;
}
r->e = fn;
};
void append(void * a,void * b){
array(void*)*arrA=a;
array(void*)*arrB=b;
long int lenA = 0;
long int lenB = 0;
long int realSizeA = 0;
long int realSizeB = 0;
lenA=len(arrA);
lenB=len(arrB);
if ((lenB==0)) {
return;
}
if ((lenA==0)) {
arrA->data=arrB->data;
arrA->length=arrB->length;
return;
}
realSizeA=lenA*arrA->elemSize;
realSizeB=lenB*arrB->elemSize;
void * buff = memoryAlloc(realSizeA+realSizeB+32);
memcpy(buff,arrA->data,realSizeA);
memcpy(buff+lenA,arrB->data,realSizeB);
arrA->length=lenA+lenB;
arrA->data=buff;
RCP_decr(buff);
};
void copy(void * a,void * b){
array(void*)*arrA=a;
array(void*)*arrB=b;
long int lenB = 0;
long int realSizeB = 0;
lenB=len(arrB);
realSizeB=lenB*arrB->elemSize;
arrA->data=memoryAlloc(realSizeB);
memcpy(arrA->data,arrB->data,realSizeB);
arrA->length=arrB->length;
};
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_READWRITE 3
#define MAP_SHARED 1
#define MAP_ANONYMOUS 32
void * sharedMemory(long int size){
if ((size==0)) {
size = 4096;
}
void * r = mmap(0,size,PROT_READ+PROT_WRITE,MAP_SHARED+MAP_ANONYMOUS,-1,0);
void * ____BAH_COMPILER_VAR_7 = r;
return ____BAH_COMPILER_VAR_7;
};
void allocateArray(void * arr,long int nbElems){
array(void*)*a=arr;
a->length=nbElems;
a->data=memoryAlloc(nbElems*a->elemSize);
};
typedef array(char)* __BAH_ARR_TYPE_char;
__BAH_ARR_TYPE_char ser(void * a);
__BAH_ARR_TYPE_char __serialize(void * a,long int s){
char * r = memoryAlloc(s+9);
memcpy(r,&s,8);
memcpy(r+8,a,s);
long int l = s+1;
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
arr->length=s+8;
arr->elemSize=1;
arr->data=r;
array(char)* ____BAH_COMPILER_VAR_8 = arr;
RCP_decr(r);
return ____BAH_COMPILER_VAR_8;
};
long int serlen(__BAH_ARR_TYPE_char data){
array(char)* sarr = memoryAlloc(sizeof(array(char)));

sarr->length = 8;
sarr->elemSize = sizeof(char);
sarr->data = memoryAlloc(sizeof(char) * 50);sarr->data[0] = data->data[0];
sarr->data[1] = data->data[1];
sarr->data[2] = data->data[2];
sarr->data[3] = data->data[3];
sarr->data[4] = data->data[4];
sarr->data[5] = data->data[5];
sarr->data[6] = data->data[6];
sarr->data[7] = data->data[7];
void * ____BAH_COMPILER_VAR_9=*sarr->data;
RCP_decr(sarr);
return ____BAH_COMPILER_VAR_9;
};
void * unser(__BAH_ARR_TYPE_char data){
long int sptr = serlen(data);
void * r = memoryAlloc(sptr);
memcpy(r,data->data+8,sptr);
void * ____BAH_COMPILER_VAR_10 = r;
return ____BAH_COMPILER_VAR_10;
};
void delete(void * a,long int i){
array(void *)* arr = (array(void *)*)a;
long int length = len(arr);
if ((i>=length)||(i<0)) {
RCP_decr(arr);
return;
}
if ((length==1)) {
arr->length=0;
RCP_decr(arr);
return;
}
long int elemSize = arr->elemSize;
char* data = arr->data;
void * destOffset = elemSize*i;
i++;
void * offset = elemSize*i;
char* src = (long int)data+(long int)offset;
char* dest = (long int)data+(long int)destOffset;
long int rightNB = length-(i-1);
memmove(dest,src,rightNB*elemSize);
arr->length=length-1;
RCP_decr(arr);
RCP_decr(data);
RCP_decr(destOffset);
RCP_decr(offset);
RCP_decr(src);
RCP_decr(dest);
};
void deleteRange(void * a,long int from,long int to){
if ((from==to)) {
delete(a,from);
return;
}
array(void *)* arr = (array(void *)*)a;
long int length = len(arr);
long int elemSize = arr->elemSize;
char* data = arr->data;
long int size = elemSize*(to-from);
void * dest = (long int)data+elemSize*from;
void * src = (long int)dest+size+elemSize;
long int rightNB = length-to;
memmove(dest,src,rightNB*elemSize);
arr->length=length-(to-from+1);
RCP_decr(arr);
RCP_decr(data);
RCP_decr(dest);
RCP_decr(src);
};
char * arrToStr(__BAH_ARR_TYPE_char arr){
long int strLen = len(arr);
char * str = memoryAllocSTR(strLen+1);
memcpy(str,arr->data,strLen);
char * ____BAH_COMPILER_VAR_11 = str;
return ____BAH_COMPILER_VAR_11;
};
__BAH_ARR_TYPE_char strToArr(char * str){
long int strLen = strlen(str);
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
arr->data=memoryAlloc(strLen+1);
memcpy(arr->data,str,strLen);
arr->length=strLen;
array(char)* ____BAH_COMPILER_VAR_12 = arr;
return ____BAH_COMPILER_VAR_12;
};
char * arrAsStr(__BAH_ARR_TYPE_char arr){
RCP_incr(arr->data);
void * ____BAH_COMPILER_VAR_13=arr->data;
char * ____BAH_COMPILER_VAR_14 = ____BAH_COMPILER_VAR_13;
return ____BAH_COMPILER_VAR_14;
};
__BAH_ARR_TYPE_char strAsArr(char * str){
RCP_incr(str);
long int l = strlen(str);
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
arr->length=l;
arr->data=str;
array(char)* ____BAH_COMPILER_VAR_15 = arr;
return ____BAH_COMPILER_VAR_15;
};
void strTrimLeft(char ** s,long int i){
long int ls = strlen(*s);
char * ns = memoryAlloc(ls-i+1);
memcpy(ns,*s+i,ls-i);
*(char **)RCP_decrIL(&*s) = *(char **)RCP_incrIL(&ns);
RCP_decr(ns);
};
void strTrimRight(char ** s,long int i){
long int ls = strlen(*s);
char * ns = memoryAlloc(ls-i+1);
memcpy(ns,*s,ls-i);
*(char **)RCP_decrIL(&*s) = *(char **)RCP_incrIL(&ns);
RCP_decr(ns);
};
#define __bah_memory_realloc memoryRealloc
#define __bah_memory_str memoryAllocSTR
char * concatCPSTRING(char * a,char * b){
long int lenA = strlen(a);
long int lenB = strlen(b);
char * r = memoryAlloc(lenA+lenB+1);
strncpy(r,a,lenA);
strcat(r,b);
char * ____BAH_COMPILER_VAR_16 = r;
return ____BAH_COMPILER_VAR_16;
};
char * __STR(char * a){
long int lenA = strlen(a);
char * r = memoryAllocSTR(lenA+1);
memcpy(r,a,lenA);
char * ____BAH_COMPILER_VAR_17 = r;
return ____BAH_COMPILER_VAR_17;
};
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void print(char * s){
write((void *)1,s,strlen(s));
};
void * cArr(void * arr){
array(void*)*a=arr;
void * ____BAH_COMPILER_VAR_18=a->data;
void * ____BAH_COMPILER_VAR_19 = ____BAH_COMPILER_VAR_18;
return ____BAH_COMPILER_VAR_19;
};
char __checkString(char * s,char * l){
if (((void *)s==null)) {
char * ____BAH_COMPILER_VAR_20 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(l);
long int strLen_1 = strlen(") is null \n");
long int strLen_2 = strlen("cpstring (");
;                            
            ____BAH_COMPILER_VAR_20 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_20+currStrOff, "cpstring (", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_20+currStrOff, l, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_20+currStrOff, ") is null \n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_20);
exit(1);
RCP_decr(____BAH_COMPILER_VAR_20);
}
return true;
};
#include <pthread.h>
#define __thread_create pthread_create
#define __thread_join pthread_join
#define currentThread pthread_self
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
struct mutexCondition {
pthread_cond_t id;
void(*init)(struct mutexCondition* this);
void(*wait)(struct mutexCondition* this,struct mutex m);
void(*send)(struct mutexCondition* this);
void(*destroy)(struct mutexCondition* this);
};
void mutexCondition__init(struct mutexCondition* this){
pthread_cond_init(&this->id,0);
};
void mutexCondition__wait(struct mutexCondition* this,struct mutex m){
pthread_mutex_t mid = m.id;
pthread_cond_wait(&this->id,&mid);
};
void mutexCondition__send(struct mutexCondition* this){
pthread_cond_signal(&this->id);
};
void mutexCondition__destroy(struct mutexCondition* this){
pthread_cond_destroy(&this->id);
};
struct mutexCondition mutexCondition(){
struct mutexCondition ____BAH_COMPILER_VAR_21 = {};
____BAH_COMPILER_VAR_21.init = mutexCondition__init;
____BAH_COMPILER_VAR_21.wait = mutexCondition__wait;
____BAH_COMPILER_VAR_21.send = mutexCondition__send;
____BAH_COMPILER_VAR_21.destroy = mutexCondition__destroy;
#define m ____BAH_COMPILER_VAR_21
m.init(&m);
struct mutexCondition ____BAH_COMPILER_VAR_22 = m;

#undef m
return ____BAH_COMPILER_VAR_22;
};
struct thread {
pthread_t id;
void (*handle)(void *);
void(*create)(struct thread* this);
void(*createWithArg)(struct thread* this,void * arg);
void(*wait)(struct thread* this);
};
void thread__create(struct thread* this){
__thread_create(&this->id,null,this->handle,null);
};
void thread__createWithArg(struct thread* this,void * arg){
__thread_create(&this->id,null,this->handle,arg);
};
void thread__wait(struct thread* this){
__thread_join(this->id,null);
};
struct mutex mutex(){
struct mutex ____BAH_COMPILER_VAR_23 = {};
____BAH_COMPILER_VAR_23.init = mutex__init;
____BAH_COMPILER_VAR_23.lock = mutex__lock;
____BAH_COMPILER_VAR_23.unlock = mutex__unlock;
____BAH_COMPILER_VAR_23.destroy = mutex__destroy;
#define m ____BAH_COMPILER_VAR_23
m.init(&m);
struct mutex ____BAH_COMPILER_VAR_24 = m;

#undef m
return ____BAH_COMPILER_VAR_24;
};
struct queueNode {
long int key;
void * data;
struct queueNode* next;
struct queueNode* prev;
};
struct queue {
long int length;
struct queueNode* head;
struct queueNode* end;
void(*insert)(struct queue* this,void * data);
void(*delete)(struct queue* this,long int key);
void *(*get)(struct queue* this,long int key);
void(*set)(struct queue* this,long int key,void * data);
void *(*pop)(struct queue* this);
void(*clear)(struct queue* this);
};
void queue__insert(struct queue* this,void * data){
struct queueNode* ____BAH_COMPILER_VAR_25 = memoryAlloc(sizeof(struct queueNode));
____BAH_COMPILER_VAR_25->data= null;
____BAH_COMPILER_VAR_25->next= null;
____BAH_COMPILER_VAR_25->prev= null;
____BAH_COMPILER_VAR_25->key = this->length;
____BAH_COMPILER_VAR_25->data = data;
____BAH_COMPILER_VAR_25->prev = this->end;
struct queueNode* node = *(struct queueNode**)RCP_incrIL(&____BAH_COMPILER_VAR_25);
this->length++;
if ((this->end==null)) {
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&node);
*(struct queueNode**)RCP_decrIL(&this->end) = *(struct queueNode**)RCP_incrIL(&this->head);
}
else {
*(struct queueNode**)RCP_decrIL(&this->end->next) = *(struct queueNode**)RCP_incrIL(&node);
*(struct queueNode**)RCP_decrIL(&this->end) = *(struct queueNode**)RCP_incrIL(&node);
}
RCP_decr(____BAH_COMPILER_VAR_25);
RCP_decr(node);
};
void queue__delete(struct queue* this,long int key){
if ((this->length==0)) {
return;
}
struct queueNode* current = *(struct queueNode**)RCP_incrIL(&this->head);
struct queueNode* previous= null;
while ((current->key!=key)) {
if ((current->next==null)) {
RCP_decr(current);
RCP_decr(previous);
return;
}
*(struct queueNode**)RCP_decrIL(&previous) = *(struct queueNode**)RCP_incrIL(&current);
*(struct queueNode**)RCP_decrIL(&current) = *(struct queueNode**)RCP_incrIL(&current->next);
};
if ((current==this->head)) {
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&current->next);
}
else {
*(struct queueNode**)RCP_decrIL(&previous->next) = *(struct queueNode**)RCP_incrIL(&current->next);
}
this->length = this->length-1;
RCP_decr(current);
RCP_decr(previous);
};
void * queue__get(struct queue* this,long int key){
long int z = 0;
void * zp = (void *)z;
if ((this->length==0)) {
void * ____BAH_COMPILER_VAR_26 = zp;
return ____BAH_COMPILER_VAR_26;
}
struct queueNode* ptr = *(struct queueNode**)RCP_incrIL(&this->head);
while ((ptr->key!=key)) {
if ((ptr->next==null)) {
void * ____BAH_COMPILER_VAR_27 = zp;
RCP_decr(ptr);
return ____BAH_COMPILER_VAR_27;
}
*(struct queueNode**)RCP_decrIL(&ptr) = *(struct queueNode**)RCP_incrIL(&ptr->next);
};
void * data = *(void **)RCP_incrIL(&ptr->data);
void * ____BAH_COMPILER_VAR_28 = data;
RCP_decr(zp);
RCP_decr(ptr);
return ____BAH_COMPILER_VAR_28;
};
void queue__set(struct queue* this,long int key,void * data){
this->delete(this,key);
struct queueNode* ____BAH_COMPILER_VAR_29 = memoryAlloc(sizeof(struct queueNode));
____BAH_COMPILER_VAR_29->data= null;
____BAH_COMPILER_VAR_29->next= null;
____BAH_COMPILER_VAR_29->prev= null;
struct queueNode* node = *(struct queueNode**)RCP_incrIL(&____BAH_COMPILER_VAR_29);
node->key = key;
*(void **)RCP_decrIL(&node->data) = *(void **)RCP_incrIL(&data);
*(struct queueNode**)RCP_decrIL(&node->next) = *(struct queueNode**)RCP_incrIL(&this->head);
this->length = this->length+1;
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&node);
RCP_decr(____BAH_COMPILER_VAR_29);
RCP_decr(node);
};
void * queue__pop(struct queue* this){
if ((this->head==null)) {
void * ____BAH_COMPILER_VAR_30 = null;
RCP_incr(null);return ____BAH_COMPILER_VAR_30;
}
void * data = *(void **)RCP_incrIL(&this->head->data);
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&this->head->next);
if ((this->head==null)) {
struct queueNode* ____BAH_COMPILER_VAR_31 = this->end; this->end = null;RCP_decr(____BAH_COMPILER_VAR_31);
;
}
this->length--;
void * ____BAH_COMPILER_VAR_32 = data;
return ____BAH_COMPILER_VAR_32;
};
void queue__clear(struct queue* this){
struct queueNode* ____BAH_COMPILER_VAR_33 = this->head; this->head = (void *)0;RCP_decr(____BAH_COMPILER_VAR_33);
;
this->length = 0;
};
struct channel {
pthread_mutex_t m_mut;
pthread_cond_t w_cond;
pthread_cond_t r_cond;
long int w_waitting;
long int r_waitting;
struct queue* queue;
long int cap;
void(*send)(struct channel* this,void * data);
void(*sendAny)(struct channel* this,void * data,long int len);
void *(*receive)(struct channel* this);
void(*destroy)(struct channel* this);
long int(*len)(struct channel* this);
};
void channel__send(struct channel* this,void * data){
pthread_mutex_lock(&this->m_mut);
if ((this->cap!=-1)) {
while ((this->queue->length==this->cap)) {
this->w_waitting++;
pthread_cond_wait(&this->w_cond,&this->m_mut);
this->w_waitting--;
};
}
this->queue->insert(this->queue,data);
if ((this->r_waitting>0)) {
pthread_cond_signal(&this->r_cond);
}
pthread_mutex_unlock(&this->m_mut);
};
void channel__sendAny(struct channel* this,void * data,long int len){
pthread_mutex_lock(&this->m_mut);
if ((this->cap!=-1)) {
while ((this->queue->length==this->cap)) {
this->w_waitting++;
pthread_cond_wait(&this->w_cond,&this->m_mut);
this->w_waitting--;
};
}
void * p = memoryAlloc(len);
memcpy(p,data,len);
this->queue->insert(this->queue,p);
if ((this->r_waitting>0)) {
pthread_cond_signal(&this->r_cond);
}
pthread_mutex_unlock(&this->m_mut);
RCP_decr(p);
};
void * channel__receive(struct channel* this){
pthread_mutex_lock(&this->m_mut);
while ((this->queue->length==0)) {
this->r_waitting++;
pthread_cond_wait(&this->r_cond,&this->m_mut);
this->r_waitting--;
};
void * data = this->queue->pop(this->queue);
if ((this->w_waitting>0)) {
pthread_cond_signal(&this->w_cond);
}
pthread_mutex_unlock(&this->m_mut);
void * ____BAH_COMPILER_VAR_34 = data;
return ____BAH_COMPILER_VAR_34;
};
void channel__destroy(struct channel* this){
pthread_mutex_destroy(&this->m_mut);
pthread_cond_destroy(&this->w_cond);
pthread_cond_destroy(&this->r_cond);
};
long int channel__len(struct channel* this){
long int l = this->queue->length;
return l;
};
struct channel* channel(){
struct channel* ____BAH_COMPILER_VAR_35 = memoryAlloc(sizeof(struct channel));
____BAH_COMPILER_VAR_35->w_waitting = 0;
____BAH_COMPILER_VAR_35->r_waitting = 0;
____BAH_COMPILER_VAR_35->queue= null;
____BAH_COMPILER_VAR_35->cap = -1;
____BAH_COMPILER_VAR_35->send = channel__send;
____BAH_COMPILER_VAR_35->sendAny = channel__sendAny;
____BAH_COMPILER_VAR_35->receive = channel__receive;
____BAH_COMPILER_VAR_35->destroy = channel__destroy;
____BAH_COMPILER_VAR_35->len = channel__len;
struct channel* c = *(struct channel**)RCP_incrIL(&____BAH_COMPILER_VAR_35);
pthread_mutex_init(&c->m_mut,0);
pthread_cond_init(&c->w_cond,0);
pthread_cond_init(&c->r_cond,0);
struct queue* ____BAH_COMPILER_VAR_36 = memoryAlloc(sizeof(struct queue));
____BAH_COMPILER_VAR_36->length = 0;
____BAH_COMPILER_VAR_36->head = null;
____BAH_COMPILER_VAR_36->end = null;
____BAH_COMPILER_VAR_36->insert = queue__insert;
____BAH_COMPILER_VAR_36->delete = queue__delete;
____BAH_COMPILER_VAR_36->get = queue__get;
____BAH_COMPILER_VAR_36->set = queue__set;
____BAH_COMPILER_VAR_36->pop = queue__pop;
____BAH_COMPILER_VAR_36->clear = queue__clear;
*(struct queue**)RCP_decrIL(&c->queue) = *(struct queue**)RCP_incrIL(&____BAH_COMPILER_VAR_36);
struct channel* ____BAH_COMPILER_VAR_37 = c;
RCP_decr(____BAH_COMPILER_VAR_35);
RCP_decr(____BAH_COMPILER_VAR_36);
return ____BAH_COMPILER_VAR_37;
};
void setChanCap(void * c,long int cap){
struct channel* cp = *(struct channel**)RCP_incrIL(&c);
cp->cap = cap;
RCP_decr(cp);
};
struct channel * __BAH_panic_chan;
void __Bah_common_panic(char * e){
if (strlen(e)) {
print(e);
print("\n");
cleanShutDown();
}
};
#define panic __Bah_common_panic
struct __Bah_fnName_mapper {
void * p;
char * n;
};
array(struct __Bah_fnName_mapper)* __Bah_fnNames;
void __Bah_fnNames_append(struct __Bah_fnName_mapper fnn){

{
long nLength = len(__Bah_fnNames);
if (__Bah_fnNames->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(__Bah_fnNames->data, (nLength+50)*sizeof(struct __Bah_fnName_mapper));
__Bah_fnNames->data = newPtr;
}
__Bah_fnNames->data[len(__Bah_fnNames)] = fnn; RCP_scanStack(&fnn, sizeof(fnn), 0);
__Bah_fnNames->length = nLength+1;
} else {
RCP_scanStack(&__Bah_fnNames->data[len(__Bah_fnNames)], sizeof(__Bah_fnNames->data[len(__Bah_fnNames)]), 1); __Bah_fnNames->data[len(__Bah_fnNames)] = fnn; RCP_scanStack(&fnn, sizeof(fnn), 0);
}
};
};
long int backtrace(void * arr,long int l);
void __BAH_panic(char * e,char * line){
if ((__BAH_panic_chan!=null)) {
__BAH_panic_chan->send(__BAH_panic_chan, e);
return;
}
char * ____BAH_COMPILER_VAR_38 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(e);
long int strLen_1 = strlen("\n");
long int strLen_2 = strlen("): ");
long int strLen_3 = strlen(line);
long int strLen_4 = strlen("panic (");
;                            
            ____BAH_COMPILER_VAR_38 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2+strLen_3+strLen_4);
            
                    memcpy(____BAH_COMPILER_VAR_38+currStrOff, "panic (", strLen_4);
                    currStrOff += strLen_4;
                    
                    memcpy(____BAH_COMPILER_VAR_38+currStrOff, line, strLen_3);
                    currStrOff += strLen_3;
                    
                    memcpy(____BAH_COMPILER_VAR_38+currStrOff, "): ", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_38+currStrOff, e, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_38+currStrOff, "\n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_38);
array(void *)* arr = memoryAlloc(sizeof(array(void *)));

arr->length = 0;
arr->elemSize = sizeof(void *);
allocateArray(arr,10);
long int size = backtrace(arr->data,10);
print("Backtrace:\n");
long int min = -1;
long int max = -1;
long int i = 1;
for (; (i<size); i++) {
long int p = arr->data[i];
struct __Bah_fnName_mapper closest;
long int dist = -1;
long int j = 0;
for (; (j<len(__Bah_fnNames)); j++) {
struct __Bah_fnName_mapper fnn = __Bah_fnNames->data[j]; RCP_scanStack(&__Bah_fnNames->data[j], sizeof(__Bah_fnNames->data[j]), 0);
long int fnp = fnn.p;
if ((fnp<min)||(min==-1)) {
min = fnp;
}
if ((fnp>max)||(max==-1)) {
max = fnp;
}
if ((p>fnp)) {
if ((dist==-1)||(p-fnp<dist)) {
dist = p-fnp;
RCP_scanStack(&closest, sizeof(closest), 1); closest = fnn; RCP_scanStack(&fnn, sizeof(fnn), 0);
}
}
RCP_scanStack(&fnn, sizeof(fnn), 1);
};
if ((dist==-1)) {
print("\t???\n");
RCP_scanStack(&closest, sizeof(closest), 1);
continue;
}
char * status = "";
long int fnp = closest.p;
if ((min==fnp)||(max==fnp)) {
if ((dist>10000)) {
RCP_scanStack(&closest, sizeof(closest), 1);
RCP_decr(status);
continue;
}
char * ____BAH_COMPILER_VAR_39 = status; status = "?";RCP_decr(____BAH_COMPILER_VAR_39);
;
}
char * ____BAH_COMPILER_VAR_40 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(status);
long int strLen_1 = strlen(" \n");
long int strLen_2 = strlen("() ");
long int strLen_3 = strlen(closest.n);
long int strLen_4 = strlen("\t");
;                            
            ____BAH_COMPILER_VAR_40 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2+strLen_3+strLen_4);
            
                    memcpy(____BAH_COMPILER_VAR_40+currStrOff, "\t", strLen_4);
                    currStrOff += strLen_4;
                    
                    memcpy(____BAH_COMPILER_VAR_40+currStrOff, closest.n, strLen_3);
                    currStrOff += strLen_3;
                    
                    memcpy(____BAH_COMPILER_VAR_40+currStrOff, "() ", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_40+currStrOff, status, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_40+currStrOff, " \n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_40);
if ((strcmp(closest.n, "main") == 0)) {
RCP_scanStack(&closest, sizeof(closest), 1);
RCP_decr(status);
RCP_decr(____BAH_COMPILER_VAR_40);
break;
}
RCP_scanStack(&closest, sizeof(closest), 1);
RCP_decr(status);
RCP_decr(____BAH_COMPILER_VAR_40);
};
cleanShutDown();
RCP_decr(____BAH_COMPILER_VAR_38);
RCP_decr(arr);
};
char * (*onMemoryError)();
void __Bah_segfault_handle(long int sig){
char * res = "";
if ((onMemoryError!=null)) {
char * ____BAH_COMPILER_VAR_41 = res; res = onMemoryError();RCP_decr(____BAH_COMPILER_VAR_41);
;
}
char * ____BAH_COMPILER_VAR_42 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen("Memory error (segfault).\n");
long int strLen_1 = strlen(res);
;                            
            ____BAH_COMPILER_VAR_42 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_42+currStrOff, "Memory error (segfault).\n", strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_42+currStrOff, res, strLen_1);
            currStrOff += strLen_1;
        
        }__BAH_panic(____BAH_COMPILER_VAR_42,"???");
RCP_decr(res);
RCP_decr(____BAH_COMPILER_VAR_42);
};
char __Bah_init_segfaultHandle(){
signal(SIGSEGV,__Bah_segfault_handle);
return true;
};
char __Bah_init_segfaultHandle_OK;
char recover(char ** s){
struct channel * ____BAH_COMPILER_VAR_43 = __BAH_panic_chan; __BAH_panic_chan = channel();RCP_decr(____BAH_COMPILER_VAR_43);
;
char * err = (char *)__BAH_panic_chan->receive(__BAH_panic_chan);
if ((s!=null)) {
*(char **)RCP_decrIL(&*s) = *(char **)RCP_incrIL(&err);
}
RCP_decr(err);
return true;
};
char * __Bah_safe_string(char * s){
if (((void *)s==null)) {
char * ____BAH_COMPILER_VAR_44 = "(nil)";
return ____BAH_COMPILER_VAR_44;
}
if ((strlen(s)>50)) {
RCP_incr(s);char * ____BAH_COMPILER_VAR_45 = s; s = __STR(s);RCP_decr(____BAH_COMPILER_VAR_45);
;
array(char)* a = strAsArr(s);

{
long nLength = 47;
if (a->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(a->data, (nLength+50)*sizeof(char));
a->data = newPtr;
}
a->data[47] = 46;
a->length = nLength+1;
} else {
a->data[47] = 46;
}
};

{
long nLength = 48;
if (a->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(a->data, (nLength+50)*sizeof(char));
a->data = newPtr;
}
a->data[48] = 46;
a->length = nLength+1;
} else {
a->data[48] = 46;
}
};

{
long nLength = 49;
if (a->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(a->data, (nLength+50)*sizeof(char));
a->data = newPtr;
}
a->data[49] = 46;
a->length = nLength+1;
} else {
a->data[49] = 46;
}
};

{
long nLength = 50;
if (a->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(a->data, (nLength+50)*sizeof(char));
a->data = newPtr;
}
a->data[50] = (char)0;
a->length = nLength+1;
} else {
a->data[50] = (char)0;
}
};
RCP_decr(a);
}
char * ____BAH_COMPILER_VAR_46 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(s);
long int strLen_1 = strlen("\"");
long int strLen_2 = strlen("\"");
;                            
            ____BAH_COMPILER_VAR_46 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_46+currStrOff, "\"", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_46+currStrOff, s, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_46+currStrOff, "\"", strLen_1);
            currStrOff += strLen_1;
        
        }char * ____BAH_COMPILER_VAR_47 = ____BAH_COMPILER_VAR_46;
RCP_decr(____BAH_COMPILER_VAR_46);
return ____BAH_COMPILER_VAR_47;
};
char cpstringCharAt(char * s,long int i){
char c = (char)0;
c=s[i];
return c;
};
char * cpstringSubsitute(char * s,long int i,long int l){
long int size = l-i;
char * ns = memoryAllocSTR(size+1);
memcpy(ns,s+i,size);
char * ____BAH_COMPILER_VAR_48 = ns;
return ____BAH_COMPILER_VAR_48;
};
typedef array(void *)* __BAH_ARR_TYPE_ptr;
void * arraySubstitute(__BAH_ARR_TYPE_ptr arr,long int i,long int l){
long int length = l-i;
long int offset = i*arr->elemSize;
array(void *)* na = memoryAlloc(sizeof(array(void *)));

na->length = 0;
na->elemSize = sizeof(void *);
na->elemSize=arr->elemSize;
na->length=length;
long int allocLength = length;
if ((length>50)) {
allocLength = allocLength+allocLength%50;
}
else {
allocLength = 50;
}
long int size = allocLength*arr->elemSize;
long int realSize = length*arr->elemSize;
void * data = memoryAlloc(size);
char * oData = arr->data;
memcpy(data,oData+offset,realSize);
na->data=data;
void * ____BAH_COMPILER_VAR_49 = na;
RCP_decr(data);
RCP_decr(oData);
return ____BAH_COMPILER_VAR_49;
};
long int __Bah_map_hash(char * s,long int l){
long int hash = 5381;
long int i = 0;
for (; (i<strlen(s)); i++) {
hash = ((long int)hash<<5+0)+hash+(long int)s[i];
};
if ((hash<0)) {
hash = 0-hash;
}
return hash%l;
};
struct mapElem {
char * key;
void * val;
};
struct mapWrapper {
array(struct mapElem*)* elems;
long int length;
void(*grow)(struct mapWrapper* this,long int nb);
void(*set)(struct mapWrapper* this,char * k,void * e);
void(*setAny)(struct mapWrapper* this,char * k,void * e,long int s);
void(*delete)(struct mapWrapper* this,char * k);
void *(*get)(struct mapWrapper* this,char * k);
};
void mapWrapper__grow(struct mapWrapper* this,long int nb){
long int l = len(this->elems);
long int i = l;
for (; (i<l+nb); i++) {

{
long nLength = i;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
struct mapElem* ____BAH_COMPILER_VAR_50 = this->elems->data[i]; this->elems->data[i] = null;RCP_decr(____BAH_COMPILER_VAR_50);
;
this->elems->length = nLength+1;
} else {
struct mapElem* ____BAH_COMPILER_VAR_50 = this->elems->data[i]; this->elems->data[i] = null;RCP_decr(____BAH_COMPILER_VAR_50);
;
}
};
};
};
void mapWrapper__set(struct mapWrapper* this,char * k,void * e){
if ((this->length*2>=len(this->elems))) {
this->grow(this,this->length);
}
struct mapElem* ____BAH_COMPILER_VAR_51 = memoryAlloc(sizeof(struct mapElem));
____BAH_COMPILER_VAR_51->key= null;
____BAH_COMPILER_VAR_51->val= null;
____BAH_COMPILER_VAR_51->key = k;
____BAH_COMPILER_VAR_51->val = e;
struct mapElem* elem = *(struct mapElem**)RCP_incrIL(&____BAH_COMPILER_VAR_51);
long int ind = __Bah_map_hash(k,len(this->elems));
long int i = 0;
for (; (i<len(this->elems)); i++) {
long int j = (i+ind)%len(this->elems);
struct mapElem* ce = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((ce==null)) {

{
long nLength = j;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
this->elems->length = nLength+1;
} else {
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
}
};
this->length++;
RCP_decr(ce);
break;
}
else if ((strcmp(ce->key, k) == 0)) {

{
long nLength = j;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
this->elems->length = nLength+1;
} else {
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
}
};
RCP_decr(ce);
break;
}
RCP_decr(ce);
};
RCP_decr(____BAH_COMPILER_VAR_51);
RCP_decr(elem);
};
void mapWrapper__setAny(struct mapWrapper* this,char * k,void * e,long int s){
if ((this->length==0)) {
this->grow(this,50);
}
if ((this->length*2>=len(this->elems))) {
this->grow(this,this->length);
}
void * p = memoryAlloc(s);
memcpy(p,e,s);
struct mapElem* ____BAH_COMPILER_VAR_52 = memoryAlloc(sizeof(struct mapElem));
____BAH_COMPILER_VAR_52->key= null;
____BAH_COMPILER_VAR_52->val= null;
____BAH_COMPILER_VAR_52->key = k;
____BAH_COMPILER_VAR_52->val = p;
struct mapElem* elem = *(struct mapElem**)RCP_incrIL(&____BAH_COMPILER_VAR_52);
long int ind = __Bah_map_hash(k,len(this->elems));
long int i = 0;
for (; (i<len(this->elems)); i++) {
long int j = (i+ind)%len(this->elems);
struct mapElem* ce = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((ce==null)) {

{
long nLength = j;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
this->elems->length = nLength+1;
} else {
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
}
};
this->length++;
RCP_decr(ce);
break;
}
else if ((strcmp(ce->key, k) == 0)) {

{
long nLength = j;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
this->elems->length = nLength+1;
} else {
*(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
}
};
RCP_decr(ce);
break;
}
RCP_decr(ce);
};
RCP_decr(p);
RCP_decr(____BAH_COMPILER_VAR_52);
RCP_decr(elem);
};
void mapWrapper__delete(struct mapWrapper* this,char * k){
long int ind = __Bah_map_hash(k,len(this->elems));
long int i = 0;
for (; (i<len(this->elems)); i++) {
long int j = (i+ind)%len(this->elems);
struct mapElem* e = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((e!=null)&&(strcmp(e->key, k) == 0)) {

{
long nLength = j;
if (this->elems->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(this->elems->data, (nLength+50)*sizeof(struct mapElem*));
this->elems->data = newPtr;
}
struct mapElem* ____BAH_COMPILER_VAR_53 = this->elems->data[j]; this->elems->data[j] = null;RCP_decr(____BAH_COMPILER_VAR_53);
;
this->elems->length = nLength+1;
} else {
struct mapElem* ____BAH_COMPILER_VAR_53 = this->elems->data[j]; this->elems->data[j] = null;RCP_decr(____BAH_COMPILER_VAR_53);
;
}
};
}
RCP_decr(e);
};
};
void * mapWrapper__get(struct mapWrapper* this,char * k){
long int ind = __Bah_map_hash(k,len(this->elems));
long int i = 0;
for (; (i<len(this->elems)); i++) {
long int j = (i+ind)%len(this->elems);
struct mapElem* e = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((e!=null)&&(strcmp(e->key, k) == 0)) {
void * ____BAH_COMPILER_VAR_54 = e->val;
RCP_incr(e->val);RCP_decr(e);
return ____BAH_COMPILER_VAR_54;
}
RCP_decr(e);
};
void * ____BAH_COMPILER_VAR_55 = null;
RCP_incr(null);return ____BAH_COMPILER_VAR_55;
};
struct mapWrapper* mapWrapper(){
struct mapWrapper* ____BAH_COMPILER_VAR_56 = memoryAlloc(sizeof(struct mapWrapper));
____BAH_COMPILER_VAR_56->elems = memoryAlloc(sizeof(array(struct mapElem*)));
            ____BAH_COMPILER_VAR_56->elems->length = 0;
            ____BAH_COMPILER_VAR_56->elems->elemSize = sizeof(struct mapElem*);
            ____BAH_COMPILER_VAR_56->grow = mapWrapper__grow;
____BAH_COMPILER_VAR_56->set = mapWrapper__set;
____BAH_COMPILER_VAR_56->setAny = mapWrapper__setAny;
____BAH_COMPILER_VAR_56->delete = mapWrapper__delete;
____BAH_COMPILER_VAR_56->get = mapWrapper__get;
struct mapWrapper* m = *(struct mapWrapper**)RCP_incrIL(&____BAH_COMPILER_VAR_56);
m->grow(m,50);
struct mapWrapper* ____BAH_COMPILER_VAR_57 = m;
RCP_decr(____BAH_COMPILER_VAR_56);
return ____BAH_COMPILER_VAR_57;
};
long int backtrace(void * arr,long int l){
return 0;
};
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
char * stdinput(){
char * buff = memoryAlloc(1025);
char * response = "";
long int nDataLength = read((void *)0,buff,1024);
if ((nDataLength<1024)) {
char * ____BAH_COMPILER_VAR_58 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(response);
long int strLen_1 = strlen(buff);
;                            
            ____BAH_COMPILER_VAR_58 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_58+currStrOff, response, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_58+currStrOff, buff, strLen_1);
            currStrOff += strLen_1;
        
        }char * ____BAH_COMPILER_VAR_59 = response; response = ____BAH_COMPILER_VAR_58;RCP_decr(____BAH_COMPILER_VAR_59);
;
RCP_decr(____BAH_COMPILER_VAR_58);
}
else {
while ((nDataLength>0)) {
char * ____BAH_COMPILER_VAR_60 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(response);
long int strLen_1 = strlen(buff);
;                            
            ____BAH_COMPILER_VAR_60 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_60+currStrOff, response, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_60+currStrOff, buff, strLen_1);
            currStrOff += strLen_1;
        
        }char * ____BAH_COMPILER_VAR_61 = response; response = ____BAH_COMPILER_VAR_60;RCP_decr(____BAH_COMPILER_VAR_61);
;
if ((nDataLength<1024)) {
long int trimAmm = 1024-nDataLength;
strTrimRight(&response,trimAmm);
RCP_decr(____BAH_COMPILER_VAR_60);
break;
}
else {
nDataLength = read((void *)0,buff,1024);
}
RCP_decr(____BAH_COMPILER_VAR_60);
};
}
strTrimRight(&response,1);
char * ____BAH_COMPILER_VAR_62 = response;
RCP_decr(buff);
return ____BAH_COMPILER_VAR_62;
};
void println(char * s){
char * ____BAH_COMPILER_VAR_63 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(s);
long int strLen_1 = strlen("\n");
;                            
            ____BAH_COMPILER_VAR_63 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_63+currStrOff, s, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_63+currStrOff, "\n", strLen_1);
            currStrOff += strLen_1;
        
        }write((void *)1,____BAH_COMPILER_VAR_63,strlen(s)+1);
RCP_decr(____BAH_COMPILER_VAR_63);
};
struct fileStream {
FILE* handle;
char * name;
long int(*isValid)(struct fileStream* this);
void(*open)(struct fileStream* this,char * path,char * mode);
void(*close)(struct fileStream* this);
long int(*getPos)(struct fileStream* this);
void(*setPos)(struct fileStream* this,long int i);
long int(*getSize)(struct fileStream* this);
void(*rewind)(struct fileStream* this);
char(*getChar)(struct fileStream* this);
void(*setChar)(struct fileStream* this,char c);
void(*createFile)(struct fileStream* this,char * path);
long int(*writeFile)(struct fileStream* this,char * content);
void(*writePtr)(struct fileStream* this,void * a,long int s);
long int(*readPtr)(struct fileStream* this,void * a,long int s);
char *(*readContent)(struct fileStream* this);
array(char)*(*readBytes)(struct fileStream* this);
void(*writeBytes)(struct fileStream* this,array(char)* d);
void(*_end)(struct fileStream* this);
};
long int fileStream__isValid(struct fileStream* this){
if ((this->handle==null)) {
return 0;
}
return 1;
};
void fileStream__open(struct fileStream* this,char * path,char * mode){
*(char **)RCP_decrIL(&this->name) = *(char **)RCP_incrIL(&path);
FILE* ____BAH_COMPILER_VAR_64 = this->handle; this->handle = fopen(path,mode);RCP_decr(____BAH_COMPILER_VAR_64);
;
};
void fileStream__close(struct fileStream* this){
if ((this->isValid(this)==0)) {
return;
}
fclose(this->handle);
FILE* ____BAH_COMPILER_VAR_65 = this->handle; this->handle = null;RCP_decr(____BAH_COMPILER_VAR_65);
;
};
long int fileStream__getPos(struct fileStream* this){
if ((this->isValid(this)==0)) {
return 0;
}
long int ____BAH_COMPILER_VAR_66=ftell(this->handle);
return ____BAH_COMPILER_VAR_66;
};
void fileStream__setPos(struct fileStream* this,long int i){
if ((this->isValid(this)==0)) {
return;
}
fseek(this->handle,i,0);
};
long int fileStream__getSize(struct fileStream* this){
if ((this->isValid(this)==0)) {
return -1;
}
long int oldPos = this->getPos(this);
fseek(this->handle,0,2);
long int size = ftell(this->handle);
this->setPos(this,oldPos);
return size;
};
void fileStream__rewind(struct fileStream* this){
rewind(this->handle);
};
char fileStream__getChar(struct fileStream* this){
char c = getc(this->handle);
return c;
};
void fileStream__setChar(struct fileStream* this,char c){
fputc(c,this->handle);
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
void fileStream__writePtr(struct fileStream* this,void * a,long int s){
fwrite(a,s,1,this->handle);
};
long int fileStream__readPtr(struct fileStream* this,void * a,long int s){
long int ____BAH_COMPILER_VAR_67=fread(a,s,1,this->handle);
return ____BAH_COMPILER_VAR_67;
};
char * fileStream__readContent(struct fileStream* this){
if ((this->isValid(this)==0)) {
char * ____BAH_COMPILER_VAR_68 = "invalid";
return ____BAH_COMPILER_VAR_68;
}
long int sz = this->getSize(this);
char * r = memoryAllocSTR(sz+1);
long int l = fread(r,1,sz,this->handle);
if ((sz!=l)) {
array(char)* rarr = strAsArr(r);

{
long nLength = l;
if (rarr->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(rarr->data, (nLength+50)*sizeof(char));
rarr->data = newPtr;
}
rarr->data[l] = (char)0;
rarr->length = nLength+1;
} else {
rarr->data[l] = (char)0;
}
};
RCP_decr(rarr);
}
char * ____BAH_COMPILER_VAR_69 = r;
return ____BAH_COMPILER_VAR_69;
};
__BAH_ARR_TYPE_char fileStream__readBytes(struct fileStream* this){
array(char)* r = memoryAlloc(sizeof(array(char)));

r->length = 0;
r->elemSize = sizeof(char);
allocateArray(r,this->getSize(this));
this->readPtr(this,r->data,len(r));
array(char)* ____BAH_COMPILER_VAR_70 = r;
return ____BAH_COMPILER_VAR_70;
};
void fileStream__writeBytes(struct fileStream* this,__BAH_ARR_TYPE_char d){
this->writePtr(this,d->data,len(d));
};
void fileStream___end(struct fileStream* this){
if (this->isValid(this)) {
char * ____BAH_COMPILER_VAR_71 =null;
        {
            long int currStrOff = 0;
            long int strLen_0 = strlen(this->name);
long int strLen_1 = strlen("'.");
long int strLen_2 = strlen("iostream: warning, auto-closing file: '");
;                            
            ____BAH_COMPILER_VAR_71 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_71+currStrOff, "iostream: warning, auto-closing file: '", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_71+currStrOff, this->name, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_71+currStrOff, "'.", strLen_1);
            currStrOff += strLen_1;
        
        }println(____BAH_COMPILER_VAR_71);
this->close(this);
RCP_decr(____BAH_COMPILER_VAR_71);
}
};
struct fileMap {
long int handle;
long int size;
void * p;
char *(*open)(struct fileMap* this,char * fileName);
long int(*isValid)(struct fileMap* this);
void(*close)(struct fileMap* this);
};
char * fileMap__open(struct fileMap* this,char * fileName){
this->handle = open(fileName,O_RDWR,S_IRUSR|S_IWUSR);
struct stat ____BAH_COMPILER_VAR_72 = {};
#define sb ____BAH_COMPILER_VAR_72
fstat(this->handle,&sb);
this->size = sb.st_size;
void * ____BAH_COMPILER_VAR_73 = this->p; this->p = mmap(0,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,this->handle,0);RCP_decr(____BAH_COMPILER_VAR_73);
;
char * ____BAH_COMPILER_VAR_74 = this->p;
RCP_incr(this->p);
#undef sb
return ____BAH_COMPILER_VAR_74;
};
long int fileMap__isValid(struct fileMap* this){
if ((this->handle<0)) {
return 0;
}
return 1;
};
void fileMap__close(struct fileMap* this){
if ((this->handle==-1)) {
return;
}
munmap(this->p,this->size);
close(this->handle);
};
__BAH_ARR_TYPE_cpstring listFiles(char * dir){
array(char *)* files = memoryAlloc(sizeof(array(char *)));

files->length = 0;
files->elemSize = sizeof(char *);
DIR* d = opendir(dir);
struct dirent* file = readdir(d);
while ((file!=null)) {
long int lf = len(files);
if ((strcmp(file->d_name,".")==0)) {
struct dirent* ____BAH_COMPILER_VAR_75 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_75);
;
continue;
}
if ((strcmp(file->d_name,"..")==0)) {
struct dirent* ____BAH_COMPILER_VAR_76 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_76);
;
continue;
}

{
long nLength = lf;
if (files->length < nLength+1) {
if ((nLength+1) % 50 == 0 || nLength == 0) {
void * newPtr = memoryRealloc(files->data, (nLength+50)*sizeof(char *));
files->data = newPtr;
}
char * ____BAH_COMPILER_VAR_77 = files->data[lf]; files->data[lf] = __STR(file->d_name);RCP_decr(____BAH_COMPILER_VAR_77);
;
files->length = nLength+1;
} else {
char * ____BAH_COMPILER_VAR_77 = files->data[lf]; files->data[lf] = __STR(file->d_name);RCP_decr(____BAH_COMPILER_VAR_77);
;
}
};
struct dirent* ____BAH_COMPILER_VAR_78 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_78);
;
};
closedir(d);
array(char *)* ____BAH_COMPILER_VAR_79 = files;
RCP_decr(d);
RCP_decr(file);
return ____BAH_COMPILER_VAR_79;
};
long int fileExists(char * path){
long int is = access(path,0);
if ((is==0)) {
return 1;
}
return 0;
};
char removeFile(char * name){
if ((remove(name)==0)) {
return true;
}
return false;
};
long int getLastModified(char * name){
struct stat attr;
stat(name,&attr);
return attr.st_ctime;
};
long int main(__BAH_ARR_TYPE_cpstring args){
println("Hello world!");
return 0;
};
volatile struct __Bah_fnName_mapper __tmp____Bah_fnNames[132];
    
    void __attribute__((optimize("O0"))) __BAH_init() {
        DEBUG_RCP = false;
__BAH_panic_chan = null;
__Bah_fnNames = memoryAlloc(sizeof(array(struct __Bah_fnName_mapper)));

__Bah_fnNames->length = 0;
__Bah_fnNames->elemSize = sizeof(struct __Bah_fnName_mapper);
onMemoryError = null;
__Bah_init_segfaultHandle_OK = __Bah_init_segfaultHandle();

            __tmp____Bah_fnNames[0].n = "RCP_decr";
            __tmp____Bah_fnNames[0].p = RCP_decr;

            __tmp____Bah_fnNames[1].n = "__BAH_panic";
            __tmp____Bah_fnNames[1].p = __BAH_panic;

            __tmp____Bah_fnNames[2].n = "__Bah_safe_string";
            __tmp____Bah_fnNames[2].p = __Bah_safe_string;

            __tmp____Bah_fnNames[3].n = "__bah_strcmp";
            __tmp____Bah_fnNames[3].p = __bah_strcmp;

            __tmp____Bah_fnNames[4].n = "__bah_strlen";
            __tmp____Bah_fnNames[4].p = __bah_strlen;

            __tmp____Bah_fnNames[5].n = "len";
            __tmp____Bah_fnNames[5].p = len;

            __tmp____Bah_fnNames[6].n = "RCP_register";
            __tmp____Bah_fnNames[6].p = RCP_register;

            __tmp____Bah_fnNames[7].n = "RCP_remove";
            __tmp____Bah_fnNames[7].p = RCP_remove;

            __tmp____Bah_fnNames[8].n = "RCP_setNewPtr";
            __tmp____Bah_fnNames[8].p = RCP_setNewPtr;

            __tmp____Bah_fnNames[9].n = "destroy";
            __tmp____Bah_fnNames[9].p = destroy;

            __tmp____Bah_fnNames[10].n = "cmp_rcp";
            __tmp____Bah_fnNames[10].p = cmp_rcp;

            __tmp____Bah_fnNames[11].n = "RCPstate.getSize";
            __tmp____Bah_fnNames[11].p = RCPstate__getSize;

            __tmp____Bah_fnNames[12].n = "RCPstate.grow";
            __tmp____Bah_fnNames[12].p = RCPstate__grow;

            __tmp____Bah_fnNames[13].n = "RCPstate.sort";
            __tmp____Bah_fnNames[13].p = RCPstate__sort;

            __tmp____Bah_fnNames[14].n = "RCPstate.rcpToIndex";
            __tmp____Bah_fnNames[14].p = RCPstate__rcpToIndex;

            __tmp____Bah_fnNames[15].n = "RCPstate.add";
            __tmp____Bah_fnNames[15].p = RCPstate__add;

            __tmp____Bah_fnNames[16].n = "RCPstate.get";
            __tmp____Bah_fnNames[16].p = RCPstate__get;

            __tmp____Bah_fnNames[17].n = "RCPstate.set";
            __tmp____Bah_fnNames[17].p = RCPstate__set;

            __tmp____Bah_fnNames[18].n = "RCPstate.getByPtr";
            __tmp____Bah_fnNames[18].p = RCPstate__getByPtr;

            __tmp____Bah_fnNames[19].n = "RCPstate.resize";
            __tmp____Bah_fnNames[19].p = RCPstate__resize;

            __tmp____Bah_fnNames[20].n = "RCPstate.remove";
            __tmp____Bah_fnNames[20].p = RCPstate__remove;

            __tmp____Bah_fnNames[21].n = "RCPstate.lockMut";
            __tmp____Bah_fnNames[21].p = RCPstate__lockMut;

            __tmp____Bah_fnNames[22].n = "RCPstate.unlockMut";
            __tmp____Bah_fnNames[22].p = RCPstate__unlockMut;

            __tmp____Bah_fnNames[23].n = "RCP_init";
            __tmp____Bah_fnNames[23].p = RCP_init;

            __tmp____Bah_fnNames[24].n = "RCP_shutdown";
            __tmp____Bah_fnNames[24].p = RCP_shutdown;

            __tmp____Bah_fnNames[25].n = "cleanShutDown";
            __tmp____Bah_fnNames[25].p = cleanShutDown;

            __tmp____Bah_fnNames[26].n = "RCP_selfRef";
            __tmp____Bah_fnNames[26].p = RCP_selfRef;

            __tmp____Bah_fnNames[27].n = "RCP_registerSTR";
            __tmp____Bah_fnNames[27].p = RCP_registerSTR;

            __tmp____Bah_fnNames[28].n = "RCP_scanRegion";
            __tmp____Bah_fnNames[28].p = RCP_scanRegion;

            __tmp____Bah_fnNames[29].n = "RCP_incr";
            __tmp____Bah_fnNames[29].p = RCP_incr;

            __tmp____Bah_fnNames[30].n = "RCP_getCount";
            __tmp____Bah_fnNames[30].p = RCP_getCount;

            __tmp____Bah_fnNames[31].n = "RCP_isAllocated";
            __tmp____Bah_fnNames[31].p = RCP_isAllocated;

            __tmp____Bah_fnNames[32].n = "RCP_incrIL";
            __tmp____Bah_fnNames[32].p = RCP_incrIL;

            __tmp____Bah_fnNames[33].n = "RCP_decrIL";
            __tmp____Bah_fnNames[33].p = RCP_decrIL;

            __tmp____Bah_fnNames[34].n = "RCP_request";
            __tmp____Bah_fnNames[34].p = RCP_request;

            __tmp____Bah_fnNames[35].n = "RCP_decrRCP";
            __tmp____Bah_fnNames[35].p = RCP_decrRCP;

            __tmp____Bah_fnNames[36].n = "RCP_scanStack";
            __tmp____Bah_fnNames[36].p = RCP_scanStack;

            __tmp____Bah_fnNames[37].n = "RCP_scanHeap";
            __tmp____Bah_fnNames[37].p = RCP_scanHeap;

            __tmp____Bah_fnNames[38].n = "memoryAlloc";
            __tmp____Bah_fnNames[38].p = memoryAlloc;

            __tmp____Bah_fnNames[39].n = "memoryAllocSTR";
            __tmp____Bah_fnNames[39].p = memoryAllocSTR;

            __tmp____Bah_fnNames[40].n = "memoryRealloc";
            __tmp____Bah_fnNames[40].p = memoryRealloc;

            __tmp____Bah_fnNames[41].n = "clear";
            __tmp____Bah_fnNames[41].p = clear;

            __tmp____Bah_fnNames[42].n = "memoryOnEnd";
            __tmp____Bah_fnNames[42].p = memoryOnEnd;

            __tmp____Bah_fnNames[43].n = "append";
            __tmp____Bah_fnNames[43].p = append;

            __tmp____Bah_fnNames[44].n = "copy";
            __tmp____Bah_fnNames[44].p = copy;

            __tmp____Bah_fnNames[45].n = "sharedMemory";
            __tmp____Bah_fnNames[45].p = sharedMemory;

            __tmp____Bah_fnNames[46].n = "allocateArray";
            __tmp____Bah_fnNames[46].p = allocateArray;

            __tmp____Bah_fnNames[47].n = "__serialize";
            __tmp____Bah_fnNames[47].p = __serialize;

            __tmp____Bah_fnNames[48].n = "serlen";
            __tmp____Bah_fnNames[48].p = serlen;

            __tmp____Bah_fnNames[49].n = "unser";
            __tmp____Bah_fnNames[49].p = unser;

            __tmp____Bah_fnNames[50].n = "delete";
            __tmp____Bah_fnNames[50].p = delete;

            __tmp____Bah_fnNames[51].n = "deleteRange";
            __tmp____Bah_fnNames[51].p = deleteRange;

            __tmp____Bah_fnNames[52].n = "arrToStr";
            __tmp____Bah_fnNames[52].p = arrToStr;

            __tmp____Bah_fnNames[53].n = "strToArr";
            __tmp____Bah_fnNames[53].p = strToArr;

            __tmp____Bah_fnNames[54].n = "arrAsStr";
            __tmp____Bah_fnNames[54].p = arrAsStr;

            __tmp____Bah_fnNames[55].n = "strAsArr";
            __tmp____Bah_fnNames[55].p = strAsArr;

            __tmp____Bah_fnNames[56].n = "strTrimLeft";
            __tmp____Bah_fnNames[56].p = strTrimLeft;

            __tmp____Bah_fnNames[57].n = "strTrimRight";
            __tmp____Bah_fnNames[57].p = strTrimRight;

            __tmp____Bah_fnNames[58].n = "concatCPSTRING";
            __tmp____Bah_fnNames[58].p = concatCPSTRING;

            __tmp____Bah_fnNames[59].n = "__STR";
            __tmp____Bah_fnNames[59].p = __STR;

            __tmp____Bah_fnNames[60].n = "print";
            __tmp____Bah_fnNames[60].p = print;

            __tmp____Bah_fnNames[61].n = "cArr";
            __tmp____Bah_fnNames[61].p = cArr;

            __tmp____Bah_fnNames[62].n = "__checkString";
            __tmp____Bah_fnNames[62].p = __checkString;

            __tmp____Bah_fnNames[63].n = "mutex.init";
            __tmp____Bah_fnNames[63].p = mutex__init;

            __tmp____Bah_fnNames[64].n = "mutex.lock";
            __tmp____Bah_fnNames[64].p = mutex__lock;

            __tmp____Bah_fnNames[65].n = "mutex.unlock";
            __tmp____Bah_fnNames[65].p = mutex__unlock;

            __tmp____Bah_fnNames[66].n = "mutex.destroy";
            __tmp____Bah_fnNames[66].p = mutex__destroy;

            __tmp____Bah_fnNames[67].n = "mutexCondition.init";
            __tmp____Bah_fnNames[67].p = mutexCondition__init;

            __tmp____Bah_fnNames[68].n = "mutexCondition.wait";
            __tmp____Bah_fnNames[68].p = mutexCondition__wait;

            __tmp____Bah_fnNames[69].n = "mutexCondition.send";
            __tmp____Bah_fnNames[69].p = mutexCondition__send;

            __tmp____Bah_fnNames[70].n = "mutexCondition.destroy";
            __tmp____Bah_fnNames[70].p = mutexCondition__destroy;

            __tmp____Bah_fnNames[71].n = "mutexCondition";
            __tmp____Bah_fnNames[71].p = mutexCondition;

            __tmp____Bah_fnNames[72].n = "thread.create";
            __tmp____Bah_fnNames[72].p = thread__create;

            __tmp____Bah_fnNames[73].n = "thread.createWithArg";
            __tmp____Bah_fnNames[73].p = thread__createWithArg;

            __tmp____Bah_fnNames[74].n = "thread.wait";
            __tmp____Bah_fnNames[74].p = thread__wait;

            __tmp____Bah_fnNames[75].n = "mutex";
            __tmp____Bah_fnNames[75].p = mutex;

            __tmp____Bah_fnNames[76].n = "queue.insert";
            __tmp____Bah_fnNames[76].p = queue__insert;

            __tmp____Bah_fnNames[77].n = "queue.delete";
            __tmp____Bah_fnNames[77].p = queue__delete;

            __tmp____Bah_fnNames[78].n = "queue.get";
            __tmp____Bah_fnNames[78].p = queue__get;

            __tmp____Bah_fnNames[79].n = "queue.set";
            __tmp____Bah_fnNames[79].p = queue__set;

            __tmp____Bah_fnNames[80].n = "queue.pop";
            __tmp____Bah_fnNames[80].p = queue__pop;

            __tmp____Bah_fnNames[81].n = "queue.clear";
            __tmp____Bah_fnNames[81].p = queue__clear;

            __tmp____Bah_fnNames[82].n = "channel.send";
            __tmp____Bah_fnNames[82].p = channel__send;

            __tmp____Bah_fnNames[83].n = "channel.sendAny";
            __tmp____Bah_fnNames[83].p = channel__sendAny;

            __tmp____Bah_fnNames[84].n = "channel.receive";
            __tmp____Bah_fnNames[84].p = channel__receive;

            __tmp____Bah_fnNames[85].n = "channel.destroy";
            __tmp____Bah_fnNames[85].p = channel__destroy;

            __tmp____Bah_fnNames[86].n = "channel.len";
            __tmp____Bah_fnNames[86].p = channel__len;

            __tmp____Bah_fnNames[87].n = "channel";
            __tmp____Bah_fnNames[87].p = channel;

            __tmp____Bah_fnNames[88].n = "setChanCap";
            __tmp____Bah_fnNames[88].p = setChanCap;

            __tmp____Bah_fnNames[89].n = "__Bah_common_panic";
            __tmp____Bah_fnNames[89].p = __Bah_common_panic;

            __tmp____Bah_fnNames[90].n = "__Bah_fnNames_append";
            __tmp____Bah_fnNames[90].p = __Bah_fnNames_append;

            __tmp____Bah_fnNames[91].n = "backtrace";
            __tmp____Bah_fnNames[91].p = backtrace;

            __tmp____Bah_fnNames[92].n = "__Bah_segfault_handle";
            __tmp____Bah_fnNames[92].p = __Bah_segfault_handle;

            __tmp____Bah_fnNames[93].n = "__Bah_init_segfaultHandle";
            __tmp____Bah_fnNames[93].p = __Bah_init_segfaultHandle;

            __tmp____Bah_fnNames[94].n = "recover";
            __tmp____Bah_fnNames[94].p = recover;

            __tmp____Bah_fnNames[95].n = "cpstringCharAt";
            __tmp____Bah_fnNames[95].p = cpstringCharAt;

            __tmp____Bah_fnNames[96].n = "cpstringSubsitute";
            __tmp____Bah_fnNames[96].p = cpstringSubsitute;

            __tmp____Bah_fnNames[97].n = "arraySubstitute";
            __tmp____Bah_fnNames[97].p = arraySubstitute;

            __tmp____Bah_fnNames[98].n = "__Bah_map_hash";
            __tmp____Bah_fnNames[98].p = __Bah_map_hash;

            __tmp____Bah_fnNames[99].n = "mapWrapper.grow";
            __tmp____Bah_fnNames[99].p = mapWrapper__grow;

            __tmp____Bah_fnNames[100].n = "mapWrapper.set";
            __tmp____Bah_fnNames[100].p = mapWrapper__set;

            __tmp____Bah_fnNames[101].n = "mapWrapper.setAny";
            __tmp____Bah_fnNames[101].p = mapWrapper__setAny;

            __tmp____Bah_fnNames[102].n = "mapWrapper.delete";
            __tmp____Bah_fnNames[102].p = mapWrapper__delete;

            __tmp____Bah_fnNames[103].n = "mapWrapper.get";
            __tmp____Bah_fnNames[103].p = mapWrapper__get;

            __tmp____Bah_fnNames[104].n = "mapWrapper";
            __tmp____Bah_fnNames[104].p = mapWrapper;

            __tmp____Bah_fnNames[105].n = "stdinput";
            __tmp____Bah_fnNames[105].p = stdinput;

            __tmp____Bah_fnNames[106].n = "println";
            __tmp____Bah_fnNames[106].p = println;

            __tmp____Bah_fnNames[107].n = "fileStream.isValid";
            __tmp____Bah_fnNames[107].p = fileStream__isValid;

            __tmp____Bah_fnNames[108].n = "fileStream.open";
            __tmp____Bah_fnNames[108].p = fileStream__open;

            __tmp____Bah_fnNames[109].n = "fileStream.close";
            __tmp____Bah_fnNames[109].p = fileStream__close;

            __tmp____Bah_fnNames[110].n = "fileStream.getPos";
            __tmp____Bah_fnNames[110].p = fileStream__getPos;

            __tmp____Bah_fnNames[111].n = "fileStream.setPos";
            __tmp____Bah_fnNames[111].p = fileStream__setPos;

            __tmp____Bah_fnNames[112].n = "fileStream.getSize";
            __tmp____Bah_fnNames[112].p = fileStream__getSize;

            __tmp____Bah_fnNames[113].n = "fileStream.rewind";
            __tmp____Bah_fnNames[113].p = fileStream__rewind;

            __tmp____Bah_fnNames[114].n = "fileStream.getChar";
            __tmp____Bah_fnNames[114].p = fileStream__getChar;

            __tmp____Bah_fnNames[115].n = "fileStream.setChar";
            __tmp____Bah_fnNames[115].p = fileStream__setChar;

            __tmp____Bah_fnNames[116].n = "fileStream.createFile";
            __tmp____Bah_fnNames[116].p = fileStream__createFile;

            __tmp____Bah_fnNames[117].n = "fileStream.writeFile";
            __tmp____Bah_fnNames[117].p = fileStream__writeFile;

            __tmp____Bah_fnNames[118].n = "fileStream.writePtr";
            __tmp____Bah_fnNames[118].p = fileStream__writePtr;

            __tmp____Bah_fnNames[119].n = "fileStream.readPtr";
            __tmp____Bah_fnNames[119].p = fileStream__readPtr;

            __tmp____Bah_fnNames[120].n = "fileStream.readContent";
            __tmp____Bah_fnNames[120].p = fileStream__readContent;

            __tmp____Bah_fnNames[121].n = "fileStream.readBytes";
            __tmp____Bah_fnNames[121].p = fileStream__readBytes;

            __tmp____Bah_fnNames[122].n = "fileStream.writeBytes";
            __tmp____Bah_fnNames[122].p = fileStream__writeBytes;

            __tmp____Bah_fnNames[123].n = "fileStream._end";
            __tmp____Bah_fnNames[123].p = fileStream___end;

            __tmp____Bah_fnNames[124].n = "fileMap.open";
            __tmp____Bah_fnNames[124].p = fileMap__open;

            __tmp____Bah_fnNames[125].n = "fileMap.isValid";
            __tmp____Bah_fnNames[125].p = fileMap__isValid;

            __tmp____Bah_fnNames[126].n = "fileMap.close";
            __tmp____Bah_fnNames[126].p = fileMap__close;

            __tmp____Bah_fnNames[127].n = "listFiles";
            __tmp____Bah_fnNames[127].p = listFiles;

            __tmp____Bah_fnNames[128].n = "fileExists";
            __tmp____Bah_fnNames[128].p = fileExists;

            __tmp____Bah_fnNames[129].n = "removeFile";
            __tmp____Bah_fnNames[129].p = removeFile;

            __tmp____Bah_fnNames[130].n = "getLastModified";
            __tmp____Bah_fnNames[130].p = getLastModified;

            __tmp____Bah_fnNames[131].n = "main";
            __tmp____Bah_fnNames[131].p = main;

        __Bah_fnNames->data = __tmp____Bah_fnNames;
        __Bah_fnNames->length = 132;
        
    };
    