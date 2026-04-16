# Kindred Toy Functional Language

### Function Definitions
~~~
@ function which takes no parameters
func foo(:): T (
    ...
)


@ Defined as a function taking three parameters returning a value of type T

func foo(x1 : T1, x2 : T2, x3: T3):T (
    
    ..body..

    return V
)

@ No declaration of void functions as of yet
~~~
#### Functions as arguments (Typing):
~~~
func foo( bar:(T1) -> T, x:T1):T (
    return bar(x)
)
~~~
### Functions as return types:
~~~
func foo(b: bool): (T1, T2, T1) -> T1 (

    bar1: (x1:T1, x2:T2, x3:T1) -> T1 (
        return x1
    )
    bar2: (x1:T1, x2:T2, x3:T1) -> T1 (
        return x1 - foo2(x2) + x3*x3
    )
    case b of:
        | true => return bar1,
        | false => return bar2
)
~~~
alternatively (when lambda's are implemented LMAO)
~~~
func foo(): (T1, T2, T3) -> T4
    return (lamb x : T =>

    )
~~~
### Variable Declaration
Variables are immutable containers for expressions within functions
~~~
func foo(x: int): int (
    y: int = (x + 4)
    return y
)
~~~

### Conditionals
Pattern Matching
~~~
mark X of:
    X_1 => E_1,
    X_2 => E_2,
    X_3 => E_3,
    ...
    default => E_d
;
~~~
Pattern matching with constructive types works based on the
size of element for lists and existence of fields for structs
~~~
@ pattern match over length of a list

mark X of:
    x:xz:xs => E_1,
    x:xs => E_2,
    default => E_3

@ pattern match structurally on recursive struct types, if a field is a struct instance then we can check if it's nil or non-nil, note a value x in a field spot will subsume a nil check later i.e

    mark X of:
        tree{x, l, nil} => E_1, @ this pattern will subsume tree{x, nil, nil}
        tree{x, nil, nil} => E_2,
        default => E_3
    ;

mark X of:
    nil => E_1,
    tree{x, nil, nil} => E_2
    tree{x, nil, r} => E_3
    tree{x, l, r} => E_4
    default => E_5

~~~
Guarded Statements
~~~
case X of:
    | foo(X) => E_1,
    | X == Z =>
        E_2,
    | default => E_3
;
~~~

### Lambda Abstraction (WIP)
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
~~~
Numeric types are implicitly casted and expressions mixing numeric types will bind to the strongest type according to precedence:
~~~
(weakest binding) char <: int <: long <: float <: double (strongest binding)
~~~

### Lists
~~~
@Typing: defined as a list of elements with the typing Type
[Type] 

@ list initialization
list : [int] = [1,2,3,4];

[] @ empty list

@ Pattern matching on number of list elements
@ [] - 0 elements (empty)
@ l:ls - at least one element l
@ l:ls:lt - at least two elements l, ls
@ etc - default case

case list of:
    [] => E_1;
    l:ls:lt => E_2
    l:ls => E_3;
    default => E_4;
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

& @ bitwise and
| @ bitwise or
^ @ bitwise xor
! @ bitwise not (1 if 0, 0 elsewise)
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
!  @ logical not
~~~

### Operations (Lists)
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
foo{bar1, bar2, bar3}

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
@ Will print primitive values and lists of primitive values (strings as [char])
print()

@ Reads a value of primitive type (including strings) from input
read()
~~~

### Control Flow
~~~
@ Executable files contain a main function which can only be defined once as such

func main(): int
    @ main body
~~~

