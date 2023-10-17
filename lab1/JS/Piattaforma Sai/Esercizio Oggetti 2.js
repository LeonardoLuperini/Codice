function frequenzaC(s){
    var res = {}
    for (var e of s){
        if (e in res) res[e]++
        else res[e] = 1
    }
    return res
}

console.log(frequenzaC("i vitelli dei romani sono belli"))