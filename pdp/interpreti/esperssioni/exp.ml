type op = Add | Sub | Mul | Div ;;

type exp = 
    | Val of int
    | Op of op * exp * exp ;;


let rec to_string e = 
    let symbol o =
        match o with
        | Add -> "+"
        | Sub -> "-"
        | Mul -> "*"
        | Div -> "/"
    in 
    match e with
    | Val n -> string_of_int n
    | Op (o,e1,e2) -> "(" ^ (to_string e1) ^ (symbol o) ^ (to_string e2) ^ ")" ;;

let expr = Op (Sub, (Op (Mul, Val 3, Val 7)), Val 5);;
print_endline (to_string expr);;

let rec eval e =
    match e with
    | Val n -> Val n
    | Op (o, e1, e2) -> 
            match (eval e1, eval e2) with
            | (Val n1, Val n2) -> (
                match o with
                    | Add -> Val (n1 + n2)
                    | Sub -> Val (n1 - n2)
                    | Mul -> Val (n1 * n2)
                    | Div -> Val (n1 / n2)
                    )
            | _ -> failwith "Errore impossibile che si verifichi"
;;


print_endline (to_string (eval expr));;
