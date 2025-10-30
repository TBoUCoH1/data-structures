package main

import (
	"os"
	"strings"
)

// Array
func loadArrayFromFile(filename string) DynamicArray {
	data, err := os.ReadFile(filename + "_array")
	if err != nil {
		return make(DynamicArray, 0)
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return make(DynamicArray, 0)
	}
	return strings.Fields(content)
}
func saveArrayToFile(filename string, arr DynamicArray) {
	os.WriteFile(filename+"_array", []byte(strings.Join(arr, " ")), 0644)
}

// Stack
func loadStackFromFile(filename string) *Stack {
	s := &Stack{}
	data, err := os.ReadFile(filename + "_stack")
	if err != nil {
		return s
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return s
	}
	values := strings.Fields(content)
	for _, v := range values {
		s.SPush(v)
	}
	return s
}
func saveStackToFile(filename string, s *Stack) {
	var values []string
	curr := s.top
	for curr != nil {
		values = append(values, curr.data)
		curr = curr.next
	}
	for i, j := 0, len(values)-1; i < j; i, j = i+1, j-1 {
		values[i], values[j] = values[j], values[i]
	}
	os.WriteFile(filename+"_stack", []byte(strings.Join(values, " ")), 0644)
}

// Queue
func loadQueueFromFile(filename string) *Queue {
	q := &Queue{}
	data, err := os.ReadFile(filename + "_queue")
	if err != nil {
		return q
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return q
	}
	values := strings.Fields(content)
	for _, v := range values {
		q.QPush(v)
	}
	return q
}
func saveQueueToFile(filename string, q *Queue) {
	var values []string
	curr := q.head
	for curr != nil {
		values = append(values, curr.data)
		curr = curr.next
	}
	os.WriteFile(filename+"_queue", []byte(strings.Join(values, " ")), 0644)
}

// SinglyList
func loadSinglyListFromFile(filename string) *SinglyList {
	sl := &SinglyList{}
	data, err := os.ReadFile(filename + "_slist")
	if err != nil {
		return sl
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return sl
	}
	values := strings.Fields(content)
	for _, v := range values {
		sl.FPushTail(v)
	} // Добавляем в хвост, чтобы сохранить порядок
	return sl
}
func saveSinglyListToFile(filename string, sl *SinglyList) {
	var values []string
	curr := sl.head
	for curr != nil {
		values = append(values, curr.key)
		curr = curr.next
	}
	os.WriteFile(filename+"_slist", []byte(strings.Join(values, " ")), 0644)
}

// DoublyList
func loadDoublyListFromFile(filename string) *DoublyList {
	dl := &DoublyList{}
	data, err := os.ReadFile(filename + "_dlist")
	if err != nil {
		return dl
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return dl
	}
	values := strings.Fields(content)
	for _, v := range values {
		dl.LAddTail(v)
	} // Добавляем в хвост, чтобы сохранить порядок
	return dl
}
func saveDoublyListToFile(filename string, dl *DoublyList) {
	var values []string
	curr := dl.head
	for curr != nil {
		values = append(values, curr.data)
		curr = curr.next
	}
	os.WriteFile(filename+"_dlist", []byte(strings.Join(values, " ")), 0644)
}

// AVL Tree
func loadTreeFromFile(filename string) *AVLTree {
	t := &AVLTree{}
	data, err := os.ReadFile(filename + "_tree")
	if err != nil {
		return t
	}
	content := strings.TrimSpace(string(data))
	if content == "" {
		return t
	}
	values := strings.Fields(content)
	for _, v := range values {
		t.TInsert(v)
	}
	return t
}
func saveTreeToFile(filename string, t *AVLTree) {
	var values []string
	var preorder func(*AVLNode)
	preorder = func(node *AVLNode) {
		if node == nil {
			return
		}
		values = append(values, node.key)
		preorder(node.left)
		preorder(node.right)
	}
	preorder(t.root)
	os.WriteFile(filename+"_tree", []byte(strings.Join(values, " ")), 0644)
}
