type ide = string

type tname = TUnbound | TDynClosure

type exp = 
    | EDynFun of ide * exp
    | Apply of exp * exp

type evT =
    | DynClosure of ide * exp
    | Unbound

let getType (x: evT) = 
    match x with
    | DynClosure (_) -> TDynClosure
    | Unbound -> TUnbound

let typecheck ((t, x): (tname * evT)) = 
    match t with 
    | TDynClosure -> (match x with
                     | DynClosure (_) -> true
                     | _ -> false
                     ) 
    | TUnbound -> (match x with
                  | Unbound -> true
                  | _ -> false
                  )
;;

type 't env = ide -> 't

let emptyenv = fun x -> Unbound ;;

let bind (s:evT env) x v =
    fun i -> if i = x then v else (s i)

exception RuntimeError of string ;;

let rec eval e s =
    match e with
    | EDynFun (arg, body) -> DynClosure (arg, body)
    | Apply (e1, e2) -> let func = eval e1 s in
                        let act = eval e1 s in
                        match func with
                        | DynClosure (arg, body) -> let s' = bind s arg act in eval body s'
                        | _ -> raise (RuntimeError "L'argomento a sinistra di apply deve essere una funzione")
