const fs = require('fs')

var Alphabet = [
                "W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Z","X","C","V","B","N","M","Q",
                "q","w","e","r","t","y","u","i","o","p","a","s","d","f","g","h","j","k","l","z","x","c","v","b","n","m",
                "!","?",
                "1","2","3","4","5","6","7","8","9","0"
                ]

var passArray = []

for (let i = 0; i < 10; i++) {
    var randChar = Alphabet[Math.floor(Math.random()*Alphabet.length)]
    passArray.push(randChar)
}

var pass = passArray.join("")

try {
    fs.writeFileSync("C:\\Users\\Leonardo\\Desktop\\pass.txt", pass)
    // file written successfully
} catch (err) {
    console.error(err)
}

