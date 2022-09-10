#!/bin/bash

# PDF sets: 
# MMHT2014lo68cl CT14 MMHT2014 NNPDF3.0 NNPDF31_lo_as_0118 NNPDF30_lo_as_0118 NNPDF31_nlo_as_0118 CT18NLO CT14lo NNPDF31_lo_as_0118

# CT14
# MMHT2014
# NNPDF3.0
# NNPDF31_lo_as_0118
# NNPDF30_lo_as_0118	
# NNPDF31_nlo_as_0118	
# CT18NLO
# CT14lo
# NNPDF31_lo_as_0118 - this did not worked
# MMHT2014lo68cl

#seeds: 61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777

#N=500000
N=500000
index=0
#for j in 61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777; do 
#seeds for now 61972970 23354883 88615218 70896900 18669684
for j in 61972970; do
#for j in 71917516 25202807 62914023 20426705 23209777; do
    for PDF in MMHT2014lo68cl; do 
    #for PDF in PDF4LHC15_nlo_mc MMHT2014lo68cl CT14lo; do
        #CT14 MMHT2014 NNPDF3.0 NNPDF31_lo_as_0118 NNPDF30_lo_as_0118 NNPDF31_nlo_as_0118 CT18NLO; do
        for e in 900 2360 7000 13000;do
	    for v in 0.0
            sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_test.sh $e $N $j 0 $PDF hadr
            # for now noMPI_noISR sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_noMPI_noISR_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_test_noMPI_noISR.sh $e $N $j 0 $PDF hadr
            # original echo sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig.sh $e $N $j 0 $PDF hadr
            #PB for now sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_no_ISR.sh $e $N $j 0 $PDF hadr
            #PB for now sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_no_MPI.sh $e $N $j 0 $PDF hadr
            #PB for now sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_no_MPI_no_ISR.sh $e $N $j 0 $PDF hadr
            #PB for now sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig_nohadr_withMPI_and_part_shower.sh $e $N $j 0 $PDF hadr

            ## no hadr part
            #for i in 0 25 50 75 100 125 150 175;do 
            #    sbatch -n1 -o /disk0/QGjetsPetr/run/logs/job_${e}_${N}_${j}_${i}_${PDF}_nohadr ./runherwig_test.sh $e $N $j $i $PDF nohadr;
            #    let "index++"
            #    done;
        done;
        #a=$(squeue | wc -l)
        #if [ "$a" -gt 100 ]; then
        #    echo "Put you in to sleep for 1 hour"
        #    sleep 1h;
        ##else
        #fi
    done;
done;

echo "Summited ${index} jobs."

#source /disk0/QGjetsPetr/run/scripts/runherwig.sh 2360  100000 23209777 0 MMHT2014lo68cl hadr
#source /disk0/QGjetsPetr/run/scripts/runherwig.sh 7000  100000 23209777 0 MMHT2014lo68cl hadr
#source /disk0/QGjetsPetr/run/scripts/runherwig.sh 13000 100000 23209777 0 MMHT2014lo68cl hadr

