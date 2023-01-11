type exp = 
    | FinFun of id * exp * exp list
;;

type evT =
    | FinClosure of id * exp * evT list 
;;

type tname = ..| TFinClosure
;;

let typecheck (type, val) =
    match type with
    | TFinClosure -> ( match val with
                       | FinClosure (_) -> true
                       | _ -> false
                     )
;;

let getType val = 
    match val with
    | FinClosure(_) -> TFinClosure
;;

let rec eval e s = 
    match e with
    | FinFun (id, body, set) -> ( let rec eval_set s =
                                    match s with
                                    | [] -> []
                                    | w::ws -> (eval w)::(eval_set ws)
                                  in
                                  let eset = eval_set set in
                                  FinClosure(id, body, eset)
                                )
    | Apply (e1, e2) -> let func = eval e1 s in
                        let act = eval e2 s in
                        match func with
                          | FinClosure (id, body, set) -> let s' = bind s id act in
                                                          match (List.exist (function x -> x = act) set) with
                                                          | true -> eval body s'
                                                          | false -> trow Error
                        
;;
