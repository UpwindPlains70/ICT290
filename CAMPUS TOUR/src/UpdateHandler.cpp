-int 'Level' = 0
- string 'State' = Not Ready
- map < int turn, bool isPC> 'isPCTurnMap'
- map < int turn, int ID> 'turnIDMap'
- map < int turn, bool isDead> 'turnDeadMap'
- vector<Player> playerList
- bool pcHasAction
- Player nowPlayer
- Map nowMap
- vector<Enemy> nowEnemies
- maxTurn
- EntityAbility nowAbility
- int nowAbilityID

//IF State = Not Ready
Get Number of Players
Choose the first player's class and push_back the new player
Repeat till all players are done
If number of players selected and all player classes are set
State = Ready

//IF State = Ready
Doors can open now
if in area to teleport
State = Initializing

//IF State = Initializing
Choose map as 'nowMap'
draw map
empty isPCTurnMap
empty turnIDMap
empty turnDeadMap
empty nowEnemies
Figure out enemies in Level
Place enemies into 'nowEnemies'
Display enemy stats(all at once or one at a time due to who is selected)
Randomly choose location
Place first enemy
If more enemies
While('found' == false)
Randomly choose location
for (int i = -2; i <= 2; i++)
for (int j = -2; j <= 2; j++)
'newX' = 'locationX' + i
'newY' = 'locationY' + j
if (there is an enemy at map[newX][newY])
'found' = true
Repeat for each
Do the same for players
maxTurn = number of entities
Figure out turn order
(use a vector of integers filled with each number up to number of entities)
(then get random location in vector and get the turn from that)
(then removing that turn as it is used makes life easier)
Place turn in each enemy and character
Place if enemy or character into isPCTurnMap
Set all of turnDeadMap to false
State = Start Turn

//IF State = Start Turn
if turnDeadMap[Turn] == true
skip turn
if (isPCTurnMap[Turn] == false)
enemyTurn(turnIDMap[Turn])
else
playerTurn(turnIDMap[Turn])

//enemyTurn(int enemyID)
Enemy ai = nowEnemies.at(enemyID)
if (ai.stun == 1)
show stun being removed
ai.stun = 0
endturn()
else if (ai.stun == 0.5)
if in range
attack
show stun being removed
ai.stun = 0
endturn()
else
move + attack
endturn()


//playerTurn(int playerID)
Player pc = players.at(playerID)
display pc stats
pc.movementLeft = pc.movement
if (pc.stun == 1)
show stun being removed
pc.stun = 0
endturn()
else if (pc.stun == 0.5)
pc.movementLeft = 0
all pc ability cooldownLeft -= 1
pc.stun = 0
pcHasAction = true
nowPlayer = pc
State = Action

//endturn()
check if any player or enemy is dead
if so delete them from list
and add their turn to 'turnDeadMap'
remove model off board
make that space empty on map
check if no more enemies
State = Win
check if no more players
State = Lose
State = Start Turn
Turn += 1
if turn > maxTurn
turn = 1

//IF State = Action
if nowPlayer.MovementLeft > 0
if keyboard 'w'
nowPlayer.posZ += 1
nowPlayer.MovementLeft--
if keyboard 's'
nowPlayer.posZ -= 1
nowPlayer.MovementLeft--
if keyboard 'a'
nowPlayer.posX -= 1
nowPlayer.MovementLeft--
if keyboard 'd'
nowPlayer.posX += 1
nowPlayer.MovementLeft--
if pcHasAction = true
if keyboard '1'
nowAbilityID = 0
nowAbility = nowPlayer.GetAbility(0)
if cooldownLeft
if Ability.Unique = true
uniqueAbility()
if Ability.aoe > 1
State = AttackAOE
else
State = Attack
if keyboard '2'
nowAbilityID = 1
nowAbility = nowPlayer.GetAbility(1)
if cooldownLeft
if Ability.Unique = true
uniqueAbility()
if Ability.aoe > 1
State = AttackAOE
else
State = Attack

if keyboard '3'
nowAbilityID = 2
nowAbility = nowPlayer.GetAbility(2)
if cooldownLeft
if Ability.Unique = true
uniqueAbility()
if Ability.aoe > 1
State = AttackAOE
else
State = Attack
if nowPlayer.MovementLeft = 0 and pcHasAction = false
endturn()
if keyboard '`'
endturn()

//IF State = Attack
Show enemy select screen
if decided
nowPlayer.GetAbility(nowAbilityID).cooldownReset()
if in range
attack(enemy)
State = Action

//IF State = Win
if level = 10
show final win screen
else
show level win screen
upgrade()
level++
State = Initializing

//If State = Lose
Show loosing screen

//uniqueAbility()
needs to be filled in with special actions and what happens

//upgrade()
needs to be filled in with upgrading each character and displaying the update

//attack(enemy)
pcHasAction = false
foreach duplicate
if tohit
damage
stun

//IF State = AttackAOE
Show aoe select screen
if decided
nowPlayer.GetAbility(nowAbilityID).cooldownReset()
foreach enemy in aoe
attack(enemy)
