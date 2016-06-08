export OMP_NUM_THREADS=1
#mpirun -n 12 ./bstep3d 
mpirun -n 36 ./bstep3d 
#mpirun -n 2 ./bstep3d >log2
#mpirun -n 1 ./bstep3d >log1
