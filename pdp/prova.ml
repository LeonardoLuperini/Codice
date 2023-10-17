let int_of_bool b = if b then 1 else 0;;
let f g x = (g x) = 3 ;;
let pippo y = y ;;
print_int (int_of_bool(f pippo 3));;
