# Frusch

Frusch is a custom programming language that is heavily based on C-style programming and Go-style syntax. Frusch is meant to be a language with a higher-level, simple grammar with the benefits of lower level languages. Frusch runs on a custom, simple bytecode.

## Example

As stated in the header, frusch's syntax is heavily inspired by Golang.

```go
use std::alloc
use std::print

enum Result[A, B] {
	Ok(A)
	Err(b)
}

struct Buffer[T] {
	slice *const T
	length int
}

func Buffer[T](slice *const T, length int) {
	let buf *Buffer[T] = alloc(Buffer[T])
	buf.slice = slice
	buf.length = length
	return buf
}

func Buffer[T].at(index int) Result[T, ()] {
	if index >= self.length {
		return Err(())
	}
	return slice[index]
}

func main(argc int, argv *str) int {
	let arr int[3] = {1, 2, 3}
	let buf *Buffer[int] = new Buffer[int](arr, 3)
	print(buf.at(2)) // prints 3
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
