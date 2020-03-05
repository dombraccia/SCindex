## SPARSE MATRIX GENERATION USING SPLATTER (FOR BENCHMARKING) scIndex ##

# ============================= LOAD LIBRARIES ============================== #

library(Matrix)
library(splatter) #bioc
library(scater)   #bioc

# ==================== SIMULATE MATRICIES USING SPLATTER ==================== #

# Set default params
params <- newSplatParams()
params

# Set multiple parameters at once (using a list)
params <- setParams(params, 
                    update = list(
                      nGenes = 25000, 
                      batchCells = c(1000, 10000, 25000)
                      )
                    )
params

# Running simulation
sim <- splatSimulate(params)
sim

# get count matricies
name <- function(variables) {
  
}


# convert to .mtx format for input to scIndex
