Array.prototype.reverse = function () {
    for (let i = 0; i < Math.floor(this.length/2); i++) {
        var temp = this[i]
        this[i] = this[this.length-1-i]
        this[this.length-1-i] = temp
    }
}

Array.prototype.reverse2 = function (i = 0) {
    if (i < Math.floor(this.length/2)) {
        var temp = this[i]
        this[i] = this[this.length-1-i]
        this[this.length-1-i] = temp
        this.reverse2(++i)
    }
}

Array.prototype.reverse3 = ([h, ...tail]) => (tail.length != 0)? [...tail.reverse3(tail),h] : [h]

var a = [1,2,3]
var b = [1,2,3,4]

console.log(a.reverse3(a))
b.reverse3(b)
console.log(a)
console.log(b)