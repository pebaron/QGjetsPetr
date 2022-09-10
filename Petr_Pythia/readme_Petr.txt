for j in {1..10}; do sbatch -n1 ./run_pythia.sh QGjets_7TeV ${j} ; done
to modify go 
/disk0/Herwig7/src/pythia8240/examples/
e.g. switch off MPI and ISR
and make nameoffile.cc

dr.Siodmok was using MC_LHQG_dijet

for i in `ls QGjets*MPI*`;do make ${i::-3};done
for i in `ls QGjets*MPI*.cc`;do a=$(echo $i | sed 's/^.*eV//');a=$(echo ${a::-3});echo $a;sed -i 's/.fifo/'"${a}"'.fifo/g' $i ;done

for i in `ls QGjets*.cc`;do make ${i::-3};done


to do:
add grooming techniques for runs with MPI and ISR

sed -i 's/pythia.readString("Random:setSeed = on");/\/\/ PB DEBUG pythia.readString("Random:setSeed = on");/' /disk0/Herwig7/src/pythia8240/examples/QGjets*.cc
sed -i 's/pythia.readString("Random:seed = 0");/\/\/ PB DEBUG pythia.readString("Random:seed = 0");/' /disk0/Herwig7/src/pythia8240/examples/QGjets*.cc


