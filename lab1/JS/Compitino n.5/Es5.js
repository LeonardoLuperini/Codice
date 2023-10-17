function argmax(a){
    var value = Math.max(...a)
    var index = a.findIndex((e) => e == value)
    return [index, value]
}

console.log(argmax([3,5,8,-1,0]))