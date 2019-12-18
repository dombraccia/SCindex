## SPARSE MATRIX GENERATION USING SPLATTER (FOR BENCHMARKING) scIndex ##

# ============================= LOAD LIBRARIES ============================== #

print("-- loading libraries")
library(Matrix)
library(splatter)               #bioconductor
library(scater)                 #bioconductor
library(SingleCellExperiment)   #bioconductor
library(tictoc)

# ==================== SIMULATE MATRICIES USING SPLATTER ==================== #
print("-- simulating some sparse matricies")

# create set_params function to take various input paramters for simulating counts
params <- splatter::newSplatParams() # with default params
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

# simulate counts varying number of cells
param_set_nCells <- list(num_cells = c(100, 1000, 10000, 1e+05))
celltype_ratios <- c(0.3, 0.2, 0.1, 0.2, 0.1, 0.1)
for (p in 1:length(param_set_nCells$num_cells)) {
  print(paste0("--- set up current batch of parameters: nCells = ", param_set_nCells$num_cells[p]))
  params <- set_params(num_genes = 20000, 
                       num_cells = param_set_nCells$num_cells[p],
                       cell_types = celltype_ratios,
                       dropout_index = 5) # gives ~ 98.5% sparsity
  current_params <- splatter::setParams(params)
  current_sim <- splatter::splatSimulate(current_params)

  print("--- get count mats")
  current_sparse <- Matrix(counts(current_sim), sparse = TRUE) # try truecounts() to act

  print("--- convert to .mtx format for input to scIndex")
  filename <- paste0("../data/", params@nGenes, "genes_", 
                     params@nCells, "cells_", 
                     params@dropout.mid, "dropindex", 
                     ".mtx")
  Matrix::writeMM(obj = current_sparse, file = filename)

  # remove all intermediate variables to save memory (if necessary)
  rm(current_params, current_sim, current_sparse, filename)
}
toc()

# simulate counts varying sparsity
param_set_dropout_index <- list(dropout_index = c(5, 4, 3, 2, 1)) # used to sim sparsity
for (d in 1:length(param_set_dropout_index$dropout_index)) {
  print(paste0("--- set up current batch of parameters: dropout_index = ", param_set_dropout_index$dropout_index[d]))
  params <- set_params(num_genes = 20000, 
                       num_cells = 68000, # keeping the same as pbmc_68k
                       cell_types = celltype_ratios,
                       dropout_index = param_set_dropout_index[["dropout_index"]][d])
  current_params <- splatter::setParams(params)
  current_sim <- splatter::splatSimulate(current_params)

  print("--- get count mats") 
  current_sparse <- Matrix(counts(current_sim), sparse = TRUE) # try truecounts() to act

  print("--- convert to .mtx format for input to scIndex")
  filename <- paste0("../data/", params@nGenes, "genes_", 
                     params@nCells, "cells_", 
                     params@dropout.mid, "dropindex", 
                     ".mtx")
  Matrix::writeMM(obj = current_sparse, file = filename)

  # remove all intermediate variables to save memory (if necessary)
  rm(current_params, current_sim, current_sparse, filename)
}
