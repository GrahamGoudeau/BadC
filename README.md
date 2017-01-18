# Bad C
Examples of how NOT to write C, with plenty of comments along the way to explain why.

## How to use this repo
The examples in this repo are based around the idea of modeling a "User".  This could be a User of a website, of a computer, etc.

Users have a field for their age, their name, and what kind of permissions they have.

Before looking at anything else, take a look at `user.h` and get a feel for what kind of functions the interface exposes to you.  It is not too important to look at `user.c`, but if you are curious you can.  Then you can look at some of the files which are *clients* of this interface, and observe how they use the interface badly.

## Building things
This repo contains a Makefile which has some useful rules you can execute.  These include:

### Non-executable
* `make syntax` - run the C preprocessor stage on `user.h`.  This will dump the processed text in a new file called `afterProcessor.c`.  The resulting file is pretty massive, but if you look at line 1700 (roughly) and afterwards, you can see that the `T` type definitions have been simply expanded into `User_T`.

### Executable
* `make` - generate all executable files listed below. This does not run the preprocessor as described above.
* `make callStack` - produces `./callStack` which shows how pointing to the function call stack can go wrong
* `make memLeak` - produces `./memLeak` which shows a common pattern that produces a memory leak
* `make doubleFree` - produces `./doubleFree` which attempts to free the same memory twice
* `make passByRef` - produces `./passByRef` which (tries) to pass a User_T around by reference
* `make pointerInit` - produces `./pointerInit` which fails to correctly initialize a UserPermissions pointer
