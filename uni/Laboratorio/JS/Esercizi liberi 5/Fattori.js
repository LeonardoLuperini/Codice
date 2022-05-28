
function fattori(n) {
    var res1 = [] 
    var res2 = []
    for (let i = 1; i*i<=n; i++){
        if (n%i == 0) {
            res1.push([i,n/i])
            res2.push([n/i,i])
        }
    }
    return [...res1, ...res2.reverse()]
}