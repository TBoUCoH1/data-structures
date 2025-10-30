package main

import "fmt"

type SinglyNode struct {
	key  string
	next *SinglyNode
}

type SinglyList struct {
	head *SinglyNode
	size int
}

func (sl *SinglyList) FPushHead(key string) {
	newNode := &SinglyNode{key: key, next: sl.head}
	sl.head = newNode
	sl.size++
}

func (sl *SinglyList) FPushTail(key string) {
	newNode := &SinglyNode{key: key}
	if sl.head == nil {
		sl.head = newNode
	} else {
		current := sl.head
		for current.next != nil {
			current = current.next
		}
		current.next = newNode
	}
	sl.size++
}

func (sl *SinglyList) FGet(key string) *SinglyNode {
	current := sl.head
	for current != nil {
		if current.key == key {
			return current
		}
		current = current.next
	}
	return nil
}

func (sl *SinglyList) FPushAfter(targetKey, newKey string) bool {
	targetNode := sl.FGet(targetKey)
	if targetNode == nil {
		return false
	}
	newNode := &SinglyNode{key: newKey, next: targetNode.next}
	targetNode.next = newNode
	sl.size++
	return true
}

func (sl *SinglyList) FPushBefore(targetKey, newKey string) bool {
	if sl.head == nil {
		return false
	}
	// Если целевой элемент - голова
	if sl.head.key == targetKey {
		sl.FPushHead(newKey)
		return true
	}
	// Ищем узел перед целевым
	prev := sl.head
	for prev.next != nil && prev.next.key != targetKey {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	newNode := &SinglyNode{key: newKey, next: prev.next}
	prev.next = newNode
	sl.size++
	return true
}

func (sl *SinglyList) FDelHead() (string, error) {
	if sl.head == nil {
		return "", fmt.Errorf("ошибка: список пуст")
	}
	value := sl.head.key
	sl.head = sl.head.next
	sl.size--
	return value, nil
}

func (sl *SinglyList) FDelTail() (string, error) {
	if sl.head == nil {
		return "", fmt.Errorf("ошибка: список пуст")
	}
	if sl.head.next == nil {
		value := sl.head.key
		sl.head = nil
		sl.size--
		return value, nil
	}
	current := sl.head
	for current.next.next != nil {
		current = current.next
	}
	value := current.next.key
	current.next = nil
	sl.size--
	return value, nil
}

func (sl *SinglyList) FDel(key string) bool {
	if sl.head == nil {
		return false
	}
	if sl.head.key == key {
		sl.head = sl.head.next
		sl.size--
		return true
	}
	prev := sl.head
	for prev.next != nil && prev.next.key != key {
		prev = prev.next
	}
	if prev.next != nil {
		prev.next = prev.next.next
		sl.size--
		return true
	}
	return false
}

func (sl *SinglyList) FPrint() {
	if sl.head == nil {
		fmt.Println("Список пуст.")
		return
	}
	current := sl.head
	for current != nil {
		fmt.Printf(`"%s" `, current.key)
		current = current.next
	}
	fmt.Println()
}
