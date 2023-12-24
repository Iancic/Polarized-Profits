----------Polarized Profits--------
Made by Iancic David for the BUas intake.
Run the executable file (.exe).

https://github.com/Iancic/Polarized-Profits

----------Tutorial Level 1---------
How To Play:
W, A, S, D - Move The Magnet
Spacebar - Change Polarity (Red Attracts Coins, Blue Deflects Coins)

Rules: 
You have 90 seconds to collect the coins into the piggy bank.
Avoid getting to close to the magnet. You can break your coins if not careful.
Avoid the thief hands. They wanna steal your coins.

----------Tutorial Level 2---------
How To Play:
A,D - Move The Hands Left And Right

Rules:
Break the piggy bank and try to catch as many coins as possible.

----------FOR DEVELOPER: To Do List Until Deadline (Last Change: 18.12.23)----------

PowerPoint Presentation:
1) Fill in text for Portfolio Slides 
2) Go over Portfolio Slides And Rework Photo Arrangement
3) Fill In Slides For Assigment
4) Make an itch.io page for the game. GOOD LOOKING PAGE
5) Prepare a script for interview
6) Do a mock presentation on discord with a volunteer

Code Docs:
1) Rework and request feedback at the end of the month for code
2) Find, document and learn all concepts from the code
3) Make some mock script for the powerpoint / interview about the overall code

First Level:
Hand Algorithm:
1. Spawn a right hand and a left hand (Initialization, Update, Render, Spawner). DONE 20.12.2023
2. Move the hand. (Move Function that counts to how many second the hand should move before it stops. When counter reaches 0, change the sprite to closed fist then change movement direction, kill the hand after certain amount (retraction function) ). 
3. Collision with coins. (Destroy the coin, change the hand sprite and activate retraction function).
4. Play with difficulty of the hand.

Second Level:
1. Make Begging Hand Class (Initialization, Update, Render, Spawner).
2. Input for begger movement (Left And Right + Bounds For Movement).
3. Spawn coins based on balance function (call the spawn method based on balance / 2 how much coins to spawn) (play with the random positions).
4. Begger collision with coins.
5. Pig Animation With hammer (after hammer kills pig spawn the coins).
6. If all coins have fallen, take the player to the end screen.

End Screen:
a) Play Again Button
b) Exit Game Button
c) Amount Of Money Collected UI
d) Funny Message At The End

SFX:
a) Magnet Sound At Polarity Change (+ and - polarity)
b) Piggy Bank Sound At Collision
c) Hand Failed Retracting Sound
d) Hand Catched Gold Sound 
e) Main Menu / End Screen
f) Level 1 / Level 2 Soundtrack

Visual Overhaul:
a) Magnet Sprite
b) Plus / Minus Polarity Background
c) Piggy Bank Sprite
d) Simple Coin, Valuable Coin, Hairclip
e) Left & Right Hand
f) Font
g) Menus Rework (With Main Menu Tutorial Image in Photoshop Collage)
h) Code Transition Class that gets player at every scene beggining and Transition End At Changing Scene

Other Notes:
make a list with predefined flags and object pooling
enumerators as game scene manager
pointers
case if s
classes 
headers
function and other dictionary

particles don t get deleted just get flagged

visual ray of attraction / denial

INTERVIEW ARE YOU TEACHEABLE, CHALLENGES THAT I OVERCOME WHAT WAS HARD ON THE GAME, 3DGEP COURSE

CHECK FOR LINKS, IMG, VIDEOS, MOCK INTAKE

CMGT - cREATIVE MEDIA AND GAME TECHNOL

BUAS CMGT
