st - simple terminal
--------------------
This is a fork of [charlesdaniels'](https://github.com/charlesdaniels/st) fork of [st](https://st.suckless.org/).
Thanks to *charlesdaniels* and [saitoha](https://gist.github.com/saitoha/70e0fdf22e3e8f63ce937c7f7da71809) it supports sixels graphics.

Requirements
------------
In order to build st you need the Xlib header files.

Installation
------------
Edit config.mk to match your local setup (st is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install st (if
necessary as root):

    make clean install


Running st
----------
If you did not install st with make clean install, you must compile
the st terminfo entry with the following command:

    tic -sx st.info

See the man page for additional details.

