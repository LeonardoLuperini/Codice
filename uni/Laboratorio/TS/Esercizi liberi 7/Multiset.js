class NoSuchElementException extends Error{}

class MultiSet {
    constructor(set = {}) {
        this.set = {}
        for(let key in set) {
            if (typeof key == "string"){
                if(typeof set[key] == "number" && set[key] > 0){
                    this.add(key, set[key])
                }
            }
        }
    }
    
    add(e, n = 1) {
        n = Math.ceil(n)
        if (this.set[e]) this.set[e] += n
        else this.set[e] = n
    }

    remove(e, n = 1) {
        if (this.set[e]){
            this.set[e] -= n
            if(this.set[e] <= 0) delete this.set[e]
        }
        else throw new NoSuchElementException()
    }

    get size() {
        var c = 0
        for (let key in this.set) c++
        return c
    }

    union(S) {
        var newSet = new MultiSet(this.set)
        for(let key in S.set){
            newSet.add(key, S.set[key])
        }
        return newSet
    }
    
    diff(S) {
        var newSet = new MultiSet(this.set)
        for(let key in S.set){
            if (newSet.set[key]) newSet.remove(key, S.set[key])
        }
        return newSet
    }
}

var roba = new MultiSet({cavoli: 3, carote: 5})
var spesa = new MultiSet({cavoli: 4, piselli: 2})

var robaUspesa = roba.union(spesa)
console.log(robaUspesa.set)

var roba_spesa = roba.diff(spesa)

console.log(roba_spesa.set)
console.log(spesa.diff(roba).set)

console.log(roba)