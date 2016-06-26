# pong-over-tcp
Simply pong

**Installation**

pong-over-tcp uses the qt graphics library. Mac OS users can download it via homebrew `brew install qt`. Windows users may have to visit https://www.qt.io/download/.

Once you have qt installed, run qmake to generate the makefile, then make.

**TCP**

pong-over-tcp was inspired by [Vic Hargrave's article](http://vichargrave.com/network-programming-design-patterns-in-c/) on Network Porgramming Design Patterns in C++ and incorporates code from that article (published with APLv2). Any modifications to it, mostly for the purposes of playing pong, are indicated by comments throughout the code.