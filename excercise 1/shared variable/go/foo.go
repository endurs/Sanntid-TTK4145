// Use `go run foo.go` to run your program

package main

import (
	. "fmt"
	"runtime"
	"sync"
	//"time"
)

var i = 0
var wg sync.WaitGroup //waitgroup to handle stopping the program

func handleIncDec(inc chan bool, dec chan bool) {
	defer wg.Done()
	for {
		select {
		case _, ok := <-inc:
			if ok {
				i++
				//Printf("i is now %d\n", i)
			} else {
				inc = nil
			}
		case _, ok := <-dec:
			if ok {
				i--
				//Printf("i is now %d\n", i)
			} else {
				dec = nil
			}
		}
		if inc == nil && dec == nil {
			break
		}
	}

}

// function to increment i 1000000 times, add to channel
func incrementing(c chan bool) {
	for j := 0; j < 1000069; j++ {
		c <- true
	}
	//close channel
	close(c)
}

// function to decrement i 1000000 times, add to channel
func decrementing(c chan bool) {
	for j := 0; j < 1000000; j++ {
		c <- true
	}
	//close channel
	close(c)
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	//// running at most just one process at a time will remove the race condition and the result will always be 0
	runtime.GOMAXPROCS(3)

	//create an add channel and a subtract channel
	inc := make(chan bool)
	dec := make(chan bool)

	//spawn the goroutines
	wg.Add(1)
	go incrementing(inc)
	go decrementing(dec)
	go handleIncDec(inc, dec)

	wg.Wait()
	Println("The magic number is:", i)
	if i == 69 {
		Println("Nice")
	}
}
