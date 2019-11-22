# Matrix sub-pattern search for querying of single-cell data

This repo was created to track the progress of a CMSC856D final project. Here is the project problem statement:

Consider a large single-cell expression matrix E of dimensions M × N. Here, M
is the number of reference genes, and N is the number of cells. In general, M
is relatively fixed while N grows as experimental techniques yield ever-higher
throughput. One can imagine wanting the ability to search such matrices for
cells exhibiting some interesting pattern of gene expression.
The goal of this project is to develop an efficient query scheme / index to allow
these types of “expression pattern” queries. To simplify the problem, assume
that E is treated as a binary matrix; in each cell, every gene is either expressed
(1) or not expressed (0). Extending basic seach schemes to deal with expression
weights should not be difficult. Now, you are presented with a series of queries
of the form gi ^ ¬gj ^ (gk _ g`) — that is, each query is a logical conjunction of
clauses, where each clause asks for genes to be expressed or not expressed. The
“answer” to such a query is a set of indices R = {ci0 , . . . , ci0+j0} where each index
in R is a cell from E that satisfies the query phrase. The difficulty comes from
the fact that, while you are allowed to “index” E before the queries are issued,
you do not know which specific genes will be involved in the queries. Thus,
the index should be flexible and capable of accelerating queries for very diverse
subsets of genes. If the length of the query in terms of number of genes involved
is q, then a trivial upper bound on the time required to answer the queries
is O(qN). However, we should often be able to do much better. Single-cell
expression matrices are usually very sparse, and we are allowed to process the
queries in any order we wish and are interested only in cells that satisfy all of
the constrants. A trivial lower-bound on the query time is O(|R|) — that is
linear in the size of the output. The goal here is to develop an index that lets
you answer arbitrary queries quickly in expectation, beating the trivial upper
bound for most queries.

More to come

