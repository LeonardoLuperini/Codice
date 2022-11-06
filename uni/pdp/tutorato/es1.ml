let rec len l = 
    match l with
        | [] -> 0
        | y::ys -> 1 + len(ys)
;;

let rec drop n l = (* Non funziona *)
    match l with
        | [] -> []
        | y::ys -> if( (len(y::ys)) mod n == 0) then drop n ys else y::drop n ys
;;

let rec lts l = 
    match l with
        | [] -> ""
        | y::ys -> (string_of_int y)^";"^lts(ys)
;;

print_string(lts(drop 2 [1;2;3;4;5;6;7;8;9;10]));;
