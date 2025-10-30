package main

import "fmt"

type DoublyNode struct {
	data string
	next *DoublyNode
	prev *DoublyNode
}

type DoublyList struct {
	head *DoublyNode
	tail *DoublyNode
	size int
}

func (dl *DoublyList) LAddHead(data string) {
	newNode := &DoublyNode{data: data, next: dl.head}
	if dl.head != nil {
		dl.head.prev = newNode
	}
	dl.head = newNode
	if dl.tail == nil {
		dl.tail = newNode
	}
	dl.size++
}

func (dl *DoublyList) LAddTail(data string) {
	newNode := &DoublyNode{data: data, prev: dl.tail}
	if dl.tail != nil {
		dl.tail.next = newNode
	}
	dl.tail = newNode
	if dl.head == nil {
		dl.head = newNode
	}
	dl.size++
}

func (dl *DoublyList) LGet(data string) *DoublyNode {
	current := dl.head
	for current != nil {
		if current.data == data {
			return current
		}
		current = current.next
	}
	return nil
}

func (dl *DoublyList) LAddBefore(targetData, newData string) bool {
	targetNode := dl.LGet(targetData)
	if targetNode == nil {
		return false
	}

	// Если целевой узел - это голова, то это просто LAddHead
	if targetNode == dl.head {
		dl.LAddHead(newData)
		return true
	}

	// Стандартный случай
	newNode := &DoublyNode{data: newData, prev: targetNode.prev, next: targetNode}
	targetNode.prev.next = newNode
	targetNode.prev = newNode
	dl.size++
	return true
}

func (dl *DoublyList) LAddAfter(targetData, newData string) bool {
	targetNode := dl.LGet(targetData)
	if targetNode == nil {
		return false
	}
	newNode := &DoublyNode{data: newData, prev: targetNode, next: targetNode.next}
	if targetNode.next != nil {
		targetNode.next.prev = newNode
	} else {
		dl.tail = newNode
	}
	targetNode.next = newNode
	dl.size++
	return true
}

func (dl *DoublyList) LDelHead() (string, error) {
	if dl.head == nil {
		return "", fmt.Errorf("ошибка: список пуст")
	}
	value := dl.head.data
	dl.head = dl.head.next
	if dl.head != nil {
		dl.head.prev = nil
	} else {
		dl.tail = nil
	}
	dl.size--
	return value, nil
}

func (dl *DoublyList) LDelTail() (string, error) {
	if dl.tail == nil {
		return "", fmt.Errorf("ошибка: список пуст")
	}
	value := dl.tail.data
	dl.tail = dl.tail.prev
	if dl.tail != nil {
		dl.tail.next = nil
	} else {
		dl.head = nil
	}
	dl.size--
	return value, nil
}

func (dl *DoublyList) LDel(data string) bool {
	nodeToDel := dl.LGet(data)
	if nodeToDel == nil {
		return false
	}
	if nodeToDel.prev != nil {
		nodeToDel.prev.next = nodeToDel.next
	} else {
		dl.head = nodeToDel.next
	}
	if nodeToDel.next != nil {
		nodeToDel.next.prev = nodeToDel.prev
	} else {
		dl.tail = nodeToDel.prev
	}
	dl.size--
	return true
}

func (dl *DoublyList) LPrint() {
	if dl.head == nil {
		fmt.Println("Список пуст.")
		return
	}
	current := dl.head
	for current != nil {
		fmt.Printf(`"%s" `, current.data)
		current = current.next
	}
	fmt.Println()
}

func (dl *DoublyList) LPrintBackward() {
	if dl.tail == nil {
		fmt.Println("Список пуст.")
		return
	}
	current := dl.tail
	for current != nil {
		fmt.Printf(`"%s" `, current.data)
		current = current.prev
	}
	fmt.Println()
}
