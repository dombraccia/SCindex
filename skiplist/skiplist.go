package main

import (
	"fmt"
	// "github.com/bradleyjkemp/memviz"
	"strconv"
	"strings"
	"bufio"
	"os"
	// "bytes"
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
}


func buildSkipList(filepath string) *skiplist {

	// create empty skiplist
	skip_obj := new(skiplist)
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

	rowdim, _ := strconv.ParseInt(words[0], 10, 32)
	coldim, _ := strconv.ParseInt(words[1], 10, 32)
	rowlength, _ := strconv.ParseInt(words[2], 10, 32)

	fmt.Println("rowdim, coldim, rowlength", rowdim, coldim, rowlength)

	skip_list_last_tracker := make(map[int]*cell)

	for fscanner.Scan() {

		words := strings.Fields(fscanner.Text())

		m, err := strconv.ParseInt(words[0], 10, 32)
		if err != nil {
			panic("index error!")
		}

		n, err := strconv.ParseInt(words[1], 10, 32)
		if err != nil {
			panic("index error!")
		}

		tmp_cell := new(cell)
		tmp_cell.cellid = int(n)

		_, ok := skip_list_last_tracker[int(m)]
		if ok {
			last_cell := skip_list_last_tracker[int(m)]
			last_cell.next = tmp_cell
			skip_list_last_tracker[int(m)] = tmp_cell
		} else {
			skip_list_last_tracker[int(m)] = tmp_cell
			skip_obj.list[int(m)] = tmp_cell
		}

		skip_obj.counts[int(m)]++
	}

	return skip_obj
}

func main() {

	skips := buildSkipList("/mnt/c/Users/jayar/Desktop/projects/SCindex/filtered_matrices_mex/hg19/matrix.mtx")
	fmt.Println("end building")
	
	fmt.Println(skips.counts)
	fmt.Println(skips.list[32709])
	fmt.Println(skips.list[32709].cellid)
	fmt.Println(skips.list[32709].next)
	fmt.Println(skips.list[32709].next.cellid)
	fmt.Println(skips.list[32709].next.next.cellid)
	fmt.Println(skips.list[32709].next.next.next.cellid)
}