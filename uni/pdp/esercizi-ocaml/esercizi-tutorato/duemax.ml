let rec duemax list =
    match list with
    | [] -> None
    | a::[] -> Some(a, a)
    | a::b::[] -> if a > b then Some(a, b) else Some(b, a)
    | w::ws -> (match (duemax ws) with
               | Some(a, b) -> if w > a then Some(w, a) else if w > b then Some(a, w) else Some(a, b)
               | None -> failwith "Errore impossibile"
               )
;;

let rec max list =
    match list with
    | [] -> None
    | w::ws -> (match (max ws) with
               | Some(v) -> if w > v then Some(w) else Some(v)
               | None -> Some(w)
               )
;;

let pippo = ["ciao"; "come"; "stai"; "wee"];; 

let res = (match (max pippo) with
          | Some(v) -> v
          | None -> "--None--"
          )
in
print_string(res ^ "\n")
;;

let res2 = (match (duemax pippo) with
           | Some(a, b) -> (print_string ("( " ^ a ^ " , " ^ b ^ " )\n"))
           | None -> (print_string ("--None--\n"))
           )
;;
