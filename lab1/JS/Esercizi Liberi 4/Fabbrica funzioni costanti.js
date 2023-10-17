var fabbrica = (k) => ( () => k );

var f = fabbrica(1)
var g = fabbrica(2)
var h = fabbrica(true)
console.log(f())
console.log(g())
console.log(h())