Math.rational = function rational(x) {
    var denom, exp = 0
    while( !(Number.isInteger(x * 10**exp)) ) exp++
    x *= 10**exp
    denom = 10**exp 
    while ((x % 2 == 0 && denom % 2 == 0) || (x % 5 == 0 && denom % 5 == 0)){
        if (x % 2 == 0 && denom % 2 == 0) {
            x /= 2
            denom /= 2
        }
        else{
            x /= 5
            denom /= 5
        }
    }
    return [x, denom]
}
console.log(3.1415)
console.log(Math.rational(3.1415))