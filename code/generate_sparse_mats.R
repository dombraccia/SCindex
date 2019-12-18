## SPARSE MATRIX GENERATION USING SPLATTER (FOR BENCHMARKING) scIndex ##

# ============================= LOAD LIBRARIES ============================== #

print("-- loading libraries")
library(Matrix)
library(splatter)               #bioc
library(scater)                 #bioc
library(SingleCellExperiment)   #bioc
library(tictoc)

# ==================== SIMULATE MATRICIES USING SPLATTER ==================== #
print("-- simulating some sparse matricies")
tic()

# Set default params
params <- splatter::newSplatParams() # with default params
#dropout_index = 3	#3 for 60% dropout, 5 for 80% dropout, ...

# Set multiple parameters at once (using a list)
set_params <- function(num_genes, num_cells, dropout_index, cell_types) {
  params <- splatter::setParams(params, 
                    update = list(
                      nGenes = num_genes, 
                      batchCells = num_cells,
                      group.prob = cell_types,
                      dropout.shape = -1,
                      dropout.type = "batch",
                      dropout.mid = dropout_index # controls sparsity
                      )
                    )
}

# ============================ RUN SIMULATIONS ============================== #

# initialize parameters
param_set <- list(num_cells = c(1e6, 1e7))
celltype_ratios <- c(0.3, 0.2, 0.1, 0.2, 0.1, 0.1)

# simulate counts
for (p in 1:length(param_set$num_cells)) {
  print("--- set up current batch of parameters")
  params <- set_params(num_genes = 20000, 
                       num_cells = param_set$num_cells[p],
                       cell_types = celltype_ratios,
                       dropout_index = 5) # gives ~ 1.5% density
  current_params <- setParams(params)
  current_sim <- splatter::splatSimulate(current_params)

  print("--- get count mats")
  current_counts <- counts(current_sim) # try truecounts() to act
  sum(current_counts > 0)/length(current_counts)
  current_sparse <- Matrix(current_counts, sparse = TRUE)

  print("--- convert to .mtx format for input to scIndex")
  filename <- paste0("../data/", params@nGenes, "genes_", param_set[["num_cells"]][p], "cells.mtx")
  Matrix::writeMM(obj = current_sparse, file = filename)

  # remove all intermediate variables to save memory (if necessary)
  #rm(current_counts, current_params, current_sim, current_sparse)
}
toc()
