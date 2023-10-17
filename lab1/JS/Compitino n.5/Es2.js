function* madhava() {
    var n = 0
    var total = 0
    while(true){
        total += (((-1)**n)/((2*n) +1))*4
        yield total
        n++
    }
}

var x=madhava()
for (var i=1;i<=10;i++) console.log(x.next().value)