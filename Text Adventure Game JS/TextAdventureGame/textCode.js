//Author: Maciej Dowbor
//Module Title: Computer Science and Web Technologies Primer
//Module Code: MED4141
//Date: 26/10/2019

const textElement = document.getElementById("text");
const optionButtonsElement = document.getElementById("optionButtons");

//Declearing variables
var randomNumber = {};
var fight = {};
var armWrestle = {};
var items = {};

//RNG to determine random outcomes
//Depending on the number generated, different values would be assigned to variables that determine the ID of the next scene
randomNumber = Math.floor((Math.random() * 100));
if (randomNumber >= 50) {
    fight = 5;
}
else {
    fight = 6;
}
if (randomNumber >= 75) {
    armWrestle = 11;
}
else {
    armWrestle = 12;
}
//Resets items and displays 1st scene
//This function is also used to restart the game when player loses
function setUpGame() {
    items = {};
    displaySceneID(0);
}
//Displays options that do not require items and options that do (only if the player has the required item)
function showOption(option) {
    return option.requiredItems == null || option.requiredItems(items);
}
//Displays scenes according to their ID
function displaySceneID(currentID) {
    var scene = scenes.find(scene => scene.ID === currentID); //Finds the current scene ID

    textElement.innerText = scene.text; //Sets up the text above option boxes depending on current scene ID

    //Removes previous option buttons
    while (optionButtonsElement.firstChild) {
        optionButtonsElement.removeChild(optionButtonsElement.firstChild);
    }
    //Displays buttons
    scene.options.forEach(option => {
        if (showOption(option)) { //Sets up buttons and text inside them for every option in current scene
            const btn = document.createElement("btn");
            btn.innerText = option.text;
            btn.classList.add("button");
            btn.addEventListener("click", () => selectOption(option));//When the button is clicked, selectOption function is carried out
            optionButtonsElement.appendChild(btn);
        }
    })
}


function selectOption(option) {
    if (option.nextID <= -2) { //Used to restart the game, if the value of nextID of selected option is lower or equal to -2 , the game will restart
        setUpGame(); //Runs this function to remove any items that player acquired and displays the menu
    }
    if (option.nextID >= 20) {
        window.location.href = "http://localhost:52019/PlatformerGame.html";
        //When the player completes all scenes, a new HTML file will open that will run the platformer part of my game
        //I did it this way to avoid any problems and because of its simplicity
    }
    items = Object.assign(items, option.setItems); //Acquiring items
    displaySceneID(option.nextID); //Sets the displaySceneID to the nextID in selected option
}

// Array of scenes with assigned ID to tell the displaySceneID function what text and options to show
var scenes = [
    {
        ID: -1,
        text: "Use your mouse to click the buttons to choose what you want to do. Your choices will affect your story by giving you more or less options to interact with other characters that could lead to other outcomes.",
        options: [
            {
                text: "Main menu",
                nextID: 0
            }
        ]
    },
    {
        ID: 0,
        text: "Menu",
        options: [
            {
                text: "Start",
                nextID: 1
            },
            {
                text: "How to play",
                nextID: -1,
            }
        ]
    },
    {
        ID: 1, //ID of the scene
        text: "You’re a mercenary on your way to a local town to find a job. As you follow a path to the town, you stumble upon a troubled eldery man holding a wooden wheel and an old cart tipped on its side next to him. “Excuse me sir, would you mind helping an old man in need?”.",
        options: [ //Available options during this scene
            {
                text: "Help him", //Displayed text of this option
                setItems: { gold: true }, //If this option is picked, player gains gold which will unlock options in future scenes
                nextID: 3 //Next scene ID (if this option is picked, scene 3 is shown)
            },
            {
                text: "Demand payment first",
                setItems: { gold: true },
                nextID: 2
            },
            {
                text: "Apologise and tell him you don’t have time for this. You carry on walking",
                nextID: 2
            },
            {
                text: "Ignore the old man and carry on walking",
                nextID: 2
            }
        ]
    },
    {
        ID: 2,
        text: "You have arrived at your destination. As you try to enter the town, two guards come over and start questioning you. “What brings you here?” Asked one of the guards. “I’m a mercenary, I’m traveling from town to town in search of commissions.” you replied. “Oh a mercenary, you bring a lot of trouble, but your pouch is always full of gold. We aren’t supposed to let anyone in, but if you pay us, we will let you through”.",
        options: [
            {
                text: "Pay them",
                requiredItems: (currentItems) => currentItems.gold, //In order for this option to be displayed, the player would have to acquire gold in a previous scene
                setItems: { gold: false }, //Removes gold from the player
                nextID: 4
            },
            {
                text: "You don't have any gold, try to fight them",
                nextID: fight //fight is a variable that is randomly determined when the game is initialised
            }
        ]
            
    },
    {
        ID: 3,
        text: "To thank you for your troubles, the old man gave you a few gold coins and a ride to the town. As you travel along the main road, you see a couple of places that interest you. As you get off the cart, you thank the old man and head towards…",
        options: [
            {
                text: "A tavern",
                nextID: 7
            },
            {
                text: "A magic shop",
                nextID: 8
            },
            {
                text: "A statue surrounded by common folk",
                nextID: 9
            },
            {
                text: "A wealthy looking man angrily walking in front of a courthouse",
                nextID: 10
            }
        ]
    },
    {
        ID: 4,
        text: "You enter the town feeling a little lighter. As you travel along the main road, you see a couple of places that interest you. You decide to go to…",
        options: [
            {
                text: "A tavern",
                nextID: 7
            },
            {
                text: "A magic shop",
                nextID: 8
            },
            {
                text: "A statue surrounded by common folk",
                nextID: 9
            },
            {
                text: "A wealthy looking man angrily walking in front of a courthouse",
                nextID: 10
            }
        ]
    },
    {
        ID: 5,
        text: "As you draw your sword, the guards realise you have no intention to pay them. Your years of experience as a mercenary taught you how to fight and you defeat the guards with ease. While cleaning what remained of the guards off your sword, you travel along the main road and see a couple of places that interest you. You decide to go to…",
        options: [
            {
                text: "A tavern",
                nextID: 7
            },
            {
                text: "A magic shop",
                nextID: 8
            },
            {
                text: "A statue surrounded by common folk",
                nextID: 9
            },
            {
                text: "A wealthy looking man angrily walking in front of a courthouse",
                nextID: 10
            }
        ]
    },
    {
        ID: 6,
        text: "As you draw your sword, the guards realise you have no intention to pay them. You strike one of the guards with your sword however it has no effect. Their thick armour deflects your attacks. Upon realising you have no chance of beating them, you beg them to spare your life. They restrain you and throw you into one of their jail cells.",
        options: [
            {
                text: "Restart",
                nextID: -2  //If the ID of the next scene is <= -2 then the selectOption function restarts the game
            }
        ]
    },
    {
        ID: 7,
        text: "You walk into the tavern but unfortunately it’s almost empty. In the corner, you see a group of men surrounding two people sitting opposite each other. As you get closer, you can tell they had a bit to drink and are having an arm wrestling competition. Everyone starts to cheer as one of the hands slams the wooden table. The winner takes a sip of ale and looks at you “It’s very rare to see a new face here, what do you want?”. “I want no trouble, I’m a mercenary traveling from town to town in search of commissions.” you reply. A smug smile appears on the mans face “It’s your lucky day! I know someone that could use your help however, you will need to prove yourself before I can give you any more details. An arm wrestle should do it.”.",
        options: [
            {
                text: "Accept the challange",
                nextID: armWrestle
            },
            {
                text: "Use a strength potion and accept the challenge",
                requiredItems: (currentItems) => currentItems.strPotion,
                setItems: { strPotion: false },
                nextID: 11
            },
            {
                text: "You won’t participate in such primitive activities",
                nextID: 13
            }
        ]
    },
    {
        ID: 8,
        text: "You walk into the magic shop, the shelves are full of glowing potions and unusual artefacts. At the top of one of the bookshelves, you see a black cat watching you, behind the counter there is an old lady standing motionless with an empty stare. “H-hello” you say nervously “I’m a mercenary, I was wondering if there is anything you might want me to help you with”. You get no response, she could have a hearing problem so you repeat yourself, but again, no response. As you wave your hand in front of her face, you hear little taps on the countertop as the cat jumps down from the bookshelf. “She has been like this for a while now, if you could help me to prepare a potion that could save her, I would reward you with a potion of strength, I’m sure a mercenary could make use of it.” You stand motionless for a while just like the eldelry woman, in disbelief you shake your head and get yourself together.",
        options: [
            {
                text: "Help the talking cat",
                setItems: { strPotion: true },
                nextID: 14
            },
            {
                text: "It’s a damn cat, just take the potion and leave",
                nextID: 15
            },
            {
                text: "Run back outside to the main road",
                nextID: 13
            }
        ]
    },
    {
        ID: 9,
        text: "You walk towards the statue surrounded by people holding hands and running around it, you can also hear them chanting words you don’t understand. “COME MY BROTHER! PRAY WITH US!” maniacally shouts one of the participants. You slowly walk away as more heads turn towards you, their wide open eyes scare you more than anything you’ve come across so far. Fortunately they are too busy doing… whatever… that… is… You safely get away.",
        options: [
            {
                text: "Go back to the main road",
                nextID: 13
            }
        ]
    },
    {
        ID: 10,
        text: "You see a wealthy man walking around in circles in front of a courthouse. By the look on his face, you can clearly see he’s not happy with what happened in there. He notices you with the corner of his eye and walks towards you. “What are you looking at?” he shouted angrily. “You look like you could use a mercenary, thought I could offer you my services.” you replied. “Indeed, I could use your help, but I need to be sure you’re the right person for the job. My old friend is in the tavern, go and talk to him, he will let me know if you’re good enough.”.",
        options: [
            {
                text: "Go back to the main road",
                nextID: 13
            },
            {
                text: "You already proven you're strong enough",
                requiredItems: (currentItems) => currentItems.champion,
                nextID: 16
            }
        ]
    },
    {
        ID: 11,
        text: "You defeated the current champion of arm wrestling, everyone around you is shocked for a few seconds and then they start to celebrate your victory. Meanwhile, the now ex champion loses the smirk off his face and says “Didn’t expect so much strength in these noodle arms. I’ll tell my old friend that you are good enough for the job. He should be standing in front of the courthouse, try to not wind him up, he got himself in a lot of trouble recently.” You get up and squeeze yourself through the drunken mob to the exit.",
        options: [
            {
                text: "Go back to the main road",
                setItems: { champion: true },
                nextID: 13
            }
        ]
    },
    {
        ID: 12,
        text: "Unfortunately you are too weak, you lose the arm wrestle. Your opponent is so powerful that he knocks you off your seat. As you fall, the sword falls out of your seath and your hand lands on the hilt of the sword. The drunken crowd assumes you are trying to attack them and they run out of the tavern. Moments after, you see guards storming inside. You try to persuade them that you had no intention of fighting, but the guards aren’t having any of it. They restrain you and throw you into one of their jail cells.",
        options: [
            {
                text: "Restart",
                nextID: -2
            }
        ]
    },
    {
        ID: 13,
        text: "You are back on the main road in the town, where would you like to go now?",
        options: [
            {
                text: "A tavern",
                nextID: 7
            },
            {
                text: "A magic shop",
                nextID: 8
            },
            {
                text: "A statue surrounded by common folk",
                nextID: 9
            },
            {
                text: "A wealthy looking man angrily walking in front of a courthouse",
                nextID: 10
            }
        ]
    },
    {
        ID: 14,
        text: "“A potion of strength may come in handy, how do I prepare the potion you speak of?” you ask. “You see the two potions on the far right side, second row of the shelf. I want you to pour half of it into the other. I know, I know. It’s very simple, but there is little I can do with my pawns.” says the cat pointing towards a huge shelf full of potions that covers the whole wall. Without any questions, you do what the talking cat has told you. You pour half of the liquid from one flask into the other. You can feel the mixture warming up, colour of the potion changes colour from bright orange to black. It doesn’t feel like liquid anymore. “Quick, pour it into her mouth before it gets cold!” the cat shouted. You rush to the old lady and pour the black tar-like mixture into her mouth. “Take this strength potion and leave before she gets conscious.”. As you grab the potion you can see that her fingers began to twitch, you rush to the entrance and leave the shop. After what happened in there, you decide to be more careful where you go as this could have ended badly. Where will you go next?",
        options: [
            {
                text: "A tavern",
                nextID: 7
            },
            {
                text: "A magic shop",
                nextID: 8
            },
            {
                text: "A statue surrounded by common folk",
                nextID: 9
            },
            {
                text: "A wealthy looking man angrily walking in front of a courthouse",
                nextID: 10
            }
        ]
    },
    {
        ID: 15,
        text: "“There are all these potions laying around and the owner is clearly dead, there is only this damn cat around, I can take whatever I want.” you think to yourself. You open your leather bag and start filling it with flasks full of glowing liquid. The cat rolls its eyes and jumps onto the top shelf under which you’re casually stealing unknown, potentially hazardous, magical substances. The cat does what cats do best and pushes a potion from the top shelf straight onto your head. You start to feel like you’re burning, you can see your hair falling off your head. Your body starts to shrink and you feel like your insides begin to bubble. Shelf seems to be getting bigger every second and before you know it, you’ve shrunk so much you can see the carpet of dust underneath it. You look at your reflection in one of the broken shards of the glass flask that fell on your head and you realise that you are now a frog.",
        options: [
            {
                text: "Restart",
                nextID: -2
            }
        ]
    },
    {
        ID: 16,
        text: "“I’ve already talked to him, he said he will tell you about me.” you said. “Oh, you’re the one my friend talked about. Sorry, you don’t look as strong as he described you, but I’ll take his word for it. Recently I’ve gotten myself into some trouble with the mayor, tomorrow a person who hates my guts is going to testify against me. He has a lot of influence in this town and I’m sure he will do anything to put me in jail. I need you to get rid of him, if you succeed I’ll give you as much gold as he weights. He lives at the top floor of the mansion in the middle of the town, it’s not hard to spot, you can almost see it from here. He usually wears a dark blue cloak with golden royal army symbol, I’m sure you will recognise him.”. The door opens and you see a tall guy in silver armour and a dark blue cloak walking out of the courthouse. You realise that this is the guy wanted dead. Without a word you and your new employer walk in the opposite directions like you’ve never talked to each other. You decide that your best chance is to catch him at night in his apartment.",
        options: [
            {
                text: "Wait until midnight and sneak into his chambers.",
                nextID: 17
            }
        ]
    },
    {
        ID: 17,
        text: "Under the cover of the night you climb over the fence and sneak into the mansion. You can’t hear any noise coming from the building so you decide to walk up the spiral stairs. As you get to the top floor, you see light flickering from underneath the only door on this floor. You grab your sword and enter the room. Inside you see a man sitting on his bed that clearly was about to go to sleep and dark blue cloak with a golden symbol hanging over a chair. You have no doubt that this is the man you agreed to kill. As you run towards him and swing your sword, he reaches underneath his bed and wields his giant sword. He blocks your strike and pushes you away.",
        options: [
            {
                text: "Try to attack him again",
                nextID: 18
            },
            {
                text: "Throw your pouch of gold the old man gave you at him and attack again",
                requiredItems: (currentItems) => currentItems.gold,
                setItems: { gold : false},
                nextID: 19
            }

        ]

    },
    {
        ID: 18,
        text: "You charge at him again and swing your sword at his head. Your attack gets blocked again knocking your sword out of your hand. You had enough, this guy is too strong for you. Unfortunately he now stands between you and the door, your only option is to escape using the window and parkour your way down to the ground.",
        options: [
            {
                text: "Escape using the window",
                nextID: 20
            }
        ]
    },
    {
        ID: 19,
        text: "As the pouch of gold meets his face you rush towards him and strike with your sword. You slash his neck open and see him suffocating in his blood, you are sure he won’t survive. From the stairway you hear distant voices, the only way out of this chamber unseen is to escape through the window and parkour your way down to the ground.",
        options: [
            {
                text: "Escape using the window",
                nextID: 20
            }
        ]

    },
]

setUpGame(); //Initialise the game