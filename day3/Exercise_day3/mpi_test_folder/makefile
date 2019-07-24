#######################################################################	

all: 	broadcast.exec allreduce.exec scatter.exec mpi_pi.exec

#######################################################################	

## Broadcast
broadcast.exec: broadcast.cpp
	mpicxx -O3 broadcast.cpp -o broadcast.exec

## Reduce
allreduce.exec: allreduce.cpp
	mpicxx -O3 allreduce.cpp -o allreduce.exec

## Scatter
scatter.exec: scatter.cpp
	mpicxx -O3 scatter.cpp -o scatter.exec

## Calculating pi
mpi_pi.exec: mpi_pi.cpp
	mpicxx -O3 mpi_pi.cpp -o mpi_pi.exec


#######################################################################	
	
clean :
	rm -f *.exec
