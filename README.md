# Fast Hilbert Matrix :arrow_backward: :zap: :black_circle: :zap: :arrow_forward:

Welcome to `fhmdot` (Fast Hilbert Matrix​ :arrow_backward: :zap: :black_circle: :zap: :arrow_forward:), a quantum number agnostic routine for differential gate application.

## Abstract

`fhmdot` has tow different component : 

* a routine library <!-- which could be chained (:smirk_cat:) which give a new dimension for quantum gate application simulations.​ -->
* a python interface to help user enter the data production.

## Performance

We benchmark the code using `hyperfine`

* Internal dimension `k = 1, 8, 16, 32, 64, 128, 256, 516, 1028, 2056, 4112, 8224`.

* Random data but fixed structure of `A`, `B` and `T`
* Different quantum structure
* Different parallel token and platforms

#### Results



## Design

The interface uses three objects, two similar hierarchical matrices (`A` and `B`) and one gate `T`.

### In-depth details using the python interface



  



