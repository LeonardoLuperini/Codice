let rec elem x xs =
    match xs with
    | [] -> false
    | y::ys -> if (x = y) then true else elem x ys
;;

if (elem 5 [1;2;3;5;6]) then print_string "True\n" else print_string "False\n"

 
