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

Enter the task data

### Format of the TaskFile.json

#### Problem

Description of the problem to be solved

| Value             | Description                                                                                                                      |
|-------------------|----------------------------------------------------------------------------------------------------------------------------------|
| Twin equation     | The twin equation will be solved with a control parameter derived analytically from the kernel data.                             |
| Original equation | The original equation will be solved with the control parameters derived analytically by Theorem 4.3 \[diplom_Bodrov_2013.pdf\]. |

#### Integration method

The method to be used during integration

| Value       | Description                      |
|-------------|----------------------------------|
| Column      | Rectangle method aka Riemann sum |
| Trapezoid   | Trapezoidal method               |
| Simpsons    | Simpson\`s method                |

#### Iteration method

The method by which iterations will be performed

| Value    | Description                                                                                    |
|----------|------------------------------------------------------------------------------------------------|
| Manual   | The integral operator will be applied by finding the sum using a loop at each point each time. |
| Matrix   | The integral operator will be applied by multiplying the vector by the pre-calculated matrix.  |

#### Kernels

To set exponential kernels of fertility and mortality, enter

```json
{
  "kernel": {
    "type": "Exponential",
    "A": "1",
    "B": "1"
  }
}
```

you should also set parameters A and B.

To set rational kernels of fertility and mortality, enter

```json
{
  "kernel": {
    "type": "Rational",
    "A": "1",
    "p": "1"
  }
}
```

you should also set parameters A and p.

#### Other parameters

| Parameter           | Description                                          | Type             |
|---------------------|------------------------------------------------------|------------------|
| b                   | Birth rating                                         | Real             |
| d'                  | Competition rating                                   | Real             |
| r                   | The rounding boundary of the integral `[-r,r]`       | Real             |
| grid count          | Number of calculation points                         | Positive integer |
| iteration count     | Number of iterations of the algorithm                | Positive integer |
| path to result file | The path to the file with the results of the results | String           |

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
