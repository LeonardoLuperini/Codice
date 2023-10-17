Array.prototype.reverse2 = function() { 
    function rec([t,...tail]){
        if (t){
            return [...rec(tail), t]
        }
        return []
    }
    return rec(this)
}

console.log([1,2,3,4,5].reverse2())