function Crocette(A) {
    class TooSmallException extends Error {}
    class InvalidFormatException extends Error {}
    class BadContentException extends Error {}
    
    function isCrocetta(A, i ,j){
        var crocetta = [[0,1,0],
                        [1,1,1],
                        [0,1,0]]

        for (let k = 0; k < 3; k++){
            for (let l = 0; l < 3; l++){
                if ( ! (A[i+k][j+l] == crocetta[k][l]) ) return false
            }
        }
        return true
    }

    var r = A.length
    var c = A[0].length
    if (r < 3 && c < 3) throw new TooSmallException()
    for (row of A) { if (row.length != c) throw new InvalidFormatException() }
    
    for (let i = 0; i <= r-3; i++){
        for ( let j = 0; j <= c-3; j++){
            if (A[i][j] == 0){
                if (isCrocetta(A, i ,j)) console.log(`A[${j+1},${i+1}]`)
            }
            else if (A[i][j] != 1) throw new BadContentException()
        }
    }
}

var A =[[ 1,0,0,1,1 ],
        [ 0,1,0,1,0 ],
        [ 1,1,1,1,1 ],
        [ 0,1,0,1,0 ],
        [ 1,1,1,1,1 ],
        [ 0,1,0,1,1 ]]

var B =[[1,0,0],
        [1,0,2],
        [0,1,1]]


Crocette(A)
Crocette(B)