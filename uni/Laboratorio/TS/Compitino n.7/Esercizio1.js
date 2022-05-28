function lindip(A){
    var k
    var trovato = true
    for (let i = 0; i < A.length; i++){
        k = "empty"
        for( let h = 0; h < A.length; h++){
            trovato = true
            if (h != i){
                for(let j = 0; j < A[0].length; j++){
                    if (k == "empty") k = A[i][j]/A[h][j]
                    if (k != A[i][j]/A[h][j]) {
                        trovato = false
                    }
                }
                if (trovato) return trovato
            }
        }
    }
    return false
}

var A=[
    [ 2, 4, 6 ],
    [ 5, 7, 1 ],
    [ 3, 3, 8 ],
    [ 1, 2, 3 ]]

lindip(A)