# matrix


### matrix (struct)
A matrix is defined by its number of elements per line (column size).
__Its methods are:__
- <code>**index**(r int, c int) int </code> Get an index from row and column index.
- <code>**rowIndex**(i int) int </code> Get the row index from an index.


### matrix (func)
<code>matrix(sc int) matrix&ast; </code>
Makes a new matrix by its column size.


## Example
```bah
 &num;include "iostream.bah"
 &num;include "matrix.bah"
 main(args []cpstring) int {
     a = []int
     m = matrix(3)
     i=0; for i &lt; 4 {
         a[m.index(i,0)] = 1+i
         a[m.index(i,1)] = 2+i
         a[m.index(i,2)] = 3+i
         i = i + 1
     }
     println("a[2;1] = "+intToStr(a[m.index(2,1)]))
     rows = m.rowIndex(len(a))
     i=0; for i &lt; rows {
         row = ""
         j=0; for j &lt; m.colSize {
             e = a[m.index(i, j)]
             row = row + " " + intToStr(e)
             j = j + 1
         }
         println(row)
         i = i + 1
     }
     return 0
 }
```