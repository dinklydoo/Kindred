# Kindred Toy Functional Language
### Program Linking
~~~
#include foo.kd
~~~
linking includes all declarations in the file specified by the include path (as follows)
### Program Declarations (Function definitions and Globals)
Declarations are also used in linking, only declared functions are visible to functions that include the file
~~~
@ declare a function before definition
#declare func foo:T(x1: T1, x2: T2)

@ declare a global variable name
#declare BAR 1
~~~

### Function Definitions
~~~
@ Defined as a function taking three parameters returning a value of type T

func foo(x1 : T1, x2 : T2, x3: T3):T
    
    ..body..

    return V

@ No declaration of void functions as we have no store (duh)
~~~

### Conditionals
Guarded Statements (haskell like):
~~~
case X of:
    X_1 => E_1,
    X_2 => E_2,
    X_3 => E_3,
    ...
    default => E_d
~~~

To use guarded as an if block just denote X as a boolean and pattern match with true and default (default as else expression)

### Lambda Abstraction
~~~
(lamb x : T => E)

@ With Nesting we define
(lamb x : T_1 => 
    (lamb y : T_2 => E_2 )
)
~~~

### Commenting Syntax
Single Line Commenting
~~~
@ This is a single line comment using a single at
~~~
Block Commenting
~~~
@*
This is a blocked comment,
defined by asterisk and at
*@
~~~

### Primitive Types
~~~
@ sizes are fixed i.e not dependent on compile target

bool - 1B
char - 1B
int - 4B
long - 8B
float - 4B
double - 8B

@ for numeric types (int, long, float, double) we can prepend unsigned, chars will be unsigned by default
~~~

### Lists
~~~
[] @ empty list
[Type]
@ defined as a list of elements with the typing Type

@ Pattern matching will be of two cases empty list and elsewise
case list of:
    [] => E_1;
    default => E_2;
~~~

### Operations (Numeric)
~~~
+ @ addition
- @ subtraction
* @ multiplication
/ @ division (type preserving, rounds down on int/long)
% @ modulo (only on int/long)
// @ floor division (only on float/double)
** @ power

& @ logical bitwise and
| @ logical bitwise or
^ @ logical bitwise xor
! @ logical bitwise not (1 if 0, 0 elsewise)
>> @ bitwise shift right
<< @ bitwise shift left

> @ comparitive gt
< @ comparitive lt
>= @ comparitive geq
<= @ comparitive leq
== @ comparitive eq
!= @ comparitive neq
~~~

### Operations (Boolean)
~~~
&& @ logical and
|| @ logical or
~~~

### Operations (Lists)
Need memory allocation with garbage collection
~~~
@ define strings as char lists
++ @ list concatenation (can be defined between two lists and singular element either [T]->[T]->[T] or [T]->T->[T] vice versa)

list[i] @ list indexing (0 indexed)
~~~

### Structure definitions
~~~
struct foo (
    bar1 : T1,
    bar2 : T2,
    bar3 : T3
)

@Constructor definition
foo(bar1, bar2, bar3)

@ Accessing structure variables
foo.bar1
~~~

### Enum definitions
~~~
enum foo (
    foo1, foo2, foo3, foo4
)
~~~

### I/O Operations
~~~
@ Will print to stdout variable contained within, for structs (records) it will print all internal values recursively to primitives (labelled)
print()

@ Reads a single PRIMITIVE value from input (buffered)
read()
~~~

### Control Flow
~~~
@ Executable files contain a main function which can only be defined once as such

func main(): int
    @ main body
~~~

