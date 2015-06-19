# Basic implementation of RFC862 echo protocol 

Note: This is for academic purposes only - this application is *not* designed for production but for demonstration. For example security issues have not been addressed.

## Doing it by hand

If you don't want to use clion or you want to do things manually:

    $ git clone https://github.com/pmembrey/echo.git
    $ cd echo
    $ mkdir build
    $ cd build
    $ cmake -G "Unix Makefiles" ../
    $ make


Some pre-requisites for the example we'll do in class:

    $ sudo apt-get install tmux tcpdump

First you'll need to run the server in a new terminal. It blocks when it runs:

    $ ./echos  12345

Then in another terminal run:

    $ ./echoc 127.0.0.1 12345 "Hello world!"




