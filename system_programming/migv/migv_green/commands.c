
Post exercise questions

2)

gd -c -fPIC migv1.c

ar rcs libmig_c.a migv1.o

gd -c -fPIC migv_dyn2.c
gd -c -fPIC migv_dyn2_2.c

gd -o libmigv1.so -Wl,--whole-archive libmigv_s.a -Wl,--no-whole-archive -shared migv_dyn2.o
gd -o libmigv2.so -Wl,--whole-archive libmigv_s.a -Wl,--no-whole-archive -shared migv_dyn2_2.o


gd -L. global_exe.c -lmigv_s -lmigv1 -lmigv2 -Wl,-rpath,.

/a.out

received output:

Global Variable address: 0x556924024010
Global Variable address: 0x556924024010
Global Variable address: 0x556924024010

3.a)

gd -c -fPIC src.c

gd src.o -shared -o libsrc.so

gd -L. main.c -Wl,-rpath,.

3.b)

/* int __attribute__((weak))  x = 2; */

gd -c -fPIC src.c

gd src.o -shared -o libsrc.so

gd -L. main.c -Wl,-rpath,.

The address of x from Foo3: 0x7f0acd570028
The address of x after dlopen : 0x55ecba801010


if we do only declaration, we receive:
The address of x from Foo3: (nil)
The address of x after dlopen : (nil)



4)

gd -c -fPIC src1.c
gd -c -fPIC src2.c

gd src1.o -shared -o libsrc1.so
gd src2.o -shared -o libsrc2.so

gd -L. main.c -Wl,-rpath,.


















