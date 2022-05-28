const canvas = document.getElementById('canvas1')
canvas.width = document.body.clientWidth; //document.width is obsolete
canvas.height = document.body.clientHeight; //document.height is obsolete

const ctx = canvas.getContext('2d');
//Quando la pagina viene ridimensionata questa funzione parte
//e fa in modo che se c'era disegnato qualcosa questo qualcosa non venga deformato
window.addEventListener("resize", () => {
    canvas.width = document.body.clientWidth; //document.width is obsolete
    canvas.height = document.body.clientHeight; //document.height is obsolete
    //ciò che voglio che sia disegnato
    
    ctx.beginPath()
    ctx.rect(10, 10, 10, 10)
    ctx.fillStyle = 'limegreen'
    ctx.fill()
})

ctx.beginPath()
ctx.rect(0, 0, innerHeight, innerWidth)
ctx.fillStyle = 'limegreen'
ctx.fill()