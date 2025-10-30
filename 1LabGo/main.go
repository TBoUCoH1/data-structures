package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	fmt.Print("Введите базовое имя файла для работы (например, 'mydatabase'): ")
	scanner.Scan()
	filename := scanner.Text()

	fmt.Println("Введите команды (для выхода введите 'exit' или 'quit'):")

	for {
		fmt.Print("> ")
		scanner.Scan()
		query := scanner.Text()

		if query == "exit" || query == "quit" {
			break
		}

		if query != "" {
			execute(query, filename)
		}
	}
	fmt.Println("Программа завершена.")
}

func execute(query, filename string) {
	parts := strings.Fields(query)
	if len(parts) == 0 {
		return
	}
	command := parts[0]
	args := parts[1:]

	// Array
	if strings.HasPrefix(command, "M") {
		arr := loadArrayFromFile(filename)
		modified := false
		switch command {
		case "MPUSH":
			if len(args) < 1 {
				fmt.Println("Ошибка: MPUSH требует <значение>")
				return
			}
			arr = append(arr, args[0])
			fmt.Println("-> добавлен", args[0])
			modified = true
		case "MINSERT":
			if len(args) < 2 {
				fmt.Println("Ошибка: MINSERT требует <индекс> <значение>")
				return
			}
			idx, err := strconv.Atoi(args[0])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть числом")
				return
			}
			if err = arr.MInsert(idx, args[1]); err != nil {
				fmt.Println(err)
				return
			}
			fmt.Printf("-> вставлен %s по индексу %d\n", args[1], idx)
			modified = true
		case "MDEL":
			if len(args) < 1 {
				fmt.Println("Ошибка: MDEL требует <индекс>")
				return
			}
			idx, err := strconv.Atoi(args[0])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть числом")
				return
			}
			if err = arr.MDel(idx); err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> удален элемент по индексу", idx)
			modified = true
		case "MGET":
			if len(args) < 1 {
				fmt.Println("Ошибка: MGET требует <индекс>")
				return
			}
			idx, err := strconv.Atoi(args[0])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть числом")
				return
			}
			val, err := arr.MGet(idx)
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Printf("-> элемент [%d] = \"%s\"\n", idx, val)
		case "MSET":
			if len(args) < 2 {
				fmt.Println("Ошибка: MSET требует <индекс> <значение>")
				return
			}
			idx, err := strconv.Atoi(args[0])
			if err != nil {
				fmt.Println("Ошибка: индекс должен быть числом")
				return
			}
			if err = arr.MSet(idx, args[1]); err != nil {
				fmt.Println(err)
				return
			}
			fmt.Printf("-> элемент [%d] заменен на \"%s\"\n", idx, args[1])
			modified = true
		case "MLEN":
			fmt.Printf("-> длина массива: %d\n", arr.MLen())
		case "MPRINT":
			arr.MPrint()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveArrayToFile(filename, arr)
		}
		return
	}

	// Stack
	if strings.HasPrefix(command, "S") {
		stack := loadStackFromFile(filename)
		modified := false
		switch command {
		case "SPUSH":
			if len(args) < 1 {
				fmt.Println("Ошибка: SPUSH требует <значение>")
				return
			}
			stack.SPush(args[0])
			fmt.Println("-> добавлен", args[0])
			modified = true
		case "SPOP":
			val, err := stack.SPop()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> извлечен", val)
			modified = true
		case "SPEEK":
			val, err := stack.SPeek()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("->", val)
		case "SPRINT":
			stack.SPrint()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveStackToFile(filename, stack)
		}
		return
	}

	// Queue
	if strings.HasPrefix(command, "Q") {
		queue := loadQueueFromFile(filename)
		modified := false
		switch command {
		case "QPUSH":
			if len(args) < 1 {
				fmt.Println("Ошибка: QPUSH требует <значение>")
				return
			}
			queue.QPush(args[0])
			fmt.Println("-> добавлен", args[0])
			modified = true
		case "QPOP":
			val, err := queue.QPop()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> извлечен", val)
			modified = true
		case "QPEEK":
			val, err := queue.QPeek()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("->", val)
		case "QPRINT":
			queue.QPrint()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveQueueToFile(filename, queue)
		}
		return
	}

	// SinglyList
	if strings.HasPrefix(command, "F") {
		slist := loadSinglyListFromFile(filename)
		modified := false
		switch command {
		case "FPUSH_HEAD":
			if len(args) < 1 {
				fmt.Println("Ошибка: FPUSH_HEAD требует <значение>")
				return
			}
			slist.FPushHead(args[0])
			fmt.Println("-> добавлен", args[0], "в начало")
			modified = true
		case "FPUSH_TAIL", "FPUSH":
			if len(args) < 1 {
				fmt.Println("Ошибка: FPUSH_TAIL требует <значение>")
				return
			}
			slist.FPushTail(args[0])
			fmt.Println("-> добавлен", args[0], "в конец")
			modified = true
		case "FPUSH_AFTER":
			if len(args) < 2 {
				fmt.Println("Ошибка: FPUSH_AFTER требует <новое_значение> <целевое_значение>")
				return
			}
			if slist.FPushAfter(args[1], args[0]) {
				fmt.Printf("-> вставлен %s после %s\n", args[0], args[1])
				modified = true
			} else {
				fmt.Printf("-> целевой элемент %s не найден\n", args[1])
			}
		case "FPUSH_BEFORE":
			if len(args) < 2 {
				fmt.Println("Ошибка: FPUSH_BEFORE требует <новое_значение> <целевое_значение>")
				return
			}
			if slist.FPushBefore(args[1], args[0]) {
				fmt.Printf("-> вставлен %s перед %s\n", args[0], args[1])
				modified = true
			} else {
				fmt.Printf("-> целевой элемент %s не найден\n", args[1])
			}
		case "FDEL_HEAD":
			val, err := slist.FDelHead()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> удален из начала:", val)
			modified = true
		case "FDEL_TAIL":
			val, err := slist.FDelTail()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> удален из конца:", val)
			modified = true
		case "FDEL":
			if len(args) < 1 {
				fmt.Println("Ошибка: FDEL требует <значение>")
				return
			}
			if slist.FDel(args[0]) {
				fmt.Println("-> удален", args[0])
				modified = true
			} else {
				fmt.Println("-> элемент", args[0], "не найден")
			}
		case "FGET":
			if len(args) < 1 {
				fmt.Println("Ошибка: FGET требует <значение>")
				return
			}
			if slist.FGet(args[0]) != nil {
				fmt.Printf("-> элемент \"%s\" найден\n", args[0])
			} else {
				fmt.Printf("-> элемент \"%s\" не найден\n", args[0])
			}
		case "FPRINT":
			slist.FPrint()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveSinglyListToFile(filename, slist)
		}
		return
	}

	// DoublyList
	if strings.HasPrefix(command, "L") {
		dlist := loadDoublyListFromFile(filename)
		modified := false
		switch command {
		case "LADD_HEAD":
			if len(args) < 1 {
				fmt.Println("Ошибка: LADD_HEAD требует <значение>")
				return
			}
			dlist.LAddHead(args[0])
			fmt.Println("-> добавлен", args[0], "в начало")
			modified = true
		case "LADD_TAIL", "LPUSH":
			if len(args) < 1 {
				fmt.Println("Ошибка: LADD_TAIL требует <значение>")
				return
			}
			dlist.LAddTail(args[0])
			fmt.Println("-> добавлен", args[0], "в конец")
			modified = true
		case "LADD_BEFORE":
			if len(args) < 2 {
				fmt.Println("Ошибка: LADD_BEFORE требует <новое_значение> <целевое_значение>")
				return
			}
			if dlist.LAddBefore(args[1], args[0]) {
				fmt.Printf("-> вставлен %s перед %s\n", args[0], args[1])
				modified = true
			} else {
				fmt.Printf("-> целевой элемент %s не найден\n", args[1])
			}
		case "LADD_AFTER":
			if len(args) < 2 {
				fmt.Println("Ошибка: LADD_AFTER требует <новое_значение> <целевое_значение>")
				return
			}
			if dlist.LAddAfter(args[1], args[0]) {
				fmt.Printf("-> вставлен %s после %s\n", args[0], args[1])
				modified = true
			} else {
				fmt.Printf("-> целевой элемент %s не найден\n", args[1])
			}
		case "LDEL_HEAD":
			val, err := dlist.LDelHead()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> удален из начала:", val)
			modified = true
		case "LDEL_TAIL":
			val, err := dlist.LDelTail()
			if err != nil {
				fmt.Println(err)
				return
			}
			fmt.Println("-> удален из конца:", val)
			modified = true
		case "LDEL":
			if len(args) < 1 {
				fmt.Println("Ошибка: LDEL требует <значение>")
				return
			}
			if dlist.LDel(args[0]) {
				fmt.Println("-> удален", args[0])
				modified = true
			} else {
				fmt.Println("-> элемент", args[0], "не найден")
			}
		case "LGET":
			if len(args) < 1 {
				fmt.Println("Ошибка: LGET требует <значение>")
				return
			}
			if dlist.LGet(args[0]) != nil {
				fmt.Printf("-> элемент \"%s\" найден\n", args[0])
			} else {
				fmt.Printf("-> элемент \"%s\" не найден\n", args[0])
			}
		case "LPRINT":
			dlist.LPrint()
		case "LPRINT_BACKWARD":
			dlist.LPrintBackward()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveDoublyListToFile(filename, dlist)
		}
		return
	}

	// Tree
	if strings.HasPrefix(command, "T") {
		tree := loadTreeFromFile(filename)
		modified := false
		switch command {
		case "TINSERT":
			if len(args) < 1 {
				fmt.Println("Ошибка: TINSERT требует <значение>")
				return
			}
			tree.TInsert(args[0])
			fmt.Println("-> вставлен", args[0])
			modified = true
		case "TDEL":
			if len(args) < 1 {
				fmt.Println("Ошибка: TDEL требует <значение>")
				return
			}
			tree.TDel(args[0])
			fmt.Println("-> удален", args[0])
			modified = true
		case "TGET", "ISMEMBER":
			if len(args) < 1 {
				fmt.Println("Ошибка: TGET требует <значение>")
				return
			}
			if tree.TGet(args[0]) {
				fmt.Println("-> TRUE")
			} else {
				fmt.Println("-> FALSE")
			}
		case "TPRINT":
			tree.TPrint()
		default:
			fmt.Println("Неизвестная команда:", command)
		}
		if modified {
			saveTreeToFile(filename, tree)
		}
		return
	}

	fmt.Println("Неизвестная команда или префикс:", command)
}
