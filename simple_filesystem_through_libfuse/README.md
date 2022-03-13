A simple filesystem through libfuse
======

Tried to write a simple file system through [libfuse](https://github.com/libfuse/libfuse) library

## libfuse introduction and installation 

1. libfuse is a "extention" model, it has some kernel module integrated with kernel source tree and some user space code, with API exposed by libfuse, users can define their own file system through this library.
2. use case:
   - mount without root permission
   - define user level file system which is ease-to-use API for their own product, e.g. providing linux easy file system level access to their back-end products
   - customize some logging etc for a certain operation
3. installation:
   - referring [libfuse installation guide](https://github.com/libfuse/libfuse#installation) for library usage
   - run `sudo ldconfig` to make sure it is correctly loaded

## What is done in this simple program 

1. minimal efforts for setting up a file system
2. only three APIs are implemented:
   - getattr 
   - readdir
   - read
3. dummy file system with basic functionality - a in-memory root directory with two files inside the directory, readable files

## Example commands and output

### build

```
gcc ssfs.c -o ssfs `pkg-config fuse3 --cflags --libs`
```

### run 

```bash
mkdir ./mp
./ssfs -f ./mp
```

   in another bash shell

```
gefei@gefei-ubuntu:~/wonderful/Write-A-Simple/simple_filesystem_through_libfuse$ ls -l
total 24
drwxr-xr-x 2 gefei gefei     0 3月  13 17:09 mp
-rwxrwxr-x 1 gefei gefei 17536 3月  13 17:08 ssfs
-rw-rw-r-- 1 gefei gefei  1912 3月  13 16:54 ssfs.c
gefei@gefei-ubuntu:~/wonderful/Write-A-Simple/simple_filesystem_through_libfuse$ ls mp -l
total 0
-rw-r--r-- 1 gefei gefei 1024 3月  13 17:09 file349
-rw-r--r-- 1 gefei gefei 1024 3月  13 17:09 file54
gefei@gefei-ubuntu:~/wonderful/Write-A-Simple/simple_filesystem_through_libfuse$ cat mp/file349
Hello world from File349!
gefei@gefei-ubuntu:~/wonderful/Write-A-Simple/simple_filesystem_through_libfuse$ cat mp/file54
Hello world from File54!
```



### Reference 

[Writing a Simple Filesystem Using FUSE in C](https://www.maastaar.net/fuse/linux/filesystem/c/2016/05/21/writing-a-simple-filesystem-using-fuse/) by Mohammed Q. Hussain

the referred doc is out-of-date, EIO may be seen because of the improper `stat` structure during readdir call.

