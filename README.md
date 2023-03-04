# Asciify

Asciify is a small, command-line driven program that is capable of converting
images to ascii art. As of now it is still in development.

## Getting started

### Compiling the program

In order to successfully compile _asciify_ you need to have
[stb image](https://github.com/nothings/stb)
library installed on your system somewhere within your compiler's search path
_(which usually includes project's directory)_. This is the only non-standard
dependency of _asciify_.

To compile _asciify_ simply navigate to its directory and execute:

```shell
make
make clean
```

If you wish to have _asciify_ always at hand you can additionally either copy
or link to it in an appropriate directory. For example:

```shell
cp bin/asciify /usr/local/bin
```

or alternatively:

```shell
ln -s bin/asciify /usr/local/bin
```

### Using the program

In order to run _asciify_ simply execute it from within your terminal with a
path to image you want to convert provided as a positional argument. For
example:

```shell
./bin/asciify ~/path/to/my/image.png
```

_asciify_ outputs directly to the standard output, thus if you want to save the
result you may simply redirect the output to a file of your choice:

```shell
./bin/asciify ~/path/to/my/image.png > ~/save/me/HERE.txt
```

or, alternatively you may use the `-o` option:

```shell
./bin/asciify -o ~/save/me/HERE.txt ~/path/to/my/image.png
```

If your image is too big you may scale it down by a factor using:

```shell
./bin/asciify -r<factor> ~/path/to/my/image.png
```
