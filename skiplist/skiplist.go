package main

import (
	"fmt"
	"github.com/bradleyjkemp/memviz"
	"strconv"
	"strings"
	"bufio"
	"os"
	"bytes"
	"time"
	"math"
)

// cell structure
type cell struct {
	cellid int
	next *cell
	skip *cell
}

// skip lists
type skiplist struct {
	list map[int]*cell
	counts map[int]int
	skipval int
}

func buildSkipList(filepath string, skipval int) *skiplist {

	// create empty skiplist
	skip_obj := new(skiplist)
	skip_obj.skipval = skipval
	skip_obj.list = make(map[int]*cell)
	skip_obj.counts = make(map[int]int)

	// parse input file
	
	file, err := os.Open(filepath)

	if err != nil {
		fmt.Println(err)
        panic(err)
	}
	
    defer file.Close()
	
	fscanner := bufio.NewScanner(file)

	//  skip the two header lines
	fscanner.Scan()
	h1 := fscanner.Text()
	fmt.Println("header", h1)

	fscanner.Scan()
	h2 := fscanner.Text()
	fmt.Println("header", h2)

	// get the row summary
	fscanner.Scan()
	words := strings.Fields(fscanner.Text())

	fmt.Println("words", words)

	rowdim, _ := strconv.Atoi(words[0])
	coldim, _ := strconv.Atoi(words[1])
	rowlength, _ := strconv.Atoi(words[2])

	fmt.Println("rowdim, coldim, rowlength", rowdim, coldim, rowlength)

	skip_list_last_tracker := make(map[int]*cell)
	skip_list_skip_tracker := make(map[int]*cell)

	for fscanner.Scan() {

		words := strings.Fields(fscanner.Text())

		m, err := strconv.Atoi(words[0])
		if err != nil {
			panic("index error!")
		}

		n, err := strconv.Atoi(words[1])
		if err != nil {
			panic("index error!")
		}

		tmp_cell := new(cell)
		tmp_cell.cellid = n

		_, ok := skip_list_last_tracker[m]
		if ok {
			last_cell := skip_list_last_tracker[m]
			last_cell.next = tmp_cell
			skip_list_last_tracker[m] = tmp_cell

			last_skip_cell := skip_list_skip_tracker[m]
			if int(last_skip_cell.cellid / skipval)  !=  int(n / skipval) {
				last_skip_cell.skip = tmp_cell
				skip_list_skip_tracker[m] = tmp_cell
			}

		} else {
			skip_list_last_tracker[m] = tmp_cell
			skip_list_skip_tracker[m] = tmp_cell
			skip_obj.list[m] = tmp_cell
		}

		skip_obj.counts[m]++
	}

	return skip_obj
}

func (sl skiplist) union(genea, geneb int) *cell {
	
	cella, oka := sl.list[genea] 
    if !oka {
		panic(oka)
	} 

	cellb, okb := sl.list[geneb]
	if !okb {
		panic(okb)
	}

	union_cells := new(cell)
	var last_cell *cell = union_cells
	var last_skip *cell = union_cells

	for cella != nil && cellb != nil {
		tmp_cell := new(cell)

		if cella.cellid < cellb.cellid {
			
			last_cell.cellid = cella.cellid
			last_cell.next = tmp_cell
			last_cell = tmp_cell
			
			if int(last_skip.cellid / sl.skipval) != int(cella.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}

			cella = cella.next

		} else if cella.cellid > cellb.cellid {

			last_cell.cellid = cellb.cellid
			last_cell.next = tmp_cell
			last_cell = tmp_cell

			if int(last_skip.cellid / sl.skipval) != int(cellb.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}
			
			cellb = cellb.next

		} else if cella.cellid == cellb.cellid {

			last_cell.cellid = cella.cellid
			last_cell.next = tmp_cell
			last_cell = tmp_cell

			if int(last_skip.cellid / sl.skipval) != int(cella.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}

			cella = cella.next
			cellb = cellb.next
		}
	}

	if cella != nil {
		for cella != nil {
			tmp_cell := new(cell)
				
			last_cell.cellid = cella.cellid
			
			if int(last_skip.cellid / sl.skipval) != int(cella.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}

			cella = cella.next

			if cella != nil {
				last_cell.next = tmp_cell
				last_cell = tmp_cell
			}
		}
	}

	if cellb != nil {
		for cellb != nil {
			tmp_cell := new(cell)
				
			last_cell.cellid = cellb.cellid
			
			if int(last_skip.cellid / sl.skipval) != int(cellb.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}

			cellb = cellb.next

			if cellb != nil {
				last_cell.next = tmp_cell
				last_cell = tmp_cell
			}
		}
	}

	return union_cells
} 

func (sl skiplist) intersect(genea, geneb int) *cell {
	cella, oka := sl.list[genea] 
    if !oka {
		panic(oka)
	} 

	cellb, okb := sl.list[geneb]
	if !okb {
		panic(okb)
	}

	fmt.Println("cella", cella)
	fmt.Println("cellb", cellb)

	intersect_cells := new(cell)
	var last_cell *cell = intersect_cells
	var last_skip *cell = intersect_cells

	for cella != nil && cellb != nil {
		tmp_cell := new(cell)

		fmt.Println("loop - cella, cellb", cella, cellb)

        if cella.cellid == cellb.cellid {
			fmt.Println("cella = cellb")

			last_cell.cellid = cella.cellid
			last_cell.next = tmp_cell
			last_cell = tmp_cell

			if int(last_skip.cellid / sl.skipval) != int(cella.cellid / sl.skipval) {
				last_skip.skip = tmp_cell
				last_skip = tmp_cell
			}

			cella = cella.next
			cellb = cellb.next

        } else if cella.cellid < cellb.cellid {

			fmt.Println("loop - cella < cellb", cella, cellb)

            if int(math.Abs(float64(cella.next.cellid - cellb.cellid))) >= sl.skipval {

				fmt.Println("diff > skipval")

				for cella.cellid <= cellb.cellid {

					if cella.next.cellid > cellb.cellid {
						break
					}

					fmt.Println("skipping all the way")
					fmt.Println("cella", cella)
					fmt.Println("cellb", cellb)

					if cella.skip != nil && cella.skip.cellid <= cellb.cellid {
						cella = cella.skip
					} else if cella.next != nil && cella.next.cellid <= cellb.cellid {
						cella = cella.next
					}
				}
			}
		} else if cella.cellid > cellb.cellid {

			fmt.Println("loop - cella > cellb", cella, cellb)

            if int(math.Abs(float64(cellb.next.cellid - cella.cellid))) >= sl.skipval {

				fmt.Println("diff > skipval")

				for cellb.cellid <= cella.cellid {

					if cellb.next.cellid > cella.cellid {
						break
					}

					fmt.Println("skipping all the way")
					fmt.Println("cella", cella)
					fmt.Println("cellb", cellb)

					if cellb.skip != nil && cellb.skip.cellid <= cella.cellid {
						cellb = cellb.skip
					} else if cellb.next != nil && cellb.next.cellid <= cella.cellid {
						cellb = cellb.next
					}
				}
			}
		}
	}

	return intersect_cells
}

func main() {

	start := time.Now()
	skips := buildSkipList("/mnt/c/Users/jayar/Desktop/projects/SCindex/filtered_matrices_mex/hg19/matrix.mtx", 100)
	end := time.Now().Sub(start)
	fmt.Println(end.Nanoseconds()/1000000)
	fmt.Println("end building")
	
	// fmt.Println(skips.counts)
	// fmt.Println(skips.list[32709])
	// fmt.Println(skips.list[32709].cellid)
	// fmt.Println(skips.list[32709].next)
	// fmt.Println(skips.list[32709].next.cellid)
	// fmt.Println(skips.list[32709].next.next.cellid)
	// fmt.Println(skips.list[32709].next.next.next.cellid)

	// 16374:3 23576:4

	buf := &bytes.Buffer{}
	memviz.Map(buf, skips.list[16374])
	fmt.Println(buf.String())

	buf2 := &bytes.Buffer{}
	memviz.Map(buf2, skips.list[23576])
	fmt.Println(buf2.String())

	ucell := skips.union(16374, 23576)
	buf3 := &bytes.Buffer{}
	memviz.Map(buf3, ucell)
	fmt.Println(buf3.String())

	icell := skips.intersect(32709, 23576)
	buf4 := &bytes.Buffer{}
	memviz.Map(buf4, icell)
	fmt.Println(buf4.String())
}