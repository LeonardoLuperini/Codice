type exp =
    | on of exp * exp * exp * exp
;;
let rec eval e s =
    match e with
    | on (g1, e1, g2, e2) -> ( let c1 = eval g1 s in
                                let c2 = eval g2 s in
                                match (typecheck (Tbool, c1), c1, typecheck (Tbool, c2), c2) with
                                | (true, Bool(true), true, Bool(_)) -> eval e1 s
                                | (true, Bool(false), true, Bool(true)) -> eval e2 s
                                | _ -> trow Error 
                             )
