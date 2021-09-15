
var canvas = document.createElement("canvas");
c = canvas.getContext("2d");
canvas.width = 1520;
canvas.height = 740;
document.body.appendChild(canvas);


var positionX = 1;
var positionY = 58;
var speed = 1.5;
var deceleration = 0.99;
var jumping = false;

var player = new Image();
player.src = "Images/player.png";
var background = new Image();
background.src = "Images/platformerBackground.png"

c.font = "25px Arial";
c.fillStyle = "white";
var textTut = "Use arrows to move and jump";
var textEnd1 = "Well done, you escaped with your live however you didn't carry out the task.";
var textEnd2 = "In embarrassment and fear for your life you flee the town.";
var textEnd3 = "Thanks for playing.";

    window.addEventListener("keydown", pressKey, true);
    function pressKey(event) {
        switch (event.keyCode) {
            case 39: //right
                speedX = speed;
                deceleration = 0.99;
                break;
            case 37: //left
                speedX = -speed;
                deceleration = 0.99;
                break;
            case 38: //up
                if (jumping == false) {
                    speedY = -8;
                    jumping = true;
                }
                break;
        }
    }

setInterval(function gameUpdate() { //game update
    //Drawing images
    c.drawImage(background, 0, 0);
    c.drawImage(player, positionX, positionY, 32, 32);

    //Movement
    positionX += speedX;
    positionY += speedY;
    speedX *= deceleration;
    speedY += 0.18; //Gravity

    //Jumping deceleration
    if (jumping == true) {
        deceleration = 0.9999;
    }
    else {
        deceleration = 0.985;
    }

    //Collisions
    //Edge of the screen
    if (positionX > 1488) {
        positionX = 1488;
    }
    if (positionX < 0) {
        positionX = 0;
    }
    //floor
    if (positionY >= 668) {
        positionY = 668;
        speedY = 0;
        jumping = false;
    }
    //Sealing
    if (positionY < 1) {
        positionY = 1;
    }
    //Platforms
    if (positionY >= 58 && positionY <= 90 && positionX >= 0 && positionX <= 328) {
        speedY = 0;
        jumping = false;
        positionY = 58;
    }
    if (positionY >= 222 && positionY <= 262 && positionX >= 296 && positionX <= 656) {
        speedY = 0;
        jumping = false;
        positionY = 222;
    }
    if (positionY >= 222 && positionY <= 262 && positionX <= 328) {
        positionX = 328;
    }
    if (positionY >= 222 && positionY <= 262 && positionX >= 624 && positionX <= 630) {
        positionX = 624;
    }
    if (positionY >= 102 && positionY <= 142 && positionX >= 625 && positionX <= 820) {
        speedY = 0;
        jumping = false;
        positionY = 102;
    }
    if (positionY >= 386 && positionY <= 426 && positionX >= 810 && positionX <= 1312) {
        speedY = 0;
        jumping = false;
        positionY = 386;
    }
    if (positionY <= 386 && positionY >= 100 && positionX <= 820 && positionX >= 810) {
        positionX = 820;
    }
    if (positionY >= 668 && positionX >= 1190 && positionX <= 1192) {
        positionX = 1192;
    }
    if (positionY >= 628 && positionY <= 668 && positionX <= 1191 && positionX >= 997) {
        speedY = 0;
        jumping = false;
        positionY = 628;
    }
    if (positionY >= 668 && positionX <= 1030 && positionX >= 995) {
        positionX = 995;
    }
    if (positionY <= 668 && positionY >= 580 && positionX <= 744 && positionX >= 734) {
        positionX = 744;
    }
    if (positionY >= 548 && positionY <= 558 && positionX >= 548 && positionX <= 743) {
        speedY = 0;
        jumping = false;
        positionY = 548;
    }
    if (positionY <= 668 && positionY >= 580 && positionX <= 550 && positionX >= 548) {
        positionX = 548;
    }
    if (positionY <= 668 && positionY >= 468 && positionX <= 536 && positionX >= 534) {
        positionX = 536;
    }
    if (positionY >= 468 && positionY <= 474 && positionX <= 536 && positionX >= 340) {
        speedY = 0;
        jumping = false;
        positionY = 468;
    }
    if (positionY <= 668 && positionY >= 468 && positionX <= 342 && positionX >= 340) {
        positionX = 340;
    }

    //Display text
    if (positionY <= 262 && positionX <= 328) {
        c.fillText(textTut, 50, 50);
    }
    if (positionY >= 400 && positionX <= 340) {
        c.fillText(textEnd1, 50, 400);
        c.fillText(textEnd2, 50, 425);
        c.fillText(textEnd3, 50, 450);
    }
}, 0)
