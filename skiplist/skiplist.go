package main

import (
	"fmt"
	// "github.com/bradleyjkemp/memviz"
	"strconv"
	"strings"
	"bufio"
	"os"
	// "bytes"
	"time"
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

			if int(last_cell.cellid / skipval) + 1  ==  int(n / skipval) {
				last_skip_cell := skip_list_skip_tracker[m]
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

// func (sl skiplist) union(genea, geneb int) {
	
// 	cella, oka := sl.list[genea] 
//     if !oka {
// 		panic(oka)
// 	} 

// 	cellb, okb := sl.list[geneb]
// 	if !okb {
// 		panic(okb)
// 	}

// 	union_list := make([]int, 0)

// 	union_cells = func(cella, cellb *cell) {

// 		if cella.cellid < cellb.cellid {
// 			union_cells(cella.next, cellb); 
// 			return append(union_list, cella.cellid); 
// 		} else if cella.cellid > cellb.cellid {
// 			union_cells(cella, cellb.next); 
// 			return append(union_list, cellb.cellid); 
// 		} else if cella.cellid == cellb.cellid {
// 			union_cells(cella.next, cellb.next);
// 			return append(union_list, cella.cellid)
// 		}
// 	}

// 	union_cells(cella, cellb)
// } 

// func (sl skiplist) intersect(genea,geneb int, cell* intersection)
// {
//     if (!A)
//         return B;
//     if(!B)
//         return A;
// ​
//     bool flag = True;
//     if (A->data == B->data)
//     {
//         cell *temp = new cell;
//         temp->data = A->data;
//         temp->next = NULL;
//         intersection = temp;
//     }
//     else
//         flag = False;
// ​
//     if (A->next->cellid > B->next->cellid )
//     {
//         if(abs(A->next->cellid - B->cellid + 1) >= skip_value)
//         {
//             if (B->skip != NULL)
//                 B = B->skip;
//             else
//                 B = B->next;
//         }
//         else
//             B = B->next;
//         A = A->next;
//     }
// ​
//     else
//     {
//         if(abs(A->next->cellid - B->cellid + 1) >= skip_value)
//         {
//             if (A->skip != NULL)
//                 A = A->skip;
//             else
//                 A = A->next;
//         }
//         else
//             A = A->next;
//         B = B->next;
//     }
//     if (flag)
//         return INTERSECTION(A, B, skip_value, intersection->next);
//     else
//         return INTERSECTION(A, B, skip_value, intersection)
// }

func main() {

	start := time.Now()
	skips := buildSkipList("/mnt/c/Users/jayar/Desktop/projects/SCindex/filtered_matrices_mex/hg19/matrix.mtx", 100)
	end := time.Now().Sub(start)
	fmt.Println(end.Nanoseconds()/1000000)
	fmt.Println("end building")
	
	// fmt.Println(skips.counts)
	fmt.Println(skips.list[32709])
	// fmt.Println(skips.list[32709].cellid)
	// fmt.Println(skips.list[32709].next)
	// fmt.Println(skips.list[32709].next.cellid)
	// fmt.Println(skips.list[32709].next.next.cellid)
	// fmt.Println(skips.list[32709].next.next.next.cellid)	q

	// buf := &bytes.Buffer{}
	// memviz.Map(buf, skips.list[28606])
	// fmt.Println(buf.String())
}