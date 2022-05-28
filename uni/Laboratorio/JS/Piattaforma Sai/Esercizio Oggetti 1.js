function maxprod(a) {
    var res = {idx: 0, val: a[0]}

    for (var i in a) if (a[i]*i > res.idx*res.val) res = {idx: i, val: a[i]}
    
    return res

}

a = [8, 2, 2, 1]
b = [1, 8, 1, 2, 2]
console.log(maxprod(a))
console.log(maxprod(b))