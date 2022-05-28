function estrai(a) {
    var res = []
    for (var e of a) {
        if (typeof e == 'object') res = [...res, ...estrai(e)]
        else res.push(e)
    }
    return res
}

console.log(estrai([
    ["che"], "bello", ["questo", "esercizio"], "qui", []
]))