#mpiexec.hydra -n 60 -env OMP_NUM_THREADS 4 -host mic0 -wdir /tmp /tmp/cylinder2d
#mpiexec.hydra -n 60 -env OMP_NUM_THREADS 4 -host mic0 ./cylinder2d
#mpiexec.hydra -n 12 -host crt06 ./bstep3d : -n 12 -env OMP_NUM_THREADS 20 -env KMP_AFFINITY verbose,balanced -host mic0 -wdir /tmp /tmp/bstep3d
mpiexec.hydra -n 12 -host crt06 ./bstep3d : -n 15 -env OMP_NUM_THREADS 16 -env KMP_AFFINITY verbose,balanced -host mic0 -wdir /tmp /tmp/bstep3d
#mpiexec.hydra -n 12 -host crt06 ./bstep3d : -n 10 -env OMP_NUM_THREADS 24 -env KMP_AFFINITY verbose,balanced -host mic0 -wdir /tmp /tmp/bstep3d
