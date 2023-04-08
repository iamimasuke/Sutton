const canvas = document.getElementById('myCanvas')
const ctx = canvas.getContext('2d');

var x = canvas.width / 2
var y = canvas.height - 30



var dx = 2
var dy = -2


let ballRadius = 10


let tableHeight = 10
let tableWidth = 75

let lastMouseX = canvas.width / 2;
let intervalId = setInterval(draw, 10)
let retryFontSize = 25

let blockWidth = 75
let blockHeight = 20
let blockWidthCount = 5
let blockHeightCount = 5
let blockTotal = blockHeightCount * blockWidthCount
let blockEdgeSpace = 30
let blockSpace = 10
let blocks = []

let score = 0



for (let i = 0; i < blockHeightCount; i++) {
  blocks[i] = []
  for (let j = 0; j < blockWidthCount; j++) {
    blocks[i][j] = { x: 0, y: 0, state: 1 }
  }
}

function drawBlocks() {
  for (let i = 0; i < blockHeightCount; i++) {
    for (let j = 0; j < blockWidthCount; j++) {
      let b = blocks[i][j];
      if (b.state == 1) {
        b.x = blockEdgeSpace + j * (blockWidth + blockSpace);
        b.y = blockEdgeSpace + i * (blockHeight + blockSpace);

        ctx.beginPath()
        ctx.rect(blocks[i][j].x, blocks[i][j].y, blockWidth, blockHeight);
        if (i % 2 == 0 && j % 2 == 0) {
          ctx.fillStyle = 'blue';
        } else {
          ctx.fillStyle = 'pink'
        }
        ctx.fill()
        blockCollision()
      }
    }
  }
}


function drawBall() {
  ctx.beginPath()
  ctx.arc(x, y, ballRadius, 0, Math.PI * 2);
  ctx.fillStyle = 'pink'
  ctx.fill()
  ctx.closePath()
}



function collision() {
  if (x + dx < ballRadius | x + dx > -ballRadius + canvas.width) {
    dx = -dx;
  }
  if (y + dy < ballRadius) {
    dy = -dy;
  }
  if (y + dy + ballRadius == canvas.height - tableHeight && lastMouseX - 10 <= x && x <= lastMouseX + tableWidth + 10) {
    dy = -dy;
  }
  if (y + dy - ballRadius == canvas.height) {
    gameOver()
  }
}

function blockCollision() {
  for (let i = 0; i < blockHeightCount; i++) {
    for (let j = 0; j < blockWidthCount; j++) {
      let b = blocks[i][j]

      if (b.state == 1) {
        if (x > b.x && x < b.x + blockWidth && y + ballRadius > b.y && y < b.y + blockHeight) {
          dy = -dy;
          b.state = 0;
          score++
        }
      }
    }
  }
}

function showScore() {
  ctx.font = "15px Arial"
  ctx.fillStyle = 'pink'
  ctx.textAlign = 'left'
  ctx.fillText("Score:" + score, 5, 20);

}

function finish() {
  let count = 0
  for (let i = 0; i < blockHeightCount; i++) {
    for (let j = 0; j < blockWidthCount; j++) {
      if (blocks[i][j].state == 0) count++
      if (count == blockTotal) {
        clearInterval(intervalId);
        ctx.clearRect(0, 0, canvas.width, canvas.height)
        ctx.closePath()
        ctx.font = "30px Arial";
        ctx.fillStyle = "pink";
        ctx.textAlign = "center";
        ctx.fillText("Game Clear", canvas.width / 2, canvas.height / 2);
      }
    }
  }
}

function gameOver() {
  clearInterval(intervalId);
  ctx.clearRect(0, 0, canvas.width, canvas.height)
  ctx.closePath()
  ctx.font = "30px Arial";
  ctx.fillStyle = "red";
  ctx.textAlign = "center";
  ctx.fillText("Game Over", canvas.width / 2, canvas.height / 2);
  retry()
}

function retry() {
  ctx.font = "25px Arial";
  ctx.fillStyle = "white";
  ctx.textAlign = "center";
  ctx.fillText("Retry", canvas.width / 2, canvas.height / 2 + 50);

  canvas.addEventListener('click', function (event) {
    const rect = canvas.getBoundingClientRect();
    const mouseX = event.clientX - rect.left;
    const mouseY = event.clientY - rect.top;
    if (mouseX >= canvas.width / 2 - retryFontSize && mouseX <= canvas.width / 2 + retryFontSize && mouseY >= canvas.height / 2 + 50 - retryFontSize && mouseY <= canvas.height / 2 + 50 + retryFontSize) {
      location.reload();
    }
  });

}


function drawTable(x) {
  ctx.beginPath()
  ctx.rect(x, canvas.height - tableHeight, tableWidth, tableHeight);
  ctx.fillStyle = 'blue'
  ctx.fill()
}

function handleMouseMove(event) {
  const rect = canvas.getBoundingClientRect();
  const mouseX = event.clientX - rect.left;
  if (mouseX > canvas.width - tableWidth) mouseX = canvas.width - tableWidth;
  lastMouseX = mouseX
  drawTable(mouseX);
}



function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height)
  showScore()
  drawBlocks()
  drawBall()
  collision()
  blockCollision()
  drawTable(lastMouseX)
  x += dx
  y += dy
  acceleration()
  finish()
}

canvas.addEventListener('mousemove', handleMouseMove);