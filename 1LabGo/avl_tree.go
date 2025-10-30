package main

import "fmt"

type AVLNode struct {
	key    string
	height int
	left   *AVLNode
	right  *AVLNode
}

type AVLTree struct {
	root *AVLNode
}

func height(n *AVLNode) int {
	if n == nil {
		return 0
	}
	return n.height
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func (t *AVLTree) TInsert(key string) {
	t.root = tInsert(t.root, key)
}

func (t *AVLTree) TDel(key string) {
	t.root = tDel(t.root, key)
}

func (t *AVLTree) TGet(key string) bool {
	return tGet(t.root, key) != nil
}

func (t *AVLTree) TPrint() {
	tPrint(t.root, "", true)
}

// Рекурсивные вспомогательные функции
func tInsert(node *AVLNode, key string) *AVLNode {
	if node == nil {
		return &AVLNode{key: key, height: 1}
	}
	if key < node.key {
		node.left = tInsert(node.left, key)
	} else if key > node.key {
		node.right = tInsert(node.right, key)
	} else {
		return node
	}
	return rebalance(node)
}

func tDel(node *AVLNode, key string) *AVLNode {
	if node == nil {
		return node
	}
	if key < node.key {
		node.left = tDel(node.left, key)
	} else if key > node.key {
		node.right = tDel(node.right, key)
	} else {
		if node.left == nil || node.right == nil {
			var temp *AVLNode
			if node.left != nil {
				temp = node.left
			} else {
				temp = node.right
			}
			if temp == nil {
				node = nil
			} else {
				*node = *temp
			}
		} else {
			temp := minValueNode(node.right)
			node.key = temp.key
			node.right = tDel(node.right, temp.key)
		}
	}
	if node == nil {
		return node
	}
	return rebalance(node)
}

func tGet(node *AVLNode, key string) *AVLNode {
	if node == nil || node.key == key {
		return node
	}
	if key < node.key {
		return tGet(node.left, key)
	}
	return tGet(node.right, key)
}

func rebalance(node *AVLNode) *AVLNode {
	node.height = 1 + max(height(node.left), height(node.right))
	balance := getBalance(node)

	if balance > 1 && getBalance(node.left) >= 0 {
		return rightRotate(node)
	}
	if balance > 1 && getBalance(node.left) < 0 {
		node.left = leftRotate(node.left)
		return rightRotate(node)
	}
	if balance < -1 && getBalance(node.right) <= 0 {
		return leftRotate(node)
	}
	if balance < -1 && getBalance(node.right) > 0 {
		node.right = rightRotate(node.right)
		return leftRotate(node)
	}
	return node
}

func leftRotate(z *AVLNode) *AVLNode {
	y := z.right
	t2 := y.left
	y.left = z
	z.right = t2
	z.height = 1 + max(height(z.left), height(z.right))
	y.height = 1 + max(height(y.left), height(y.right))
	return y
}

func rightRotate(z *AVLNode) *AVLNode {
	y := z.left
	t3 := y.right
	y.right = z
	z.left = t3
	z.height = 1 + max(height(z.left), height(z.right))
	y.height = 1 + max(height(y.left), height(y.right))
	return y
}

func getBalance(n *AVLNode) int {
	if n == nil {
		return 0
	}
	return height(n.left) - height(n.right)
}

func minValueNode(node *AVLNode) *AVLNode {
	current := node
	for current.left != nil {
		current = current.left
	}
	return current
}

func tPrint(node *AVLNode, indent string, last bool) {
	if node != nil {
		fmt.Print(indent)
		if last {
			fmt.Print("R----")
			indent += "   "
		} else {
			fmt.Print("L----")
			indent += "|  "
		}
		fmt.Printf(`"%s" (h:%d, b:%d)\n`, node.key, node.height, getBalance(node))
		tPrint(node.left, indent, false)
		tPrint(node.right, indent, true)
	}
}
