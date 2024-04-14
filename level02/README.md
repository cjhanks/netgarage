# Level 02

The goal here is to trigger a `SIGFPE`.

The code already verifies that the second argument is not 0 in this call.

```
    //                vvvvvvvvvvvv
    if (argc != 3 || !atoi(argv[2]))
        return 1;
```

Since we are not using floats, we need to look for other events which can trigger the `SIGFPE`.

In `man signal`, you can find a line which paranthetically says.

> (Also dividing the most negative integer by -1 may generate SIGFPE.)  
> Ignoring this signal might lead to an endless loop.

We can exploit this to store the most negative integer into the first half, and 
-1 into the second half.

```
          vvvvvvvvvvvvvvvvvv
    return abs(atoi(argv[1])) / atoi(argv[2]);
                                ^^^^^^^^^^^^^
```

The `abs` makes it tricky to get the most negative integer, so we have to use 
overflow.  

The binary value of the most positive value would look like: 

`2 << 32 = 0b11111111111111111111111111111111`.  

We want it to be 
`2 << 32 - 1 = 0b100000000000000000000000000000000`.  

**That gives us a solution** of: `-4294967295 -1`.
