function initMatrice(matrice,arr){
    for (let i = 0; i < arr.length;i++){
        matrice[i] = []       
    }
    
    for(let j = 0; j < arr.length; j++){
        for (let i = j; i < arr.length;i++){
            matrice[i][j] = 0
        }
    }
}

function updateSequanceArray(seqArr, k){
    var n = seqArr.length
    for(var a = 0; a < n; a++){
        var seq = seqArr[a]
        if (k > seq[seq.length-1]){
            seq.push(k)
        }
        else {
            var b
            var trovato = false
            for(b = seq.length - 1; b > -1; b--){
                if (k > seq[b]) {
                    trovato = true
                    break
                }
            }
            if (trovato){
                var temp = []
                for (let c = 0; c <= b; c++){
                    temp.push(c)
                }
                temp.push(k)
                seqArr.push(temp)
            }
        }
    }
}

function elementiMatrice(m){
    var res = []
    for(e of m){
        res = [...res, e[e.length-1]]
    }
    return res
}

function LS(arr){
    var matrice = []
    initMatrice(matrice,arr) //N^2
    for(let i = 0; i < arr.length; i++){ //scorro le righe
        var seqArr = [[arr[i]]]
        for (let j = i; j < arr.length; j++){ //scorro le colonne
            updateSequanceArray(seqArr, arr[j])
            matrice[i][j] = Math.max( ...( seqArr.map( (e) => e.length ) ) )
        }
    }
    console.log(matrice)
    return Math.max(...(elementiMatrice(matrice)))
}

var arr = [9,15,3,6,4,2,5,10,3]
console.log(LS(arr))