function titolizza() {
    return this.toUpperCase().split("").join(" ")
}

String.prototype.titolo = titolizza

console.log(`pippo ${5+6}`.titolo())