function plotta(f, a, b, d = 0.01) {
    for (var x = a; x < b; x += d)
        punto(x, f(x), 1.5, "#008000")
}

/*
function zeroi(f, a, b, d = 0.01) {
    for (var x = a; x <= b; x += d) {
        if (f(x) * f(x + d) < 0)
            return x + d / 2
    }
    return undefined
}
*/
function zero(f, a, b, e = 0.01) {
    // console.log(a,b)
    var m = a + (b - a) / 2
    if (b - a < e)
        return m
    if (f(a) * f(m) <= 0)
        return zero(f, a, m, e)
    else
        return zero(f, m, b, e)
}

function intdef(f, a, b, n = 10) {
    var h = (b - a) / n
    var sum = 0
    for (var i = 0; i < n; i++) {
        var x = a + h * i + h / 2
        sum += (h * f(x))
    }
    return sum
}
/*
function intdefdx(f, a, b, n = 10) {
    var h = (b - a) / n
    var sum = 0
    for (var i = 0; i < n; i++) {
        var x = a + h * i + h
        sum += (h * f(x))
    }
    return sum
}

function intdefsx(f, a, b, n = 10) {
    var h = (b - a) / n
    var sum = 0
    for (var i = 0; i < n; i++) {
        var x = a + h * i
        sum += (h * f(x))
    }
    return sum
}
*/
class Rational {
    constructor(num, den = 1) {
        this.num = num
        this.den = den
        this.simplify()
    }

    simplify() {
        var m = this.mcd(this.num, this.den)
        var s = this.den < 0 ? -1 : 1
        this.num /= m * s
        this.den /= m * s
    }

    mcd(a, b) {
        a = Math.abs(a)
        b = Math.abs(b)
        while (b) {
            [a, b] = [b, a % b]
        }
        return a
    }

    plus(r) { return new Rational(this.num * r.den + r.num * this.den, this.den * r.den) }

    minus(r) { return new Rational(this.num * r.den - r.num * this.den, this.den * r.den) }
    
    times(r) { return new Rational(this.num * r.num, this.den * r.den) }

    div(r) { return new Rational(this.num * r.den, this.den * r.num) }

    abs() { return new Rational(Math.abs(this.num), this.den) }

    toString() { return `${this.num}/${this.den}` }

    valueOf() { return this.num/this.den }

    toNumber() { return this.num / this.den }
}

function main() {
    const f = (x) => 2*x + 4
    const g = (x) => -2*x + 4
    const h = (x) => 2*x + -4
    const i = (x) => -0.5*x + -4
    //plotta(f, -50, 50)
    //plotta(g, -50, 50)
    plotta(h, -50, 50)
    plotta(i, -50, 50)
}

main()