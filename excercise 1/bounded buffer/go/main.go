package main

import (
	"fmt"
	"time"
)

func producer(c chan int) {

	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		// TODO: push real value to buffer
		c <- i
	}
}

func consumer(c chan int) {

	time.Sleep(1 * time.Second)
	for {
		i := <-c
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}
}

func main() {

	bbuffer := make(chan int, 5)

	go consumer(bbuffer)
	go producer(bbuffer)

	select {}
}
