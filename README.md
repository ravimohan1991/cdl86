# cdl86

cdl86 - Compact Detour Library 86

# Abstract
cdl86 is a simple cross platform detours library written in C for Linux and Windows.

It allows for the interception of x86 and x86_64 C/C++ functions in memory.

[https://journal.lunar.sh/2022/linux-detours.html](https://journal.lunar.sh/2022/linux-detours.html)

The library currently supports two types of function hooks:
* JMP patch - patches origin function with a JMP to detour.
* INT3 patch - places software breakpoint (SWBP) at origin address. Handles control flow to detour.

This project makes use of an internal x86 instruction length disassembly engine.

# API
```C
struct cdl_jmp_patch cdl_jmp_attach(void **target, void *detour);
struct cdl_swbp_patch cdl_swbp_attach(void **target, void *detour);
void cdl_jmp_detach(struct cdl_jmp_patch *jmp_patch);
void cdl_swbp_detach(struct cdl_swbp_patch *swbp_patch);
void cdl_jmp_dbg(struct cdl_jmp_patch *jmp_patch);
void cdl_swbp_dbg(struct cdl_swbp_patch *swbp_patch);
```
The API is documented in more detail in the corresponding header and source
files.

# Example Usage

Assuming we have a function `add()` that is defined as follows:
```
int add(
    __in int x,
    __in int y
)
{
    printf("Inside original function\n");
    return x + y;
}
```

Assuming we want to hook this function with `cdl86` the first step
is to define a function pointer typedef and declare our detour function:

```
typedef int add_t(
    __in int x,
    __in int y
);
add_t* addo = NULL;
```
```
// define detour function
int add_detour(
    __in int x,
    __in int y
)
{
    printf("Inside detour function\n");
    return addo(5,5);
}

```
Then in our `main()` function we create a `cdl_jmp_patch` struct and assign
a value to `addo` (our function pointer to the original function):
```
struct cdl_jmp_patch jmp_patch = {};
addo = (add_t*)add;
```

Finally call `cdl_jmp_attach` as follows:
```
jmp_patch = cdl_jmp_attach((void**)&addo, add_detour);
```

The original function `add` has now been hooked!

To dump debug info from the `cdl_jmp_patch` struct use `cdl_jmp_dbg`.

# Info

The compiler used for this project is [tcc](https://github.com/lunarjournal/tcc).


`cdl.c` - C source file for CDL. <br>
`cdl.h` - CDL header file to include.

Folders:
* `tests` - CDL test suite. Run `make all`.


# Setting up gh pages and Doxy
- [Script](https://github.com/satu0king/Github-Documentation-With-Doxygen)


- ## gh pages
  [blog](https://blog.ediri.io/how-to-create-a-github-gh-pages-branch-in-an-existing-repository)
  
  ![image](https://github.com/ravimohan1991/cdl86/assets/2173654/7777e3d2-14da-46d9-bf12-683bb8ee9d26)

