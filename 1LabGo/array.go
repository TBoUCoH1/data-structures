package main

import (
	"fmt"
	"strings"
)

type DynamicArray []string

func (arr *DynamicArray) MInsert(index int, value string) error {
	if index < 0 || index > len(*arr) {
		return fmt.Errorf("ошибка: индекс %d вне диапазона", index)
	}
	*arr = append((*arr)[:index], append([]string{value}, (*arr)[index:]...)...)
	return nil
}

func (arr *DynamicArray) MDel(index int) error {
	if index < 0 || index >= len(*arr) {
		return fmt.Errorf("ошибка: индекс %d вне диапазона", index)
	}
	*arr = append((*arr)[:index], (*arr)[index+1:]...)
	return nil
}

func (arr *DynamicArray) MGet(index int) (string, error) {
	if index < 0 || index >= len(*arr) {
		return "", fmt.Errorf("ошибка: индекс %d вне диапазона", index)
	}
	return (*arr)[index], nil
}

func (arr *DynamicArray) MSet(index int, value string) error {
	if index < 0 || index >= len(*arr) {
		return fmt.Errorf("ошибка: индекс %d вне диапазона", index)
	}
	(*arr)[index] = value
	return nil
}

func (arr *DynamicArray) MLen() int {
	return len(*arr)
}

func (arr *DynamicArray) MPrint() {
	if len(*arr) == 0 {
		fmt.Println("Массив пуст.")
		return
	}
	quoted := make([]string, len(*arr))
	for i, v := range *arr {
		quoted[i] = fmt.Sprintf(`"%s"`, v)
	}
	fmt.Printf("Массив (size=%d): %s\n", len(*arr), strings.Join(quoted, " "))
}
