#!/bin/bash
for i in 900 2360 7000 13000; do
for j in 900 2360 7000 13000; do
if [[ j -gt i ]]; then
            root -l -b -q "./PlotControl.C(\"${i}\", \"${j}\")"
fi
done;
done;
