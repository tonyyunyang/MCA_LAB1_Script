#!/bin/bash
G_ISSUEWIDTH=$1
G_MEMLOAD=$2
G_MEMSTORE=$3
G_MEMPFT=$4
L_ISSUEWIDTH=$5
L_ALU=$6
L_MPY=$7
L_MEM=$8
L_R0=$9
L_B0=${10}

PROGRAM1=ucbqsort
PROGRAM2=convolution_5x5

if [ $# -ne 10 ]; then
	echo "Must provide 10 arguments"
	exit 2
fi

# Edit the configuration file according to input
sed -i.bck -e "s/^RES: IssueWidth     .*/RES: IssueWidth     $G_ISSUEWIDTH/" \
-e "s/^RES: MemLoad        .*/RES: MemLoad        $G_MEMLOAD/" \
-e "s/^RES: MemStore       .*/RES: MemStore       $G_MEMSTORE/" \
-e "s/^RES: MemPft         .*/RES: MemPft         $G_MEMPFT/" \
-e "s/^RES: IssueWidth.0   .*/RES: IssueWidth.0   $L_ISSUEWIDTH/" \
-e "s/^RES: Alu.0          .*/RES: Alu.0          $L_ALU/" \
-e "s/^RES: Mpy.0          .*/RES: Mpy.0          $L_MPY/" \
-e "s/^RES: Memory.0       .*/RES: Memory.0       $L_MEM/" \
-e "s/^REG: \$r0            .*/REG: \$r0            $L_R0/" \
-e "s/^REG: \$b0            .*/REG: \$b0            $L_B0/" \
configuration.mm

# Ensure some basic alphabetical order
if [ $G_ISSUEWIDTH -lt 10 ]; then
	G_ISSUEWIDTH="000$G_ISSUEWIDTH"
elif [ $G_ISSUEWIDTH -lt 100 ]; then
	G_ISSUEWIDTH="00$G_ISSUEWIDTH"
elif [ $G_ISSUEWIDTH -lt 1000 ]; then
	G_ISSUEWIDTH="0$G_ISSUEWIDTH"
fi

if [ $G_MEMLOAD -lt 10 ]; then
	G_MEMLOAD="000$G_MEMLOAD"
elif [ $G_MEMLOAD -lt 100 ]; then
	G_MEMLOAD="00$G_MEMLOAD"
elif [ $G_MEMLOAD -lt 1000 ]; then
	G_MEMLOAD="0$G_MEMLOAD"
fi

if [ $G_MEMSTORE -lt 10 ]; then
	G_MEMSTORE="000$G_MEMSTORE"
elif [ $G_MEMSTORE -lt 100 ]; then
	G_MEMSTORE="00$G_MEMSTORE"
elif [ $G_MEMSTORE -lt 1000 ]; then
	G_MEMSTORE="0$G_MEMSTORE"
fi

if [ $G_MEMPFT -lt 10 ]; then
	G_MEMPFT="000$G_MEMPFT"
elif [ $G_MEMPFT -lt 100 ]; then
	G_MEMPFT="00$G_MEMPFT"
elif [ $G_MEMPFT -lt 1000 ]; then
	G_MEMPFT="0$G_MEMPFT"
fi

if [ $L_ISSUEWIDTH -lt 10 ]; then
	L_ISSUEWIDTH="000$L_ISSUEWIDTH"
elif [ $L_ISSUEWIDTH -lt 100 ]; then
	L_ISSUEWIDTH="00$L_ISSUEWIDTH"
elif [ $L_ISSUEWIDTH -lt 1000 ]; then
	L_ISSUEWIDTH="0$L_ISSUEWIDTH"
fi

if [ $L_ALU -lt 10 ]; then
	L_ALU="000$L_ALU"
elif [ $L_ALU -lt 100 ]; then
	L_ALU="00$L_ALU"
elif [ $L_ALU -lt 1000 ]; then
	L_ALU="0$L_ALU"
fi

if [ $L_MPY -lt 10 ]; then
	L_MPY="000$L_MPY"
elif [ $L_MPY -lt 100 ]; then
	L_MPY="00$L_MPY"
elif [ $L_MPY -lt 1000 ]; then
	L_MPY="0$L_MPY"
fi

if [ $L_MEM -lt 10 ]; then
	L_MEM="000$L_MEM"
elif [ $L_MEM -lt 100 ]; then
	L_MEM="00$L_MEM"
elif [ $L_MEM -lt 1000 ]; then
	L_MEM="0$L_MEM"
fi

if [ $L_R0 -lt 10 ]; then
	L_R0="000$L_R0"
elif [ $L_R0 -lt 100 ]; then
	L_R0="00$L_R0"
elif [ $L_R0 -lt 1000 ]; then
	L_R0="0$L_R0"
fi

if [ $L_B0 -lt 10 ]; then
	L_B0="000$L_B0"
elif [ $L_B0 -lt 100 ]; then
	L_B0="00$L_B0"
elif [ $L_B0 -lt 1000 ]; then
	L_B0="0$L_B0"
fi

# Make output folders (will ignore if it exists)
NEWFOLDER="GIW:$G_ISSUEWIDTH+GML:$G_MEMLOAD+GMS:$G_MEMSTORE+GMPFT:$G_MEMPFT+LIW:$L_ISSUEWIDTH+LALU:$L_ALU+LMPY:$L_MPY+LMEM:$L_MEM+LR0:$L_R0+LB0:$L_B0"
mkdir -p outputs/$NEWFOLDER
cp configuration.mm outputs/$NEWFOLDER/

# Compile and place in seperate folders
for i in 3
do
run $PROGRAM1 -O$i
run $PROGRAM2 -O$i
cp -r output-$PROGRAM1.c/ "outputs/$NEWFOLDER/$PROGRAM1+O$i"
cp -r output-$PROGRAM2.c/ "outputs/$NEWFOLDER/$PROGRAM2+O$i"
done

# Reset the configuration to old state
cp configuration.mm.bck configuration.mm
