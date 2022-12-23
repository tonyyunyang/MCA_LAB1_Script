#!/bin/bash

for a in 4 8 # Global issue width
do
for b in 1 # MemLoad
do
for c in 1 # MemStore
do
for d in 1 # MemPft
do
#for e in 1 2 # IssueWidth.0
#do
for f in 4 # Alu.0
do
for g in 2 # Mpy.0
do
for h in 1 2 # Memory.0
do
for i in 64 # r0
do
for j in 8 # b0
do
bash acompiler.bash $a $b $c $d $a $f $g $h $i $j
#done
done
done
done
done
done
done
done
done
done