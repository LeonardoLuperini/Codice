let bts b = if b then "True" else "False"

type id = string 

type exp = 
    | Var of id
    | Lam of id * exp
    | App of exp * exp
;;

let rec fvs e =
    match e with
    | Var id -> [id]
    | Lam (id, e) -> List.filter (fun x -> x <> id) (fvs e)
    | App (e1, e2)-> fvs(e1) @ fvs(e2)
;;


let t1 = fvs (Var "x") = ["x"];;
let t2 = fvs (Lam ("x",Var "y")) = ["y"];;
let t3 = fvs (Lam ("x",Var "x")) = [];;
let t4 = fvs (App (Lam ("x", Var "z"), Var "y")) = ["z"; "y"];;

print_endline (bts t1);;
print_endline (bts t2);;
print_endline (bts t3);;
print_endline (bts t4);;
