# Fast Hilbert Matrix :arrow_backward: :zap: :red_circle: :zap: :arrow_forward:

Welcome to `fhmdot` (Fast Hilbert Matrix​ :arrow_backward: :zap:
:red_circle: :zap: :arrow_forward:), a quantum number agnostic routine
for differential gate application.

```
 ┌┴─────┴┐ 
 └┬─────┬┘ 
           
  │     │
 ┌┴┐   ┌┴┐ 
─┤A├─ ─┤B├─
 └─┘   └─┘ 
```

## Abstract

`fhmdot` has two components :

* a library dedicated to the gate application <!-- which could be chained (:smirk_cat:) which give a new dimension for quantum gate application simulations.​ -->
* a python interface to quickly use the implementation.

## Design

The interface uses three objects, two similar hierarchical matrices
(`A` and `B`) and one gate `T`.  The goal is to apply and SVD the gate
as fast as possible.

Quantum numbers of local dimension `d` are creating a difficult tensor
optimization problem.  According to the benchmarks, pools of
dimensions `~ 2*d+1` are increasing the application in practice.

## Performance

We benchmark the code using `hyperfine`

* Internal dimension `k = 1, 8, 16, 32, 64, 128, 256, 516, 1028, 2056, 4112, 8224`
* Quantum Numbers `QN='sh-None', 'sh-U1', 'so-None', 'so-U1', 'ldsh-None', 'ldsh-U1'`
* Random data in the fixed structure of `A`, `B` and `T`
* Random data in the different quantum sectors `p = 1, 2, 3, 4, 5, 6, 8, 10`
* Different parallel token and platforms



### In-depth details using the python interface




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
