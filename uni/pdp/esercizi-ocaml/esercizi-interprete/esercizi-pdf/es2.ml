type exp =
    | use of ide * exp * exp * exp * exp
;;

let rec eval e s =
    match e with
    | use (id, e1, e2, e3, g) -> ( let c = eval g s in
                               match (typecheck (Tbool, c), c) with
                               | (true, Bool(true)) -> ( let f1 = eval e1 s in
                                                         let s' = bind s id f1 in
                                                         eval e3 s'
                                                       )
                               | (true, Bool(false)) -> ( let f2 = eval e2 s in
                                                         let s' = bind s id f2 in
                                                         eval e3 s'
                                                       )
                               | _ -> trow Error
                             )

