class Linea {
    constructor(m, q) {
        this.m = m
        this.q = q
    }
    parallelo(l) {
        if (this.m == l.m) return true
        else return false
    }
    perpendicolare(l) {
        if (this.m * l.m == -1) return true
        else return false
    }
    interseca(l){
        return (!this.parallelo(l)) || this.coincide(l)
    }
    coincide(l){
        if (this.m == l.m && this.q == l.q) return true
        else return false
    }
    zero(){
        return -(this.q/this.m)
    }
}

var retta = new Linea(2,3)

console.log(retta.zero())