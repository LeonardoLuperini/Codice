function strafatto(n){
    function rec(n){
        var res = []
        for(let i = 2; i*i <= n; i++){
            if (n%i == 0){
                let temp = rec(n/i)
                if(temp.length > 0){
                    for(e of temp){
                        let temp2 = [i, ...e]
                        res.push(temp2)
                    }
                }
                res.push([i, n/i])
            }
        }
        return res
    }


    return rec(n)
}

console.log(strafatto(12))