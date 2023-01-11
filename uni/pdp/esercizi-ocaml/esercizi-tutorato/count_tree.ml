type btree =
| Void
| Node of int * btree * btree

let positivo x = 
    match x with
    | Void -> false
    | Node (i,_,_) -> i > 0
;;

let bt =
Node (3,
    Node (5,Void,Void),
    Node (-4,
        Node(6,Void,Void),
        Node(8,Void,Void)
    )
)
;;

let rec count bt p =
    match bt with
    | Void -> 0
    | Node (i,bt1,bt2) ->
        let c1 = count bt1 p in
        let c2 = count bt2 p in
        if (p bt1) && (p bt2) then c1+c2+1
            else c1+c2
;;
