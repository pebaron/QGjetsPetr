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
# NNPDF31_lo_as_0118
# MMHT2014lo68cl

#seeds: 61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777

N=100000
index=0
for j in 61972970 23354883 88615218 70896900 18669684 71917516 25202807 62914023 20426705 23209777; do 
    for PDF in MMHT2014lo68cl CT14 MMHT2014 NNPDF3.0 NNPDF31_lo_as_0118 NNPDF30_lo_as_0118 NNPDF31_nlo_as_0118 CT18NLO CT14lo NNPDF31_lo_as_0118; do
        for e in 900 2360 7000 13000;do
            sbatch -n1 -o /data/QGjets/QGjetsPetr/run/logs/job_${e}_${N}_${j}_0_${PDF}_hadr ./runherwig.sh $e $N $j 0 $PDF hadr
            for i in 0 25 50 75 100 125 150 175;do 
                sbatch -n1 -o /data/QGjets/QGjetsPetr/run/logs/job_${e}_${N}_${j}_${i}_${PDF}_nohadr ./runherwig.sh $e $N $j $i $PDF nohadr;
                let "index++"
                done;
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

#source /data/QGjets/QGjetsPetr/run/scripts/runherwig.sh 2360  100000 23209777 0 MMHT2014lo68cl hadr
#source /data/QGjets/QGjetsPetr/run/scripts/runherwig.sh 7000  100000 23209777 0 MMHT2014lo68cl hadr
#source /data/QGjets/QGjetsPetr/run/scripts/runherwig.sh 13000 100000 23209777 0 MMHT2014lo68cl hadr

