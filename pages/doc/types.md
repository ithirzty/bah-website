## Types
Bah has multiple built-in types. They are:
- **int** an 64 bits integer
- **int32** a 32 bits integer
- **uint** an unsigned integer
- **uint32** an unsigned 32 bits integer
- **long** a 128 bits integer
- **ulong** an unsigned 128 bits integer
- **short** a 16 bits integer
- **ushort** an unsigned 16 bit integer
- **float** a 63 bits floating point number
- **float32** a 32 bits floatting point number
- **ufloat** an unsigned floatting point number
- **ufloat32** an unsigned 32 bits floatting point number
- **char** a character
- **ptr** a pointer that can point to any type. *It can be used as a wildcard as <code>void&ast;</code> in c*
- **cpstring** a string of characters

There are also [structures](./structs).
You can define your own type using the keyword *#define* as such:
```bah
#define myIntegerType int
```