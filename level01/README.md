# Level 01

This level can be solved by simply reading the assembly.

```
08048080 <_start>:
 8048080:       68 28 91 04 08          push   $0x8049128
 8048085:       e8 85 00 00 00          call   804810f <puts>
 804808a:       e8 10 00 00 00          call   804809f <fscanf>
 804808f:       3d 0f 01 00 00          cmp    $0x10f,%eax
;                                       ^^^^^^^^^^^^^^^^^^
 8048094:       0f 84 42 00 00 00       je     80480dc <YouWin>
 804809a:       e8 64 00 00 00          call   8048103 <exit>
```

We can see it compares against the value of `0x10f`.

The numeral value of this is `271`.