package main

import "fmt"

type StackNode struct {
	data string
	next *StackNode
}

type Stack struct {
	top  *StackNode
	size int
}

func (s *Stack) SPush(data string) {
	newNode := &StackNode{data: data, next: s.top}
	s.top = newNode
	s.size++
}

func (s *Stack) SPop() (string, error) {
	if s.top == nil {
		return "", fmt.Errorf("ошибка: стек пуст")
	}
	data := s.top.data
	s.top = s.top.next
	s.size--
	return data, nil
}

func (s *Stack) SPeek() (string, error) {
	if s.top == nil {
		return "", fmt.Errorf("ошибка: стек пуст")
	}
	return s.top.data, nil
}

func (s *Stack) SPrint() {
	if s.top == nil {
		fmt.Println("Стек пуст.")
		return
	}
	fmt.Print("Вершина -> ")
	current := s.top
	for current != nil {
		fmt.Printf(`"%s" `, current.data)
		current = current.next
	}
	fmt.Println("-> Дно")
}