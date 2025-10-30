package main

import "fmt"

type QueueNode struct {
	data string
	next *QueueNode
}

type Queue struct {
	head *QueueNode
	tail *QueueNode
	size int
}

func (q *Queue) QPush(data string) {
	newNode := &QueueNode{data: data}
	if q.head == nil {
		q.head = newNode
		q.tail = newNode
	} else {
		q.tail.next = newNode
		q.tail = newNode
	}
	q.size++
}

func (q *Queue) QPop() (string, error) {
	if q.head == nil {
		return "", fmt.Errorf("ошибка: очередь пуста")
	}
	data := q.head.data
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	q.size--
	return data, nil
}

func (q *Queue) QPeek() (string, error) {
	if q.head == nil {
		return "", fmt.Errorf("ошибка: очередь пуста")
	}
	return q.head.data, nil
}

func (q *Queue) QPrint() {
	if q.head == nil {
		fmt.Println("Очередь пуста.")
		return
	}
	fmt.Print("Начало -> ")
	current := q.head
	for current != nil {
		fmt.Printf(`"%s" `, current.data)
		current = current.next
	}
	fmt.Println("-> Конец")
}