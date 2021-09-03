# How to make a .deb package

This tutorial shows the most basic way of packaging a simple already-compiled program.

Decide on the name of your package. Standard debian notation is all lowercase in the following format:<br>
`<project>_<major version>.<minor version>-<package revision>`<br>
For example, you could name your first package...<br>
`helloworld_1.0-1`<br>
Create a directory to make your package in. The name should be the same as the package name.<br>
`mkdir helloworld_1.0-1`<br>
Pretend that the packaging directory is actually the root of the file system. Put the files of your program where they would be installed to on a system.
```
mkdir helloworld_1.0-1/usr
mkdir helloworld_1.0-1/usr/local
mkdir helloworld_1.0-1/usr/local/bin
cp "~/Projects/Hello World/helloworld" helloworld_1.0-1/usr/local/bin
```
Now create a special metadata file with which the package manager will install your program...
```
mkdir helloworld_1.0-1/DEBIAN
gedit helloworld_1.0-1/DEBIAN/control
```
Put something like this in that file...
```
Package: helloworld
Version: 1.0-1
Section: base
Priority: optional
Architecture: i386
Depends: libsomethingorrather (>= 1.2.13), anotherDependency (>= 1.2.6)
Maintainer: Your Name <you@email.com>
Description: Hello World
 When you need some sunshine, just run this
 small program!
 
```
 (the space before each line in the description is important)
Now you just need to make the package:<br>
`dpkg-deb --build helloworld_1.0-1`<br>

And you're done! <br>
That wasn't so hard, was it?<br>
Just so you know, there are a lot more fields in the metadata file, and even extra whole configuration files which you can have dpkg work with, which I left out -- this is the bare bones of what's required.
<br><br>
Thanks to bobbocanfly for the following: If you happen to be looking for how to let the Ubuntu repositories include your project, you need to follow this guide: https://wiki.ubuntu.com/PackagingGuide/Complete. Then get in touch with the MOTU team at #ubuntu-motu on irc.freenode.net and ubuntu-motu@lists.ubuntu.com.