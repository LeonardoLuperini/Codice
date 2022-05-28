function cifreInv(n) {
    var res = []
    res.push(Math.floor((n / 10 - Math.floor(n / 10)) * 10))
    n = Math.floor(n / 10)
    res = [...res, ...(n != 0) ? cifreInv(n) : []]
    return res
}

console.log(cifreInv(2563))
console.log(cifreInv(98763))
