function contaPossibilita(n) {
    if (n == 0) return 1
    else if (n == 1) return 2
    else return 2 * contaPossibilita(n - 1) + 3 * contaPossibilita(n - 2)
}

console.log(contaPossibilita(1))
console.log(contaPossibilita(7))