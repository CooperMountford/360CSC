Cooper Mountford
V00894081

Doubly Linked List ReadMe:
I think this is the third time I've had to write a DLL in C but this time gave me the most frustrations by far.

   swap():
The swap should work according to the diagrams of its code that I've drawn but it doesn't.

   shift_left():
Instead (when run 3 times), it changes the data of the first node to 0 and the data of the next two nodes to memory addresses.
As far as I can tell, this should not happen because the supplied erase() code is correctly implemented but refuses to work.
Even when I tried running my friend's code which works perfectly on his system, I get the same behaviour.
I checked that it wasn't caused by my concat() function and the issue is present on all 3 environemnts



Shell ReadMe:

The bulk of the code was sourced from Stephen Brennan's tutorial on writing a shell in C
I followed along with the tutorial, copying the important bits and changing the notes and variables/whitespace
   to match how I write C code



