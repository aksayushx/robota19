# robota 19

## INTRODUCTION

Thanos and The Curious Bot:
Thanos has access to the three infinity stones - Mind, Time and Space. But his robo daughter
Nebula has gone rogue. He needs to get the other three stones (Soul, Power, Reality) to achieve his
goal ('The Snap'). Since Thanos is busy with the Avengers, help Thanos create a bot that help get
the other infinity stones .The three infinity stones are located in three different places, you need to
get the three stones and place them in the Base.

Design a Semi-Autonomous robot which could retrieve the stone by following a defined path.
*The game involves the use of IR sensors, which would be used to complete the line following part,
and the Bluetooth module which would be used for the locomotion.

## TASK DESCRIPTION
The match starts with the bot having autonomous control. It should follow the line until it
encounters an obstacle using IR Sensors on the path ie Boxes. It should then Switch over to
manual mode and lift/drag the Boxes and place it on the labelled Base position, only one Box can
be lifted/dragged at a time and the bot has to go to the connected node of white line, the user
then sends a signal to the bot and assumes autonomous control, the process is repeated until it
reaches finish node.
When the bot is in autonomous mode a blue led should glow and when the bot is in manual mode
a red led should glow. The Path might have a few checkpoints at some places the bot should not
respond to the marker, If the bot responds points will be deducted accordingly.
The Background will be Black and the line will be White of uniform width. If any team assumes
manual control for following the line it will be immediately disqualified. The Bot has to go by the
order, picking up the boxes in order of the number on it.

## Arena for robota 

![Arena](https://github.com/aksayushx/robota19/blob/master/RobotaArena.jpeg) 
