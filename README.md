# Frusch

Frusch is a custom programming language that is heavily based on C-style programming and Go-style syntax. Frusch is meant to be a language with a higher-level, simple grammar with the benefits of lower level languages. Frusch runs on a custom, simple bytecode.

## Example

As stated in the header, frusch's syntax is heavily inspired by Golang.

```go
use std.alloc.alloc
use std.io.print

enum Result[A, B] {
	Ok(ok A)
	Err(err B)
}

struct Buffer[T] {
	slice *const T
	length int
}

func Buffer[T].new(slice *const T, length int) *Buffer[T] {
	let buf *Buffer[T] = alloc(Buffer[T])
	buf.slice = slice
	buf.length = length
	return buf
}

func Buffer[T].at(self, index int) Result[T, ()] {
	if index >= self.length {
		return Result.Err(())
	}
	return Result.Ok(slice[index])
}

func main(argc int, argv *str) int {
	let arr int[3] = {1, 2, 3}
	let buf *Buffer[int] = Buffer[int].new(arr, 3)
	let i Result[int, ()] = buf.at(2)
	if i is Result.Err {
		print("Index out of bounds")
	} else {
		print("buf[2] = ", i.ok)
	}
	return 0
}
```

## Building

As of now frusch requires:

- `gcc (or some modern C compiler)`
- `ar`
- `make`

After installing the following dependencies and entering the project directory, run the following commands:

```sh
make ./bin/frusch # This installs the frusch binary (used to compile files)
make ./bin/fvm    # This installs the fvm binary (used to interpret the bytecode) 
```
