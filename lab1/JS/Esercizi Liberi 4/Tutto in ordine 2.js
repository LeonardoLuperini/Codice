/*Scrivere una funzione isSorted2(a), come isSorted1(a) ma senza usare cicli.*/

function isSorted2(a){
    function ricorsione(a, i){
        if (i==a.length-1) return true
        else if (a[i]>= a[i+1]) return false
        else return ricorsione (a,i+1)
    }
    return ricorsione(a,0)
}

console.log(isSorted2([-21, -2, 0, 4, 6, 210]))
console.log(isSorted2([2, 6, 8, 8, 9, 21]))
console.log(isSorted2([2, 6, 8, 9, 10, -42]))