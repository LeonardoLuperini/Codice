function tnum(a) {
    var num = 0

    function ricorsioneTNum([h, ...t]) {
        if (Array.isArray(h)){
            ricorsioneTNum(h)
        }
        else if (typeof h == "number"){
            num++
        }
        if(t.length>0){
            ricorsioneTNum(t)
        }
    }
    ricorsioneTNum(a)
    return num
}

var arr = [1,4,[3,[[5]],{3:4}]]
console.log(tnum(arr))