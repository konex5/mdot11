# Fast Hilbert Matrix :arrow_backward: :zap: :red_circle: :zap: :arrow_forward:

Welcome to `mdot11` (Matrix​ :arrow_backward: :zap:
:red_circle: :zap: :arrow_forward:), a quantum number agnostic routine
for differential gate application interfaced in python.

```
 ┌┴─────┴┐ 
 └┬─────┬┘ 
           
  │     │
 ┌┴┐   ┌┴┐ 
─┤A├─ ─┤B├─
 └─┘   └─┘ 
```

## Abstract

`mdot11` claims to :

* interface the *mdot* library
* provide a way to optimize python code when needed.

## Design

The interface uses three objects, two similar hierarchical matrices
(`A` and `B`) and one gate `T`.  The goal is to apply and SVD the gate
as fast as possible.

Quantum numbers of local dimension `d` are creating a difficult tensor
optimization problem.  According to the benchmarks, pools of
dimensions `~ 2*d+1` are increasing the application in practice.

### In-depth details using the python interface

Once compiled, go to the binary folder and import it

```bash
$ cd binaryFolder
$ python
>>> import mdot_operators
```

## Examples

Examples of iDMRG/iTEBD/DMRG/... can be found in the `./examples/` folder.


## Code Snippets

One line code formatter for C/C++ projects

```bash
black .

nixpkgs-fmt .

clang-format -i $(find . -path "./build*" -prune  -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp")

cmake-format -i $(find . -path "./build*" -prune  -name "*.cmake" -o -name "CMakeLists.txt")
```

## Code Helper

export CPLUS_INCLUDE_PATH=/home/noam/workOn/dmrg/mdot/src
export PYTHONPATH=/home/noam/workOn/dmrg/mdot11/build2/src/pybind:$PYTHONPATH
export PYTHONPATH=/home/noam/workOn/dmrg/pyfhmdot:$PYTHONPATH
