const { performance } = require('perf_hooks');

function Merge(a, p, q, r) {
    var old_p = p
    let temp = []

    while (p < q && q <= r) {
        if (a[p] < a[q]) {
            temp.push(a[p++])
        } else {
            temp.push(a[q++])
        }
    }

    if (p == q) {
        while (q <= r) {
            temp.push(a[q++])

        }
    } else {
        while (p < q) {
            temp.push(a[p++])
        }
    }

    for (let i = old_p; i <= r; i++) {
        a[i] = temp[i - old_p]
    }
}

function MergeSort(a, p = 0, r = (a.length - 1)) {
    if ((r - p) >= 1) {
        var q = Math.floor((p + r) / 2)
        MergeSort(a, p, q)
        MergeSort(a, q + 1, r)
        Merge(a, p, q + 1, r)
    }
}

function creaArray(a,n) {
    for( let i = 0; i<n; i++){
        a[i] = Math.random()*n
    }
}

var arr = [2, 6, 4, 8, 9, 7, 3, 5, 1]
var t0 = performance.now()
MergeSort(arr)
var t1 = performance.now()
console.log(`ci hai messo ${t1-t0} e l'array ordinato è:[ ${arr} ]`)

var a = []
creaArray(a,10000000)
var t0 = performance.now()
MergeSort(a)
var t1 = performance.now()
console.log(`ci hai messo ${t1-t0}`)