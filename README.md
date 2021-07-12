# Get Next Line
A function to get one line at a time from a document.

## 🗂 Table of Contents
* [About](#-about)
* [Getting Started](#-getting-started)
* [How to Use](#-how-to-use)
* [42 École | 42 São Paulo](#-42-école--42-são-paulo)

## 🧐 About
This is an implementation of a function the gets one line at a time from a document. The function returns:\
 1: A line has been read;\
 0: End of file has been reached;\
-1: An error happened;\
This project is part of 42 École/ 42 SP curriculum.\
Topics such as memory allocation, and static variables were addressed.

## 🏁 Getting Started
A C compiler such as `gcc` or `clang` is needed.

#### ⚙️ Installing
To compile the code, clone the repo, and run the commad `make`.
```
$ git clone https://github.com/filipebafica/get_next_line.git
$ cd get_next_line
$ make
```
This is going to generate a `get_next_line.a` file that you can compile with your source code.
```
$ gcc my_source.c -I ./get_next_line/includes ./get_next_line/get_next_line.a
$ ./a.out
```
## 🎈 How to Use
Call the function passing a file descriptor, and a pointer that will receive a line from the document.
```
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int   fd;
	char  *line;
  	int   call;
  
  	fd = open("my_document.txt", O_RDONLY);
  	call = 1;
 	while (call > 0)
  	{
		call = get_next_line(fd, &line);
		printf("%s\n", line);
		free (line);
	}
	return (0);
}
```
## 🏫 42 École | 42 São Paulo
42 École is a network of tech schools spread around the world where anyone can learn how to code for free.\
At 42 there are no teachers or classrooms, each student learn from and work with each other (peer-to-peer learning).\
To see more go to https://www.42.fr/ and https://www.42sp.org.br/.

