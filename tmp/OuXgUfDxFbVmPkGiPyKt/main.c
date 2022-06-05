#include <stdlib.h>
#include <string.h>
//COMPILE WITH: 'gcc -I "/opt/bah/libs/linux/include/" -L "/opt/bah/libs/linux/" tmp/OuXgUfDxFbVmPkGiPyKt/main.c -static -O1 -w  -lpthread -lm'

    void __BAH_init();
    #define noCheck(v) v
    #define array(type)	    struct{	    type *data;     long int length;     long int realLength;     long int elemSize;     }
    typedef array(char*)* __BAH_ARR_TYPE_cpstring;
    long int __BAH__main(__BAH_ARR_TYPE_cpstring);
    
            void RCP_init();
            void RCP_shutdown();
            void free(void*);
            #include <string.h>
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
long int ai = (long int)a;
long int bi = (long int)b;
if ((ai*bi==0)) {
return 1;
}
long int ____BAH_COMPILER_VAR_0=strcmp(a,b);
return ____BAH_COMPILER_VAR_0;
};
#define strcmp __bah_strcmp
long int __bah_strlen(char * s){
if (((void *)s==null)) {
return 0;
}
long int ____BAH_COMPILER_VAR_1=strlen(s);
return ____BAH_COMPILER_VAR_1;
};
#define strlen __bah_strlen
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void print(char * s){
write((void *)1,s,strlen(s));
};
void __BAH_memcpy(char * dest,char * source,long int l);
#define memcpy __BAH_memcpy
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
array(void*)*arr=a;
void * ____BAH_COMPILER_VAR_2=arr->length;
return ____BAH_COMPILER_VAR_2;
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
};
unsigned long int RCPstate__getSize(struct RCPstate* this,unsigned long int add){
unsigned long int l = this->len+add;
return l*sizeof(struct RCP);
};
void RCPstate__grow(struct RCPstate* this,unsigned long int i){
unsigned long int rs = RCPstate__getSize(this,i+30);
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
unsigned long int rs = RCPstate__getSize(this,1);
unsigned long int max = this->len-1;
if ((this->size<rs)) {
RCPstate__grow(this,1);
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
unsigned long int s = RCPstate__getSize(this,30);
if ((this->size-s>=this->size/2)) {
RCPstate__resize(this,s);
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
struct RCPstate ____BAH_COMPILER_VAR_3 = {};
____BAH_COMPILER_VAR_3.RCPs = null;
____BAH_COMPILER_VAR_3.len = 0;
____BAH_COMPILER_VAR_3.size = 0;
____BAH_COMPILER_VAR_3.heapMax= null;
____BAH_COMPILER_VAR_3.heapMin= null;
RCPstate = ____BAH_COMPILER_VAR_3;
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
register long int i = 0;
for (; (i<RCPstate.len); ++i) {
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
struct RCP ____BAH_COMPILER_VAR_4 = {};
____BAH_COMPILER_VAR_4.p = null;
____BAH_COMPILER_VAR_4.c = 0;
____BAH_COMPILER_VAR_4.s = 0;
____BAH_COMPILER_VAR_4.e = null;
#define r ____BAH_COMPILER_VAR_4
r.c = 1;
r.s = s;
r.p = p;
r.str = false;
RCPstate__add(&RCPstate,&r);

#undef r
};
void RCP_registerSTR(void * p,unsigned long int s){
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
r.str = true;
RCPstate__add(&RCPstate,&r);

#undef r
};
void RCP_setNewPtr(void * o,void * n){
if ((o==null)||(n==null)||(o==n)) {
return;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,o);
if ((r==null)) {
return;
}
r->p = n;
};
void RCP_remove(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
RCPstate__remove(&RCPstate,RCPstate__rcpToIndex(&RCPstate,r));
};
void RCP_scanRegion(void ** curr,void ** end,char decr);
void RCP_incr(void * p){
if ((p==null)) {
return;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
if ((r==null)) {
return;
}
r->c = r->c+1;
};
unsigned long int RCP_getCount(void * p){
if ((p==null)) {
return 0;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
if ((r==null)) {
return 0;
}
return r->c;
};
char RCP_isAllocated(void * p){
if ((p==null)) {
return false;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
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
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
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
RCPstate__remove(&RCPstate,RCPstate__rcpToIndex(&RCPstate,r));
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
return RCPstate__getByPtr(&RCPstate,p);
};
void RCP_decrRCP(struct RCP* r){
if ((r==null)) {
return;
}
r = RCPstate__getByPtr(&RCPstate,r->p);
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
RCPstate__remove(&RCPstate,RCPstate__rcpToIndex(&RCPstate,r));
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
struct RCP* r = RCPstate__getByPtr(&RCPstate,p);
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
array(void*)*arr=a;
memset(arr->data,null,arr->realLength*arr->elemSize);
arr->length=0;
};
void memoryOnEnd(void * obj,void * fn){
if ((obj==null)) {
return;
}
struct RCP* r = RCPstate__getByPtr(&RCPstate,obj);
if ((r==null)) {
return;
}
r->e = fn;
};
void __BAH_memcpy(char * dest,char * source,long int l){
register long int lm = l%sizeof(long int);
if ((lm!=0)) {
for (; (lm!=0); --lm) {
long int i = l-lm;
dest[i]=source[i];
};
}
long int* destI = (void *)((long int)dest-sizeof(long int));
long int* sourceI = (void *)((long int)source-sizeof(long int));
register long int i = l/sizeof(long int);
for (; (i!=0); --i) {
destI[i]=sourceI[i];
};
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
void * ____BAH_COMPILER_VAR_6 = r;
return ____BAH_COMPILER_VAR_6;
};
void allocateArray(void * arr,long int nbElems){
array(void*)*a=arr;
a->length=nbElems;
a->realLength=nbElems;
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
array(char)* ____BAH_COMPILER_VAR_7 = arr;
RCP_decr(r);
return ____BAH_COMPILER_VAR_7;
};
long int serlen(__BAH_ARR_TYPE_char data){
array(char)* sarr = memoryAlloc(sizeof(array(char)));

sarr->length = 8;
sarr->elemSize = sizeof(char);
sarr->data = memoryAlloc(sizeof(char) * 50);
                    sarr->realLength = 50;
sarr->data[0] = data->data[0];
sarr->data[1] = data->data[1];
sarr->data[2] = data->data[2];
sarr->data[3] = data->data[3];
sarr->data[4] = data->data[4];
sarr->data[5] = data->data[5];
sarr->data[6] = data->data[6];
sarr->data[7] = data->data[7];
void * ____BAH_COMPILER_VAR_8=*sarr->data;
RCP_decr(sarr);
return ____BAH_COMPILER_VAR_8;
};
void * unser(__BAH_ARR_TYPE_char data){
long int sptr = serlen(data);
void * r = memoryAlloc(sptr);
memcpy(r,data->data+8,sptr);
void * ____BAH_COMPILER_VAR_9 = r;
return ____BAH_COMPILER_VAR_9;
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
++i;
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
char * ____BAH_COMPILER_VAR_10 = str;
return ____BAH_COMPILER_VAR_10;
};
__BAH_ARR_TYPE_char strToArr(char * str){
long int strLen = strlen(str);
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
arr->data=memoryAlloc(strLen+1);
memcpy(arr->data,str,strLen);
arr->length=strLen;
array(char)* ____BAH_COMPILER_VAR_11 = arr;
return ____BAH_COMPILER_VAR_11;
};
char * arrAsStr(__BAH_ARR_TYPE_char arr){
RCP_incr(arr->data);
void * ____BAH_COMPILER_VAR_12=arr->data;
char * ____BAH_COMPILER_VAR_13 = ____BAH_COMPILER_VAR_12;
return ____BAH_COMPILER_VAR_13;
};
__BAH_ARR_TYPE_char strAsArr(char * str){
RCP_incr(str);
long int l = strlen(str);
array(char)* arr = memoryAlloc(sizeof(array(char)));

arr->length = 0;
arr->elemSize = sizeof(char);
arr->length=l;
arr->data=str;
array(char)* ____BAH_COMPILER_VAR_14 = arr;
return ____BAH_COMPILER_VAR_14;
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
char * ____BAH_COMPILER_VAR_15 = r;
return ____BAH_COMPILER_VAR_15;
};
char * __STR(char * a){
long int lenA = strlen(a);
char * r = memoryAllocSTR(lenA+1);
memcpy(r,a,lenA);
char * ____BAH_COMPILER_VAR_16 = r;
return ____BAH_COMPILER_VAR_16;
};
void * cArr(void * arr){
array(void*)*a=arr;
void * ____BAH_COMPILER_VAR_17=a->data;
void * ____BAH_COMPILER_VAR_18 = ____BAH_COMPILER_VAR_17;
return ____BAH_COMPILER_VAR_18;
};
char __checkString(char * s,char * l){
if (((void *)s==null)) {
char * ____BAH_COMPILER_VAR_19 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(l);
unsigned int strLen_1 = strlen(") is null \n");
unsigned int strLen_2 = strlen("cpstring (");
;                            
            ____BAH_COMPILER_VAR_19 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_19+currStrOff, "cpstring (", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_19+currStrOff, l, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_19+currStrOff, ") is null \n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_19);
exit(1);
RCP_decr(____BAH_COMPILER_VAR_19);
}
return true;
};
#include <pthread.h>
#define __thread_create pthread_create
#define __thread_join pthread_join
#define currentThread pthread_self
struct mutex {
pthread_mutex_t id;
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
struct mutexCondition ____BAH_COMPILER_VAR_20 = {};
#define m ____BAH_COMPILER_VAR_20
mutexCondition__init(&m);
struct mutexCondition ____BAH_COMPILER_VAR_21 = m;

#undef m
return ____BAH_COMPILER_VAR_21;

#undef m
};
struct thread {
pthread_t id;
void (*handle)(void *);
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
struct mutex ____BAH_COMPILER_VAR_22 = {};
#define m ____BAH_COMPILER_VAR_22
mutex__init(&m);
struct mutex ____BAH_COMPILER_VAR_23 = m;

#undef m
return ____BAH_COMPILER_VAR_23;

#undef m
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
};
void queue__insert(struct queue* this,void * data){
struct queueNode* ____BAH_COMPILER_VAR_24 = memoryAlloc(sizeof(struct queueNode));
____BAH_COMPILER_VAR_24->data= null;
____BAH_COMPILER_VAR_24->next= null;
____BAH_COMPILER_VAR_24->prev= null;
____BAH_COMPILER_VAR_24->key = this->length;
____BAH_COMPILER_VAR_24->data = data;
____BAH_COMPILER_VAR_24->prev = this->end;
struct queueNode* node = *(struct queueNode**)RCP_incrIL(&____BAH_COMPILER_VAR_24);
++this->length;
if ((this->end==null)) {
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&node);
*(struct queueNode**)RCP_decrIL(&this->end) = *(struct queueNode**)RCP_incrIL(&this->head);
}
else {
*(struct queueNode**)RCP_decrIL(&this->end->next) = *(struct queueNode**)RCP_incrIL(&node);
*(struct queueNode**)RCP_decrIL(&this->end) = *(struct queueNode**)RCP_incrIL(&node);
}
RCP_decr(____BAH_COMPILER_VAR_24);
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
void * ____BAH_COMPILER_VAR_25 = zp;
RCP_incr(zp);return ____BAH_COMPILER_VAR_25;
}
struct queueNode* ptr = *(struct queueNode**)RCP_incrIL(&this->head);
while ((ptr->key!=key)) {
if ((ptr->next==null)) {
void * ____BAH_COMPILER_VAR_26 = zp;
RCP_incr(zp);RCP_decr(ptr);
return ____BAH_COMPILER_VAR_26;
}
*(struct queueNode**)RCP_decrIL(&ptr) = *(struct queueNode**)RCP_incrIL(&ptr->next);
};
void * data = *(void **)RCP_incrIL(&ptr->data);
void * ____BAH_COMPILER_VAR_27 = data;
RCP_decr(zp);
RCP_decr(ptr);
return ____BAH_COMPILER_VAR_27;
};
void queue__set(struct queue* this,long int key,void * data){
queue__delete(this,key);
struct queueNode* ____BAH_COMPILER_VAR_28 = memoryAlloc(sizeof(struct queueNode));
____BAH_COMPILER_VAR_28->data= null;
____BAH_COMPILER_VAR_28->next= null;
____BAH_COMPILER_VAR_28->prev= null;
struct queueNode* node = *(struct queueNode**)RCP_incrIL(&____BAH_COMPILER_VAR_28);
node->key = key;
*(void **)RCP_decrIL(&node->data) = *(void **)RCP_incrIL(&data);
*(struct queueNode**)RCP_decrIL(&node->next) = *(struct queueNode**)RCP_incrIL(&this->head);
this->length = this->length+1;
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&node);
RCP_decr(____BAH_COMPILER_VAR_28);
RCP_decr(node);
};
void * queue__pop(struct queue* this){
if ((this->head==null)) {
void * ____BAH_COMPILER_VAR_29 = null;
RCP_incr(null);return ____BAH_COMPILER_VAR_29;
}
void * data = *(void **)RCP_incrIL(&this->head->data);
*(struct queueNode**)RCP_decrIL(&this->head) = *(struct queueNode**)RCP_incrIL(&this->head->next);
if ((this->head==null)) {
struct queueNode* ____BAH_COMPILER_VAR_30 = this->end; this->end = null;RCP_decr(____BAH_COMPILER_VAR_30);
;
}
--this->length;
void * ____BAH_COMPILER_VAR_31 = data;
return ____BAH_COMPILER_VAR_31;
};
void queue__clear(struct queue* this){
struct queueNode* ____BAH_COMPILER_VAR_32 = this->head; this->head = (void *)0;RCP_decr(____BAH_COMPILER_VAR_32);
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
};
void channel__send(struct channel* this,void * data){
pthread_mutex_lock(&this->m_mut);
if ((this->cap!=-1)) {
while ((this->queue->length==this->cap)) {
++this->w_waitting;
pthread_cond_wait(&this->w_cond,&this->m_mut);
--this->w_waitting;
};
}
queue__insert(this->queue,data);
if ((this->r_waitting>0)) {
pthread_cond_signal(&this->r_cond);
}
pthread_mutex_unlock(&this->m_mut);
};
void channel__sendAny(struct channel* this,void * data,long int len){
pthread_mutex_lock(&this->m_mut);
if ((this->cap!=-1)) {
while ((this->queue->length==this->cap)) {
++this->w_waitting;
pthread_cond_wait(&this->w_cond,&this->m_mut);
--this->w_waitting;
};
}
void * p = memoryAlloc(len);
memcpy(p,data,len);
queue__insert(this->queue,p);
if ((this->r_waitting>0)) {
pthread_cond_signal(&this->r_cond);
}
pthread_mutex_unlock(&this->m_mut);
RCP_decr(p);
};
void * channel__receive(struct channel* this){
pthread_mutex_lock(&this->m_mut);
while ((this->queue->length==0)) {
++this->r_waitting;
pthread_cond_wait(&this->r_cond,&this->m_mut);
--this->r_waitting;
};
void * data = queue__pop(this->queue);
if ((this->w_waitting>0)) {
pthread_cond_signal(&this->w_cond);
}
pthread_mutex_unlock(&this->m_mut);
void * ____BAH_COMPILER_VAR_33 = data;
return ____BAH_COMPILER_VAR_33;
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
struct channel* ____BAH_COMPILER_VAR_34 = memoryAlloc(sizeof(struct channel));
____BAH_COMPILER_VAR_34->w_waitting = 0;
____BAH_COMPILER_VAR_34->r_waitting = 0;
____BAH_COMPILER_VAR_34->queue= null;
____BAH_COMPILER_VAR_34->cap = -1;
struct channel* c = *(struct channel**)RCP_incrIL(&____BAH_COMPILER_VAR_34);
pthread_mutex_init(&c->m_mut,0);
pthread_cond_init(&c->w_cond,0);
pthread_cond_init(&c->r_cond,0);
struct queue* ____BAH_COMPILER_VAR_35 = memoryAlloc(sizeof(struct queue));
____BAH_COMPILER_VAR_35->length = 0;
____BAH_COMPILER_VAR_35->head = null;
____BAH_COMPILER_VAR_35->end = null;
*(struct queue**)RCP_decrIL(&c->queue) = *(struct queue**)RCP_incrIL(&____BAH_COMPILER_VAR_35);
struct channel* ____BAH_COMPILER_VAR_36 = c;
RCP_decr(____BAH_COMPILER_VAR_34);
RCP_decr(____BAH_COMPILER_VAR_35);
return ____BAH_COMPILER_VAR_36;
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
        unsigned long nLength = len(__Bah_fnNames);
        if (nLength >= __Bah_fnNames->length) {
            if (nLength >= __Bah_fnNames->realLength) {
                if (__Bah_fnNames->realLength != 0) {
                    __Bah_fnNames->realLength *= 2;
                } else {
                    __Bah_fnNames->realLength = 50;
                }
                void * newPtr = memoryRealloc(__Bah_fnNames->data, (__Bah_fnNames->realLength)*sizeof(struct __Bah_fnName_mapper));
                __Bah_fnNames->data = newPtr;
            }
            __Bah_fnNames->data[len(__Bah_fnNames)] = fnn; RCP_scanStack(&fnn, sizeof(fnn), 0);
            __Bah_fnNames->length = nLength+1;
        } else {
            RCP_scanStack(&__Bah_fnNames->data[len(__Bah_fnNames)], sizeof(__Bah_fnNames->data[len(__Bah_fnNames)]), 1); __Bah_fnNames->data[len(__Bah_fnNames)] = fnn; RCP_scanStack(&fnn, sizeof(fnn), 0);
        }
    }
    ;
};
long int backtrace(void * arr,long int l);
void __BAH_panic(char * e,char * line){
if ((__BAH_panic_chan!=null)) {
channel__send(__BAH_panic_chan, e);
return;
}
char * ____BAH_COMPILER_VAR_37 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(e);
unsigned int strLen_1 = strlen("\n");
unsigned int strLen_2 = strlen("): ");
unsigned int strLen_3 = strlen(line);
unsigned int strLen_4 = strlen("panic (");
;                            
            ____BAH_COMPILER_VAR_37 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2+strLen_3+strLen_4);
            
                    memcpy(____BAH_COMPILER_VAR_37+currStrOff, "panic (", strLen_4);
                    currStrOff += strLen_4;
                    
                    memcpy(____BAH_COMPILER_VAR_37+currStrOff, line, strLen_3);
                    currStrOff += strLen_3;
                    
                    memcpy(____BAH_COMPILER_VAR_37+currStrOff, "): ", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_37+currStrOff, e, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_37+currStrOff, "\n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_37);
array(void *)* arr = memoryAlloc(sizeof(array(void *)));

arr->length = 0;
arr->elemSize = sizeof(void *);
allocateArray(arr,10);
long int size = backtrace(arr->data,10);
print("Backtrace:\n");
long int min = -1;
long int max = -1;
register long int i = 1;
for (; (i<size); ++i) {
long int p = arr->data[i];
struct __Bah_fnName_mapper closest;
long int dist = -1;
register long int j = 0;
for (; (j<len(__Bah_fnNames)); ++j) {
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
char * ____BAH_COMPILER_VAR_38 = status; status = "?";RCP_decr(____BAH_COMPILER_VAR_38);
;
}
char * ____BAH_COMPILER_VAR_39 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(status);
unsigned int strLen_1 = strlen(" \n");
unsigned int strLen_2 = strlen("() ");
unsigned int strLen_3 = strlen(closest.n);
unsigned int strLen_4 = strlen("\t");
;                            
            ____BAH_COMPILER_VAR_39 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2+strLen_3+strLen_4);
            
                    memcpy(____BAH_COMPILER_VAR_39+currStrOff, "\t", strLen_4);
                    currStrOff += strLen_4;
                    
                    memcpy(____BAH_COMPILER_VAR_39+currStrOff, closest.n, strLen_3);
                    currStrOff += strLen_3;
                    
                    memcpy(____BAH_COMPILER_VAR_39+currStrOff, "() ", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_39+currStrOff, status, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_39+currStrOff, " \n", strLen_1);
            currStrOff += strLen_1;
        
        }print(____BAH_COMPILER_VAR_39);
if ((strcmp(closest.n, "main") == 0)) {
RCP_scanStack(&closest, sizeof(closest), 1);
RCP_decr(status);
RCP_decr(____BAH_COMPILER_VAR_39);
break;
}
RCP_scanStack(&closest, sizeof(closest), 1);
RCP_decr(status);
RCP_decr(____BAH_COMPILER_VAR_39);
};
cleanShutDown();
RCP_decr(____BAH_COMPILER_VAR_37);
RCP_decr(arr);
};
char * (*onMemoryError)();
void __Bah_segfault_handle(long int sig){
char * res = "";
if ((onMemoryError!=null)) {
char * ____BAH_COMPILER_VAR_40 = res; res = onMemoryError();RCP_decr(____BAH_COMPILER_VAR_40);
;
}
char * ____BAH_COMPILER_VAR_41 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen("Memory error (segfault).\n");
unsigned int strLen_1 = strlen(res);
;                            
            ____BAH_COMPILER_VAR_41 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_41+currStrOff, "Memory error (segfault).\n", strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_41+currStrOff, res, strLen_1);
            currStrOff += strLen_1;
        
        }__BAH_panic(____BAH_COMPILER_VAR_41,"???");
RCP_decr(res);
RCP_decr(____BAH_COMPILER_VAR_41);
};
char __Bah_init_segfaultHandle(){
signal(SIGSEGV,__Bah_segfault_handle);
return true;
};
char __Bah_init_segfaultHandle_OK;
char recover(char ** s){
struct channel * ____BAH_COMPILER_VAR_42 = __BAH_panic_chan; __BAH_panic_chan = channel();RCP_decr(____BAH_COMPILER_VAR_42);
;
char * ____BAH_COMPILER_VAR_43 =channel__receive(__BAH_panic_chan);char * err = *(char **)RCP_incrIL(&____BAH_COMPILER_VAR_43);
if ((s!=null)) {
*(char **)RCP_decrIL(&*s) = *(char **)RCP_incrIL(&err);
}
RCP_decr(____BAH_COMPILER_VAR_43);
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
        unsigned long nLength = 47;
        if (nLength >= a->length) {
            if (nLength >= a->realLength) {
                if (a->realLength != 0) {
                    a->realLength *= 2;
                } else {
                    a->realLength = 50;
                }
                void * newPtr = memoryRealloc(a->data, (a->realLength)*sizeof(char));
                a->data = newPtr;
            }
            a->data[47] = 46;
            a->length = nLength+1;
        } else {
            a->data[47] = 46;
        }
    }
    ;

    {
        unsigned long nLength = 48;
        if (nLength >= a->length) {
            if (nLength >= a->realLength) {
                if (a->realLength != 0) {
                    a->realLength *= 2;
                } else {
                    a->realLength = 50;
                }
                void * newPtr = memoryRealloc(a->data, (a->realLength)*sizeof(char));
                a->data = newPtr;
            }
            a->data[48] = 46;
            a->length = nLength+1;
        } else {
            a->data[48] = 46;
        }
    }
    ;

    {
        unsigned long nLength = 49;
        if (nLength >= a->length) {
            if (nLength >= a->realLength) {
                if (a->realLength != 0) {
                    a->realLength *= 2;
                } else {
                    a->realLength = 50;
                }
                void * newPtr = memoryRealloc(a->data, (a->realLength)*sizeof(char));
                a->data = newPtr;
            }
            a->data[49] = 46;
            a->length = nLength+1;
        } else {
            a->data[49] = 46;
        }
    }
    ;

    {
        unsigned long nLength = 50;
        if (nLength >= a->length) {
            if (nLength >= a->realLength) {
                if (a->realLength != 0) {
                    a->realLength *= 2;
                } else {
                    a->realLength = 50;
                }
                void * newPtr = memoryRealloc(a->data, (a->realLength)*sizeof(char));
                a->data = newPtr;
            }
            a->data[50] = (char)0;
            a->length = nLength+1;
        } else {
            a->data[50] = (char)0;
        }
    }
    ;
RCP_decr(a);
}
char * ____BAH_COMPILER_VAR_46 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(s);
unsigned int strLen_1 = strlen("\"");
unsigned int strLen_2 = strlen("\"");
;                            
            ____BAH_COMPILER_VAR_46 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_46+currStrOff, "\"", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_46+currStrOff, s, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_46+currStrOff, "\"", strLen_1);
            currStrOff += strLen_1;
        
        }char * ____BAH_COMPILER_VAR_47 = ____BAH_COMPILER_VAR_46;
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
register long int i = 0;
for (; (i<strlen(s)); ++i) {
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
};
void mapWrapper__grow(struct mapWrapper* this,long int nb){
long int l = len(this->elems);
register long int i = l;
for (; (i<l+nb); ++i) {

    {
        unsigned long nLength = i;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            struct mapElem* ____BAH_COMPILER_VAR_50 = this->elems->data[i]; this->elems->data[i] = null;RCP_decr(____BAH_COMPILER_VAR_50);
;
            this->elems->length = nLength+1;
        } else {
            struct mapElem* ____BAH_COMPILER_VAR_50 = this->elems->data[i]; this->elems->data[i] = null;RCP_decr(____BAH_COMPILER_VAR_50);
;
        }
    }
    ;
};
};
void mapWrapper__set(struct mapWrapper* this,char * k,void * e){
if ((this->length*2>=len(this->elems))) {
mapWrapper__grow(this,this->length);
}
struct mapElem* ____BAH_COMPILER_VAR_51 = memoryAlloc(sizeof(struct mapElem));
____BAH_COMPILER_VAR_51->key= null;
____BAH_COMPILER_VAR_51->val= null;
____BAH_COMPILER_VAR_51->key = k;
____BAH_COMPILER_VAR_51->val = e;
struct mapElem* elem = *(struct mapElem**)RCP_incrIL(&____BAH_COMPILER_VAR_51);
long int ind = __Bah_map_hash(k,len(this->elems));
register long int i = 0;
for (; (i<len(this->elems)); ++i) {
long int j = (i+ind)%len(this->elems);
struct mapElem* ce = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((ce==null)) {

    {
        unsigned long nLength = j;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
            this->elems->length = nLength+1;
        } else {
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
        }
    }
    ;
++this->length;
RCP_decr(ce);
break;
}
else if ((strcmp(ce->key, k) == 0)) {

    {
        unsigned long nLength = j;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
            this->elems->length = nLength+1;
        } else {
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
        }
    }
    ;
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
mapWrapper__grow(this,50);
}
if ((this->length*2>=len(this->elems))) {
mapWrapper__grow(this,this->length);
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
register long int i = 0;
for (; (i<len(this->elems)); ++i) {
long int j = (i+ind)%len(this->elems);
struct mapElem* ce = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((ce==null)) {

    {
        unsigned long nLength = j;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
            this->elems->length = nLength+1;
        } else {
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
        }
    }
    ;
++this->length;
RCP_decr(ce);
break;
}
else if ((strcmp(ce->key, k) == 0)) {

    {
        unsigned long nLength = j;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
            this->elems->length = nLength+1;
        } else {
            *(struct mapElem**)RCP_decrIL(&this->elems->data[j]) = *(struct mapElem**)RCP_incrIL(&elem);
        }
    }
    ;
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
register long int i = 0;
for (; (i<len(this->elems)); ++i) {
long int j = (i+ind)%len(this->elems);
struct mapElem* e = *(struct mapElem**)RCP_incrIL(&this->elems->data[j]);
if ((e!=null)&&(strcmp(e->key, k) == 0)) {

    {
        unsigned long nLength = j;
        if (nLength >= this->elems->length) {
            if (nLength >= this->elems->realLength) {
                if (this->elems->realLength != 0) {
                    this->elems->realLength *= 2;
                } else {
                    this->elems->realLength = 50;
                }
                void * newPtr = memoryRealloc(this->elems->data, (this->elems->realLength)*sizeof(struct mapElem*));
                this->elems->data = newPtr;
            }
            struct mapElem* ____BAH_COMPILER_VAR_53 = this->elems->data[j]; this->elems->data[j] = null;RCP_decr(____BAH_COMPILER_VAR_53);
;
            this->elems->length = nLength+1;
        } else {
            struct mapElem* ____BAH_COMPILER_VAR_53 = this->elems->data[j]; this->elems->data[j] = null;RCP_decr(____BAH_COMPILER_VAR_53);
;
        }
    }
    ;
}
RCP_decr(e);
};
};
void * mapWrapper__get(struct mapWrapper* this,char * k){
long int ind = __Bah_map_hash(k,len(this->elems));
register long int i = 0;
for (; (i<len(this->elems)); ++i) {
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
            struct mapWrapper* m = *(struct mapWrapper**)RCP_incrIL(&____BAH_COMPILER_VAR_56);
mapWrapper__grow(m,50);
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
register long int nDataLength = read((void *)0,buff,1024);
if ((nDataLength<1024)) {
char * ____BAH_COMPILER_VAR_58 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(response);
unsigned int strLen_1 = strlen(buff);
;                            
            ____BAH_COMPILER_VAR_58 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_58+currStrOff, response, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_58+currStrOff, buff, strLen_1);
            currStrOff += strLen_1;
        
        }*(char **)RCP_decrIL(&response) = *(char **)RCP_incrIL(&____BAH_COMPILER_VAR_58);
RCP_decr(____BAH_COMPILER_VAR_58);
}
else {
while ((nDataLength>0)) {
char * ____BAH_COMPILER_VAR_59 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(response);
unsigned int strLen_1 = strlen(buff);
;                            
            ____BAH_COMPILER_VAR_59 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_59+currStrOff, response, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_59+currStrOff, buff, strLen_1);
            currStrOff += strLen_1;
        
        }*(char **)RCP_decrIL(&response) = *(char **)RCP_incrIL(&____BAH_COMPILER_VAR_59);
if ((nDataLength<1024)) {
long int trimAmm = 1024-nDataLength;
strTrimRight(&response,trimAmm);
RCP_decr(____BAH_COMPILER_VAR_59);
break;
}
else {
nDataLength = read((void *)0,buff,1024);
}
RCP_decr(____BAH_COMPILER_VAR_59);
};
}
strTrimRight(&response,1);
char * ____BAH_COMPILER_VAR_60 = response;
RCP_decr(buff);
return ____BAH_COMPILER_VAR_60;
};
void println(char * s){
char * ____BAH_COMPILER_VAR_61 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(s);
unsigned int strLen_1 = strlen("\n");
;                            
            ____BAH_COMPILER_VAR_61 = memoryAllocSTR(1+strLen_0+strLen_1);
            
            memcpy(____BAH_COMPILER_VAR_61+currStrOff, s, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_61+currStrOff, "\n", strLen_1);
            currStrOff += strLen_1;
        
        }write((void *)1,____BAH_COMPILER_VAR_61,strlen(s)+1);
RCP_decr(____BAH_COMPILER_VAR_61);
};
struct fileStream {
FILE* handle;
char * name;
};
long int fileStream__isValid(struct fileStream* this){
if ((this->handle==null)) {
return 0;
}
return 1;
};
void fileStream__open(struct fileStream* this,char * path,char * mode){
*(char **)RCP_decrIL(&this->name) = *(char **)RCP_incrIL(&path);
FILE* ____BAH_COMPILER_VAR_62 = this->handle; this->handle = fopen(path,mode);RCP_decr(____BAH_COMPILER_VAR_62);
;
};
void fileStream__close(struct fileStream* this){
if ((fileStream__isValid(this)==0)) {
return;
}
fclose(this->handle);
FILE* ____BAH_COMPILER_VAR_63 = this->handle; this->handle = null;RCP_decr(____BAH_COMPILER_VAR_63);
;
};
long int fileStream__getPos(struct fileStream* this){
if ((fileStream__isValid(this)==0)) {
return 0;
}
long int ____BAH_COMPILER_VAR_64=ftell(this->handle);
return ____BAH_COMPILER_VAR_64;
};
void fileStream__setPos(struct fileStream* this,long int i){
if ((fileStream__isValid(this)==0)) {
return;
}
fseek(this->handle,i,0);
};
long int fileStream__getSize(struct fileStream* this){
if ((fileStream__isValid(this)==0)) {
return -1;
}
long int oldPos = fileStream__getPos(this);
fseek(this->handle,0,2);
long int size = ftell(this->handle);
fileStream__setPos(this,oldPos);
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
fileStream__open(this,path,"w");
fileStream__close(this);
};
long int fileStream__writeFile(struct fileStream* this,char * content){
if ((fileStream__isValid(this)==0)) {
return -1;
}
fputs(content,this->handle);
return 1;
};
void fileStream__writePtr(struct fileStream* this,void * a,long int s){
fwrite(a,s,1,this->handle);
};
long int fileStream__readPtr(struct fileStream* this,void * a,long int s){
long int ____BAH_COMPILER_VAR_65=fread(a,s,1,this->handle);
return ____BAH_COMPILER_VAR_65;
};
char * fileStream__readContent(struct fileStream* this){
if ((fileStream__isValid(this)==0)) {
char * ____BAH_COMPILER_VAR_66 = "invalid";
return ____BAH_COMPILER_VAR_66;
}
long int sz = fileStream__getSize(this);
char * r = memoryAllocSTR(sz+1);
long int l = fread(r,1,sz,this->handle);
if ((sz!=l)) {
array(char)* rarr = strAsArr(r);

    {
        unsigned long nLength = l;
        if (nLength >= rarr->length) {
            if (nLength >= rarr->realLength) {
                if (rarr->realLength != 0) {
                    rarr->realLength *= 2;
                } else {
                    rarr->realLength = 50;
                }
                void * newPtr = memoryRealloc(rarr->data, (rarr->realLength)*sizeof(char));
                rarr->data = newPtr;
            }
            rarr->data[l] = (char)0;
            rarr->length = nLength+1;
        } else {
            rarr->data[l] = (char)0;
        }
    }
    ;
RCP_decr(rarr);
}
char * ____BAH_COMPILER_VAR_67 = r;
return ____BAH_COMPILER_VAR_67;
};
__BAH_ARR_TYPE_char fileStream__readBytes(struct fileStream* this){
array(char)* r = memoryAlloc(sizeof(array(char)));

r->length = 0;
r->elemSize = sizeof(char);
allocateArray(r,fileStream__getSize(this));
fileStream__readPtr(this,r->data,len(r));
array(char)* ____BAH_COMPILER_VAR_68 = r;
return ____BAH_COMPILER_VAR_68;
};
void fileStream__writeBytes(struct fileStream* this,__BAH_ARR_TYPE_char d){
fileStream__writePtr(this,d->data,len(d));
};
void fileStream___end(struct fileStream* this){
if (fileStream__isValid(this)) {
char * ____BAH_COMPILER_VAR_69 =null;
        {
            unsigned int currStrOff = 0;
            unsigned int strLen_0 = strlen(this->name);
unsigned int strLen_1 = strlen("'.");
unsigned int strLen_2 = strlen("iostream: warning, auto-closing file: '");
;                            
            ____BAH_COMPILER_VAR_69 = memoryAllocSTR(1+strLen_0+strLen_1+strLen_2);
            
                    memcpy(____BAH_COMPILER_VAR_69+currStrOff, "iostream: warning, auto-closing file: '", strLen_2);
                    currStrOff += strLen_2;
                    
            memcpy(____BAH_COMPILER_VAR_69+currStrOff, this->name, strLen_0);
            currStrOff += strLen_0;
        
            memcpy(____BAH_COMPILER_VAR_69+currStrOff, "'.", strLen_1);
            currStrOff += strLen_1;
        
        }println(____BAH_COMPILER_VAR_69);
fileStream__close(this);
RCP_decr(____BAH_COMPILER_VAR_69);
}
};
struct fileMap {
long int handle;
long int size;
void * p;
};
char * fileMap__open(struct fileMap* this,char * fileName){
this->handle = open(fileName,O_RDWR,S_IRUSR|S_IWUSR);
struct stat ____BAH_COMPILER_VAR_70 = {};
#define sb ____BAH_COMPILER_VAR_70
fstat(this->handle,&sb);
this->size = sb.st_size;
void * ____BAH_COMPILER_VAR_71 = this->p; this->p = mmap(0,sb.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,this->handle,0);RCP_decr(____BAH_COMPILER_VAR_71);
;
char * ____BAH_COMPILER_VAR_72 = this->p;
RCP_incr(this->p);
#undef sb
return ____BAH_COMPILER_VAR_72;
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
struct dirent* ____BAH_COMPILER_VAR_73 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_73);
;
continue;
}
if ((strcmp(file->d_name,"..")==0)) {
struct dirent* ____BAH_COMPILER_VAR_74 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_74);
;
continue;
}

    {
        unsigned long nLength = lf;
        if (nLength >= files->length) {
            if (nLength >= files->realLength) {
                if (files->realLength != 0) {
                    files->realLength *= 2;
                } else {
                    files->realLength = 50;
                }
                void * newPtr = memoryRealloc(files->data, (files->realLength)*sizeof(char *));
                files->data = newPtr;
            }
            char * ____BAH_COMPILER_VAR_75 = files->data[lf]; files->data[lf] = __STR(file->d_name);RCP_decr(____BAH_COMPILER_VAR_75);
;
            files->length = nLength+1;
        } else {
            char * ____BAH_COMPILER_VAR_75 = files->data[lf]; files->data[lf] = __STR(file->d_name);RCP_decr(____BAH_COMPILER_VAR_75);
;
        }
    }
    ;
struct dirent* ____BAH_COMPILER_VAR_76 = file; file = readdir(d);RCP_decr(____BAH_COMPILER_VAR_76);
;
};
closedir(d);
array(char *)* ____BAH_COMPILER_VAR_77 = files;
RCP_decr(d);
RCP_decr(file);
return ____BAH_COMPILER_VAR_77;
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
volatile struct __Bah_fnName_mapper __tmp____Bah_fnNames[133];
    
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

            __tmp____Bah_fnNames[5].n = "print";
            __tmp____Bah_fnNames[5].p = print;

            __tmp____Bah_fnNames[6].n = "__BAH_memcpy";
            __tmp____Bah_fnNames[6].p = __BAH_memcpy;

            __tmp____Bah_fnNames[7].n = "len";
            __tmp____Bah_fnNames[7].p = len;

            __tmp____Bah_fnNames[8].n = "RCP_register";
            __tmp____Bah_fnNames[8].p = RCP_register;

            __tmp____Bah_fnNames[9].n = "RCP_remove";
            __tmp____Bah_fnNames[9].p = RCP_remove;

            __tmp____Bah_fnNames[10].n = "RCP_setNewPtr";
            __tmp____Bah_fnNames[10].p = RCP_setNewPtr;

            __tmp____Bah_fnNames[11].n = "destroy";
            __tmp____Bah_fnNames[11].p = destroy;

            __tmp____Bah_fnNames[12].n = "cmp_rcp";
            __tmp____Bah_fnNames[12].p = cmp_rcp;

            __tmp____Bah_fnNames[13].n = "RCPstate.getSize";
            __tmp____Bah_fnNames[13].p = RCPstate__getSize;

            __tmp____Bah_fnNames[14].n = "RCPstate.grow";
            __tmp____Bah_fnNames[14].p = RCPstate__grow;

            __tmp____Bah_fnNames[15].n = "RCPstate.sort";
            __tmp____Bah_fnNames[15].p = RCPstate__sort;

            __tmp____Bah_fnNames[16].n = "RCPstate.rcpToIndex";
            __tmp____Bah_fnNames[16].p = RCPstate__rcpToIndex;

            __tmp____Bah_fnNames[17].n = "RCPstate.add";
            __tmp____Bah_fnNames[17].p = RCPstate__add;

            __tmp____Bah_fnNames[18].n = "RCPstate.get";
            __tmp____Bah_fnNames[18].p = RCPstate__get;

            __tmp____Bah_fnNames[19].n = "RCPstate.set";
            __tmp____Bah_fnNames[19].p = RCPstate__set;

            __tmp____Bah_fnNames[20].n = "RCPstate.getByPtr";
            __tmp____Bah_fnNames[20].p = RCPstate__getByPtr;

            __tmp____Bah_fnNames[21].n = "RCPstate.resize";
            __tmp____Bah_fnNames[21].p = RCPstate__resize;

            __tmp____Bah_fnNames[22].n = "RCPstate.remove";
            __tmp____Bah_fnNames[22].p = RCPstate__remove;

            __tmp____Bah_fnNames[23].n = "RCPstate.lockMut";
            __tmp____Bah_fnNames[23].p = RCPstate__lockMut;

            __tmp____Bah_fnNames[24].n = "RCPstate.unlockMut";
            __tmp____Bah_fnNames[24].p = RCPstate__unlockMut;

            __tmp____Bah_fnNames[25].n = "RCP_init";
            __tmp____Bah_fnNames[25].p = RCP_init;

            __tmp____Bah_fnNames[26].n = "RCP_shutdown";
            __tmp____Bah_fnNames[26].p = RCP_shutdown;

            __tmp____Bah_fnNames[27].n = "cleanShutDown";
            __tmp____Bah_fnNames[27].p = cleanShutDown;

            __tmp____Bah_fnNames[28].n = "RCP_selfRef";
            __tmp____Bah_fnNames[28].p = RCP_selfRef;

            __tmp____Bah_fnNames[29].n = "RCP_registerSTR";
            __tmp____Bah_fnNames[29].p = RCP_registerSTR;

            __tmp____Bah_fnNames[30].n = "RCP_scanRegion";
            __tmp____Bah_fnNames[30].p = RCP_scanRegion;

            __tmp____Bah_fnNames[31].n = "RCP_incr";
            __tmp____Bah_fnNames[31].p = RCP_incr;

            __tmp____Bah_fnNames[32].n = "RCP_getCount";
            __tmp____Bah_fnNames[32].p = RCP_getCount;

            __tmp____Bah_fnNames[33].n = "RCP_isAllocated";
            __tmp____Bah_fnNames[33].p = RCP_isAllocated;

            __tmp____Bah_fnNames[34].n = "RCP_incrIL";
            __tmp____Bah_fnNames[34].p = RCP_incrIL;

            __tmp____Bah_fnNames[35].n = "RCP_decrIL";
            __tmp____Bah_fnNames[35].p = RCP_decrIL;

            __tmp____Bah_fnNames[36].n = "RCP_request";
            __tmp____Bah_fnNames[36].p = RCP_request;

            __tmp____Bah_fnNames[37].n = "RCP_decrRCP";
            __tmp____Bah_fnNames[37].p = RCP_decrRCP;

            __tmp____Bah_fnNames[38].n = "RCP_scanStack";
            __tmp____Bah_fnNames[38].p = RCP_scanStack;

            __tmp____Bah_fnNames[39].n = "RCP_scanHeap";
            __tmp____Bah_fnNames[39].p = RCP_scanHeap;

            __tmp____Bah_fnNames[40].n = "memoryAlloc";
            __tmp____Bah_fnNames[40].p = memoryAlloc;

            __tmp____Bah_fnNames[41].n = "memoryAllocSTR";
            __tmp____Bah_fnNames[41].p = memoryAllocSTR;

            __tmp____Bah_fnNames[42].n = "memoryRealloc";
            __tmp____Bah_fnNames[42].p = memoryRealloc;

            __tmp____Bah_fnNames[43].n = "clear";
            __tmp____Bah_fnNames[43].p = clear;

            __tmp____Bah_fnNames[44].n = "memoryOnEnd";
            __tmp____Bah_fnNames[44].p = memoryOnEnd;

            __tmp____Bah_fnNames[45].n = "append";
            __tmp____Bah_fnNames[45].p = append;

            __tmp____Bah_fnNames[46].n = "copy";
            __tmp____Bah_fnNames[46].p = copy;

            __tmp____Bah_fnNames[47].n = "sharedMemory";
            __tmp____Bah_fnNames[47].p = sharedMemory;

            __tmp____Bah_fnNames[48].n = "allocateArray";
            __tmp____Bah_fnNames[48].p = allocateArray;

            __tmp____Bah_fnNames[49].n = "__serialize";
            __tmp____Bah_fnNames[49].p = __serialize;

            __tmp____Bah_fnNames[50].n = "serlen";
            __tmp____Bah_fnNames[50].p = serlen;

            __tmp____Bah_fnNames[51].n = "unser";
            __tmp____Bah_fnNames[51].p = unser;

            __tmp____Bah_fnNames[52].n = "delete";
            __tmp____Bah_fnNames[52].p = delete;

            __tmp____Bah_fnNames[53].n = "deleteRange";
            __tmp____Bah_fnNames[53].p = deleteRange;

            __tmp____Bah_fnNames[54].n = "arrToStr";
            __tmp____Bah_fnNames[54].p = arrToStr;

            __tmp____Bah_fnNames[55].n = "strToArr";
            __tmp____Bah_fnNames[55].p = strToArr;

            __tmp____Bah_fnNames[56].n = "arrAsStr";
            __tmp____Bah_fnNames[56].p = arrAsStr;

            __tmp____Bah_fnNames[57].n = "strAsArr";
            __tmp____Bah_fnNames[57].p = strAsArr;

            __tmp____Bah_fnNames[58].n = "strTrimLeft";
            __tmp____Bah_fnNames[58].p = strTrimLeft;

            __tmp____Bah_fnNames[59].n = "strTrimRight";
            __tmp____Bah_fnNames[59].p = strTrimRight;

            __tmp____Bah_fnNames[60].n = "concatCPSTRING";
            __tmp____Bah_fnNames[60].p = concatCPSTRING;

            __tmp____Bah_fnNames[61].n = "__STR";
            __tmp____Bah_fnNames[61].p = __STR;

            __tmp____Bah_fnNames[62].n = "cArr";
            __tmp____Bah_fnNames[62].p = cArr;

            __tmp____Bah_fnNames[63].n = "__checkString";
            __tmp____Bah_fnNames[63].p = __checkString;

            __tmp____Bah_fnNames[64].n = "mutex.init";
            __tmp____Bah_fnNames[64].p = mutex__init;

            __tmp____Bah_fnNames[65].n = "mutex.lock";
            __tmp____Bah_fnNames[65].p = mutex__lock;

            __tmp____Bah_fnNames[66].n = "mutex.unlock";
            __tmp____Bah_fnNames[66].p = mutex__unlock;

            __tmp____Bah_fnNames[67].n = "mutex.destroy";
            __tmp____Bah_fnNames[67].p = mutex__destroy;

            __tmp____Bah_fnNames[68].n = "mutexCondition.init";
            __tmp____Bah_fnNames[68].p = mutexCondition__init;

            __tmp____Bah_fnNames[69].n = "mutexCondition.wait";
            __tmp____Bah_fnNames[69].p = mutexCondition__wait;

            __tmp____Bah_fnNames[70].n = "mutexCondition.send";
            __tmp____Bah_fnNames[70].p = mutexCondition__send;

            __tmp____Bah_fnNames[71].n = "mutexCondition.destroy";
            __tmp____Bah_fnNames[71].p = mutexCondition__destroy;

            __tmp____Bah_fnNames[72].n = "mutexCondition";
            __tmp____Bah_fnNames[72].p = mutexCondition;

            __tmp____Bah_fnNames[73].n = "thread.create";
            __tmp____Bah_fnNames[73].p = thread__create;

            __tmp____Bah_fnNames[74].n = "thread.createWithArg";
            __tmp____Bah_fnNames[74].p = thread__createWithArg;

            __tmp____Bah_fnNames[75].n = "thread.wait";
            __tmp____Bah_fnNames[75].p = thread__wait;

            __tmp____Bah_fnNames[76].n = "mutex";
            __tmp____Bah_fnNames[76].p = mutex;

            __tmp____Bah_fnNames[77].n = "queue.insert";
            __tmp____Bah_fnNames[77].p = queue__insert;

            __tmp____Bah_fnNames[78].n = "queue.delete";
            __tmp____Bah_fnNames[78].p = queue__delete;

            __tmp____Bah_fnNames[79].n = "queue.get";
            __tmp____Bah_fnNames[79].p = queue__get;

            __tmp____Bah_fnNames[80].n = "queue.set";
            __tmp____Bah_fnNames[80].p = queue__set;

            __tmp____Bah_fnNames[81].n = "queue.pop";
            __tmp____Bah_fnNames[81].p = queue__pop;

            __tmp____Bah_fnNames[82].n = "queue.clear";
            __tmp____Bah_fnNames[82].p = queue__clear;

            __tmp____Bah_fnNames[83].n = "channel.send";
            __tmp____Bah_fnNames[83].p = channel__send;

            __tmp____Bah_fnNames[84].n = "channel.sendAny";
            __tmp____Bah_fnNames[84].p = channel__sendAny;

            __tmp____Bah_fnNames[85].n = "channel.receive";
            __tmp____Bah_fnNames[85].p = channel__receive;

            __tmp____Bah_fnNames[86].n = "channel.destroy";
            __tmp____Bah_fnNames[86].p = channel__destroy;

            __tmp____Bah_fnNames[87].n = "channel.len";
            __tmp____Bah_fnNames[87].p = channel__len;

            __tmp____Bah_fnNames[88].n = "channel";
            __tmp____Bah_fnNames[88].p = channel;

            __tmp____Bah_fnNames[89].n = "setChanCap";
            __tmp____Bah_fnNames[89].p = setChanCap;

            __tmp____Bah_fnNames[90].n = "__Bah_common_panic";
            __tmp____Bah_fnNames[90].p = __Bah_common_panic;

            __tmp____Bah_fnNames[91].n = "__Bah_fnNames_append";
            __tmp____Bah_fnNames[91].p = __Bah_fnNames_append;

            __tmp____Bah_fnNames[92].n = "backtrace";
            __tmp____Bah_fnNames[92].p = backtrace;

            __tmp____Bah_fnNames[93].n = "__Bah_segfault_handle";
            __tmp____Bah_fnNames[93].p = __Bah_segfault_handle;

            __tmp____Bah_fnNames[94].n = "__Bah_init_segfaultHandle";
            __tmp____Bah_fnNames[94].p = __Bah_init_segfaultHandle;

            __tmp____Bah_fnNames[95].n = "recover";
            __tmp____Bah_fnNames[95].p = recover;

            __tmp____Bah_fnNames[96].n = "cpstringCharAt";
            __tmp____Bah_fnNames[96].p = cpstringCharAt;

            __tmp____Bah_fnNames[97].n = "cpstringSubsitute";
            __tmp____Bah_fnNames[97].p = cpstringSubsitute;

            __tmp____Bah_fnNames[98].n = "arraySubstitute";
            __tmp____Bah_fnNames[98].p = arraySubstitute;

            __tmp____Bah_fnNames[99].n = "__Bah_map_hash";
            __tmp____Bah_fnNames[99].p = __Bah_map_hash;

            __tmp____Bah_fnNames[100].n = "mapWrapper.grow";
            __tmp____Bah_fnNames[100].p = mapWrapper__grow;

            __tmp____Bah_fnNames[101].n = "mapWrapper.set";
            __tmp____Bah_fnNames[101].p = mapWrapper__set;

            __tmp____Bah_fnNames[102].n = "mapWrapper.setAny";
            __tmp____Bah_fnNames[102].p = mapWrapper__setAny;

            __tmp____Bah_fnNames[103].n = "mapWrapper.delete";
            __tmp____Bah_fnNames[103].p = mapWrapper__delete;

            __tmp____Bah_fnNames[104].n = "mapWrapper.get";
            __tmp____Bah_fnNames[104].p = mapWrapper__get;

            __tmp____Bah_fnNames[105].n = "mapWrapper";
            __tmp____Bah_fnNames[105].p = mapWrapper;

            __tmp____Bah_fnNames[106].n = "stdinput";
            __tmp____Bah_fnNames[106].p = stdinput;

            __tmp____Bah_fnNames[107].n = "println";
            __tmp____Bah_fnNames[107].p = println;

            __tmp____Bah_fnNames[108].n = "fileStream.isValid";
            __tmp____Bah_fnNames[108].p = fileStream__isValid;

            __tmp____Bah_fnNames[109].n = "fileStream.open";
            __tmp____Bah_fnNames[109].p = fileStream__open;

            __tmp____Bah_fnNames[110].n = "fileStream.close";
            __tmp____Bah_fnNames[110].p = fileStream__close;

            __tmp____Bah_fnNames[111].n = "fileStream.getPos";
            __tmp____Bah_fnNames[111].p = fileStream__getPos;

            __tmp____Bah_fnNames[112].n = "fileStream.setPos";
            __tmp____Bah_fnNames[112].p = fileStream__setPos;

            __tmp____Bah_fnNames[113].n = "fileStream.getSize";
            __tmp____Bah_fnNames[113].p = fileStream__getSize;

            __tmp____Bah_fnNames[114].n = "fileStream.rewind";
            __tmp____Bah_fnNames[114].p = fileStream__rewind;

            __tmp____Bah_fnNames[115].n = "fileStream.getChar";
            __tmp____Bah_fnNames[115].p = fileStream__getChar;

            __tmp____Bah_fnNames[116].n = "fileStream.setChar";
            __tmp____Bah_fnNames[116].p = fileStream__setChar;

            __tmp____Bah_fnNames[117].n = "fileStream.createFile";
            __tmp____Bah_fnNames[117].p = fileStream__createFile;

            __tmp____Bah_fnNames[118].n = "fileStream.writeFile";
            __tmp____Bah_fnNames[118].p = fileStream__writeFile;

            __tmp____Bah_fnNames[119].n = "fileStream.writePtr";
            __tmp____Bah_fnNames[119].p = fileStream__writePtr;

            __tmp____Bah_fnNames[120].n = "fileStream.readPtr";
            __tmp____Bah_fnNames[120].p = fileStream__readPtr;

            __tmp____Bah_fnNames[121].n = "fileStream.readContent";
            __tmp____Bah_fnNames[121].p = fileStream__readContent;

            __tmp____Bah_fnNames[122].n = "fileStream.readBytes";
            __tmp____Bah_fnNames[122].p = fileStream__readBytes;

            __tmp____Bah_fnNames[123].n = "fileStream.writeBytes";
            __tmp____Bah_fnNames[123].p = fileStream__writeBytes;

            __tmp____Bah_fnNames[124].n = "fileStream._end";
            __tmp____Bah_fnNames[124].p = fileStream___end;

            __tmp____Bah_fnNames[125].n = "fileMap.open";
            __tmp____Bah_fnNames[125].p = fileMap__open;

            __tmp____Bah_fnNames[126].n = "fileMap.isValid";
            __tmp____Bah_fnNames[126].p = fileMap__isValid;

            __tmp____Bah_fnNames[127].n = "fileMap.close";
            __tmp____Bah_fnNames[127].p = fileMap__close;

            __tmp____Bah_fnNames[128].n = "listFiles";
            __tmp____Bah_fnNames[128].p = listFiles;

            __tmp____Bah_fnNames[129].n = "fileExists";
            __tmp____Bah_fnNames[129].p = fileExists;

            __tmp____Bah_fnNames[130].n = "removeFile";
            __tmp____Bah_fnNames[130].p = removeFile;

            __tmp____Bah_fnNames[131].n = "getLastModified";
            __tmp____Bah_fnNames[131].p = getLastModified;

            __tmp____Bah_fnNames[132].n = "main";
            __tmp____Bah_fnNames[132].p = main;

        __Bah_fnNames->data = __tmp____Bah_fnNames;
        __Bah_fnNames->length = 133;
        
    };
    