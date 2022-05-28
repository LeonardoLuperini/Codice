function insertion_sort(arr) {
    var key
    var i
    for (let j = 1; j < arr.length; j++) {

        key = arr[j]
        i = j - 1

        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i]
            i = i - 1
        }

        a[i + 1] = key

    }
}

function insertion_sort_dec(arr) {
    var key
    var i
    for (let j = 1; j < arr.length; j++) {

        key = arr[j]
        i = j - 1

        while (i >= 0 && arr[i] < key) {
            arr[i + 1] = arr[i]
            i = i - 1
        }

        a[i + 1] = key

    }
}

var a = [5, 2, 4, 6, 1, 3]
insertion_sort(a)
console.log(a)
var t0 = performance.now()
insertion_sort_dec(a)
var t1 = performance.now()
console.log(`ci hai messo ${t1-t0} e l'array ordinato è:[ ${a} ]`)

//Esercizion 2.1-3 pagina 19 cormen

function ricerca(a, e) {
    for (let i = 0; i < a.length; i++) {
        if (e == a[i]) return i
    }
}

var a = [5, 2, 4, 6, 1, 3]
console.log(ricerca(a, 4))
console.log(ricerca(a, 7))