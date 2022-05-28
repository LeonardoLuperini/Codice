function LS(arr: number[], a: number = Infinity): number{
    if(arr.length == 1) return 1
    else{
        var temp = arr.pop()
        var b: number = (temp)? temp : -Infinity
        if (b < a) return Math.max(LS(arr, b) + 1, LS(arr, a))
        return 0
    }
}

var arr: number[] = [9,15,3,6,4,2,5,10,3]

console.log(LS(arr))