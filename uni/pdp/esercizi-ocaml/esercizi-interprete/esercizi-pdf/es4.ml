type pos = int;; (* pos apparteiene all intervallo di numeri interi [0, 100] *)

type ide = string;;

type exp = 
    | Den of ide
    | EPos of pos
    | MoveLeft of exp
    | MoveRight of exp
    | Let of ide * exp * exp
;;

type evT =
    | Pos of pos
    | Unbound
;;

let empty_env x = Unbound ;;

let bind s i v =
    function x -> if x = i then v else (s x)
;;


let rec eval s e = 
    match e with
    | Den (x) -> (s x)
    | EPos (y) -> y
    | MoveLeft (e1) -> (let p = eval s e1 in
                       match p with
                       | 0 -> 0
                       | k -> k-1
                       )
    | MoveRight (e2) -> (let p = eval s e2 in
                        match p with
                        | 100 -> 100
                        | k -> k+1 
                        )
    | Let (i, e3, e4) -> (let res = eval s e3 in
                          let s' = bind s i res in
                          eval s' e4
                         )
;;
