function Configurazioni(a,k) {
    for (var i = 0; i<=1; i++) {
        a[k] = i
        if (k == a.length - 1) console.log(a)
        else Configurazioni(a, k + 1)
    }
}

Configurazioni([,,,9], 0)