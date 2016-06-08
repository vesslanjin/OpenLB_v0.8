# OpenLB with AVX512

This article provides a recipe for how to obtain, configure, compile, and run optimized version of olb-0.8r0 with cylinder2d workload on Intel® Xeon® processors and Intel® Xeon Phi™ processors.
The source for this version of OpenLB can be downloaded from: https://github.com/vesslanjin/OpenLB_for_KNL

optimization we made to get the best performance on CPU/Xeon Phi.

* Inter-procedural Optimization by Intel Compiler 
* Fine tune the MPI processes and Hybrid configuration
* Make good usage of MCDRAM by numactl 
* PGO optimization for Intel Compiler
* Optimized hot function (bgkCollison which takes 30% time) by AVX512 and FMA intrinsics

other modifications:
Enlarge the lattice size of cylinder2d to get benefit from many core based on the example workload cylinder2d. 
Added time collection function to collect the time for computation, note there is a lot of serial computation in first iteration(iT=0) and takes a lot of time, it’s better to exclude this part of time for performance test (details please see examples/cylinder2d/cylinder2d.cpp)

you may get a official copy of openlb_v0.8 from [Link](https://github.com/vesslanjin/OpenLB_v0.8)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisities

To build this package, install the Intel® MPI Library 5.1.3.181 and Intel® C++ Composer XE 2016 or higher products on your host system.  Your host system must also have the Intel® MPSS for Linux* installed (installed separately from Intel® C++ Compiler XE).

### Download the source code

```
mkdir openlb_v0.8
cd openlb_v0.8
git clone  https://github.com/vesslanjin/OpenLB_v0.8
```

### Setup Intel Software tools
```
source /opt/intel/impi/<version>/bin64/mpivars.sh
source /opt/intel/composer_xe_<version>/bin/compilervars.sh intel64
```

### Compile and run application

* Build the static library libolb.a and executable for the Intel® Xeon® processor, Modify the Makefile.inc in the openlb directory, setup compile and compile options and parallel mode (here we use pure MPI version)

Change compile option in Makefile.inc
```
CXX     := mpiicpc
OPTIM   := -O3 -g -Wall  -fp-model fast=2 -xCORE_AVX2 -fma  -ipo
ARPRG   := xiar
PARALLEL_MODE   := MPI

```

Then generate the library and executable for cylinder2d in example/cylinder2d
```
cd openlb_v0.8
make clean & make
cd example/cylinder2d/
make
```

Now we have cylinder2d in examples/cylinder2d/, run the application on Intel® Xeon® processor
```
mpirun –np 36 ./cylinder2d
```

* Build the static library libolb.a and executable for the Intel® Xeon Phi™ processor
We will demonstrate how to use Profile-Guided Optimization (PGO) optimization, first to use –prof-gen and let compiler creates and links an instrumented program from source code. Details for Intel Compiler PGO optimization are discussed in this [Link](https://software.intel.com/en-us/node/512789)

change compile options in Makefile.inc:

```
CXX             := mpiicpc
OPTIM          := -O3 -g -Wall -xMIC-AVX512  -fp-model fast=2 -fma -ipo -prof-gen –DWITH_AVX512
ARPRG   := xiar
PARALLEL_MODE   := MPI
```

Then compile and run the application on Intel® Xeon Phi™ processor.

```
make clean & make
cd examples/cylinde2d
make
numactl --membind=1 mpirun –np 272 ./cylinder2d
```

The instrumented program generates several dynamic information file on source code file basis in the same location of the source code, which will be used in the second compilation. In this second compilation, we need to change the compiler option for Intel® Xeon Phi™ processor, replace the –prof-gen to –prof-use

now change the options again in order to utilize the dynamic information file
```
CXX             := mpiicpc
OPTIM          := -O3 -g -Wall -xMIC-AVX512  -fp-model fast=2 -fma -ipo -prof-use –DWITH_AVX512
ARPRG   := xiar
PARALLEL_MODE   := MPI
```

Final Run:
```
numactl --membind=1 mpirun –np 272 ./cylinder2d
```


## Performance

TO BE ADDED. 


## Contributing

Contacts:
[Jun Jin] (jun.i.jin@intel.com)
[Shan Zhou](shan.zhou@intel.com)

## Versioning

The version is based on official openlb_v0.8, you may get a official copy of openlb_v0.8 from [Link](http://www.optilb.com/openlb/wp-content/uploads/2013/11/olb-0.8r0.tgz)



## License

This project is licensed under the GPL2 License



