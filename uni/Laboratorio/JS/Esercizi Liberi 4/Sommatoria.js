var somma = (h, ...t) => (t.length >= 1) ? (h + somma(...t)) : h;

console.log(somma(5,7,2))
console.log(somma(10,5,-8,-7))