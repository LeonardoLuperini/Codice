type binary_tree =
    | Empty
    | Node of int *  binary_tree * binary_tree;;
    
(*Esempio: t1 è un BST*)
let t1 = Node(5, Node(3, Empty, Empty), Node(7, Node(6, Empty, Empty), Empty))

(*Esempio: t2 non è un BST*)
let t2 = Node(5, Node(8, Empty, Empty), Node(7, Node(6, Empty, Empty), Empty))

;;

let rec insert tree n = 
    match tree with 
    | Empty -> Node(n, Empty, Empty)
    | Node(v, l, r) -> if n < v then Node(v, insert l n, r) else Node(v, l, insert r n)
;;

insert t1 3;;
