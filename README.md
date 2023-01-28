# twineq

A project in modern C++ that calculates an approximate solution of the Twin equation and original equation by the Neumann's series method.

## Installation

```bash
git clone git@github.com:sermir2003/twineq.git
cd twineq
mkdir build-directory
cd build-directory
cmake ..
make
```

## Use

Biological and technical data are entered using json files. To create such a file, enter
```bash
./twineq newtask
```
to create a file with default name,  or
```bash
./twineq newtask your_file_name.json
```
if you want to specify a file name.

A detailed description of the task file format and all options will appear later.

To start the calculations, enter
```bash
./twineq solve
```
to use data from a file with a default name,  or
```bash
./twineq solve your_file_name.json
```
if you want to specify a file with data.

## License

The program is licensed under the [MIT License](https://opensource.org/licenses/MIT)

The program contains the [nlohmann/json](https://github.com/nlohmann/json) library which is licensed under the [MIT License](https://opensource.org/licenses/MIT).
