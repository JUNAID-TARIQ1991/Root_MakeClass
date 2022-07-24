# Root_MakeClass
if you have root already

go to the root/test directory

run .L libevent.so

Tfile *f new Tfile("output.root");

f->ls();

in the list you will see the branches of root file had.

"Branchname"->MakeClass("MyClass");

MyClass.h and MyClss.C will be generated.

A example of how to us Myclass.C for analysis is given in the above Myclass.C file. 
