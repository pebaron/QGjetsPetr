#!/bin/bash
for i in 900 2360 7000 13000; do
for j in 900 2360 7000 13000; do
if [[ j -gt i ]]; then
            for k in 02 04 06 08 10; do
            root -l -q "./PlotControl.C(\"${i}\", \"${j}\", \"${k}\")"
            done
fi
done;
done;
