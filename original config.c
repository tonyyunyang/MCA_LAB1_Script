
#-----------------------------------------------------------------------------#
#                            Global configuration                             #
#-----------------------------------------------------------------------------#

# Overall issue width. This is the number of syllables that can be executed
# per cycle, regardless of clustering. This must be at least 2.
RES: IssueWidth     4

# The following parameters specify the number of 32-bit connections to the data
# cache, for memory loads, stores, and prefetches respectively.
RES: MemLoad        1
RES: MemStore       1
RES: MemPft         1

# The following parameter specifies the number of clusters to use. It can be
# 1, 2 or 4. 
# NOTE: do NOT uncomment this line. It is commented because the number of 
# clusters is confusingly not actually part of the machine model, but
# a compiler flag. The compile script will search for this line and use it to
# set the -width compiler flag accordingly.
# We only work with a single cluster,so DO NOT CHANGE THIS PARAMETER.
# ***Clusters***    1

#-----------------------------------------------------------------------------#
#                           Cluster 0 configuration                           #
#-----------------------------------------------------------------------------#

# The following parameter specifies the maximum number of syllables that can be
# decoded by this cluster per cycle. This must be equal to the value of 
# RES:IssueWidht in global configuration.
RES: IssueWidth.0   4

# The following parameter specifies the number of ALU syllables that can be
# executed by this cluster per cycle.
RES: Alu.0          4

# The following parameter specifies the number of multiply syllables that can
# be executed by this cluster per cycle.
RES: Mpy.0          2

# The following parameter specifies the number of memory syllables that can be
# executed by this cluster per cycle.
RES: Memory.0       1

# The following two parameters specify the number of inter-cluster
# communication syllables that can be executed by this cluster per cycle. A
# register move from one cluster to another consists of a SEND syllable in the
# source cluster and a RECV syllable in the destination cluster. The number of
# SEND instructions per cycle in this cluster are governed by CopySrc, while
# RECV is governed by CopyDst.
# We only work with a single cluster,so DO NOT CHANGE THIS PARAMETER.
RES: CopySrc.0      0
RES: CopyDst.0      0

# The following parameter specifies the number of 32-bit general purpose
# registers available to this cluster.
REG: $r0            64

# The following parameter specifies the number of single bit condition
# registers available to this cluster.
REG: $b0            8

#=============================================================================#
#            For the assignments, don't change anything below here            #
#=============================================================================#

# Functional unit latencies for cluster 0.
DEL: AluR.0         0
DEL: Alu.0          0
DEL: CmpBr.0        0
DEL: CmpGr.0        0
DEL: Select.0       0
DEL: Multiply.0     1
DEL: Load.0         1
DEL: LoadLr.0       1
DEL: Store.0        0
DEL: Pft.0          0
DEL: CpGrBr.0       0
DEL: CpBrGr.0       0
DEL: CpGrLr.0       0
DEL: CpLrGr.0       0
DEL: Spill.0        0
DEL: Restore.0      1
DEL: RestoreLr.0    1

CFG: Quit           0
CFG: Warn           0
CFG: Debug          0
