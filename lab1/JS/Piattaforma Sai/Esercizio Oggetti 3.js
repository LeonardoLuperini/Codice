function zip(o){
    var res = []
    for(var i in o) res.push([i,o[i]])
    return res
}

function unzip(a){
    var res = {}
    for(var e of a) res[e[0]] = e[1]
    return res
}

console.log(zip({a:1, b:true}))
console.log(unzip(zip({a:1, b:true})))