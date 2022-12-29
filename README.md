# Rabbits-And-Flowers
a simple 2-player 2D game made in C++ using the SDL library

<a href="url"><img src="https://scontent.fias1-1.fna.fbcdn.net/v/t1.15752-9/320961861_521010643144654_5536922883851198985_n.png?_nc_cat=102&ccb=1-7&_nc_sid=ae9488&_nc_ohc=TzByljFe0rIAX-I9uKm&_nc_ht=scontent.fias1-1.fna&oh=03_AdS5kiV7fRcT5ALCbbABKe8N4YEEdDeN-ssF8C3fIwpcDA&oe=63D34C83" align="center" height="540" width="720" border="black"></a>

# Run
1. Open *SDL_GameTemplate.sln* in Visual Studio and compile the project
2. Put all dll files from *DLL* folder in *Debug* folder in project solution folder
- if an error occurs, try to copy the *assets* folder from *SDL_GameTemplate/assets* to *Debug* folder in project solution folder
- you can also change the settings like speed or size in the *Configuration.h* file if you want to

# Gameplay
In this gameplay, players take on the role of either Jack or Jill, the two rabbits competing to gather the most carrots on a field full of flowers. The game begins with both rabbits starting near the center of the field, and the goal is to collect as many carrots as possible before time runs out (after 60s).

As they hop through the field, players must be careful not to touch the cursed rose flower, but when one of them does, the opponent gets a point in return. Players also should be aware of the other 4 different flowers and what effect can have on them, especially the poison flower that can kill the rabbit that gets it within 10 seconds unless the poisoned rabbit catches the other rabbit, making the poisoned rabbit the winner of the round.

The game ends when one of the rabbits score 3 points, but every single time someone gets a point, the next round is going to be much harder for the one who previously scored. Will you be able to outdo your opponent and emerge victorious on the flower field?

# Plot
*Once upon a time, two rabbits named Jack and Jill lived in a small burrow at the edge of a beautiful field full of flowers. One day, a terrible storm hit the field, causing all of the other rabbits to flee or be killed. Jack and Jill were the only two rabbits left alive on the field.*

*At first, they were relieved to have survived the storm. But as they looked around, they realized that there were not enough carrots for both of them to survive. They knew that they had to come up with a plan in order to determine which one of them would get to stay on the field and eat the precious carrots.*

*They decided to hold a competition to see who could gather the most carrots. The rabbit who collected the most carrots would be the one to survive and remain alive on the flower field.*

*As they hopped through the flowers, they noticed a many different flowers, especially the beautiful rose flowers. They were drawn to their sweet scent and vibrant color, but they knew that they had to stay away from them. Legend had it that the rose flowers were cursed, and that any rabbit who touched them would perish.*

*From that day on, Jack and Jill worked hard to gather as many carrots as they could, always avoiding the cursed rose flower. They became fiercely competitive, always trying to outdo each other, but in the end the fate of one of them will come to an end.*

# Characters
**Jack** is a blue rabbit who lives on a field full of flowers. He is fiercely determined and works hard to gather as many carrots as possible in order to survive. Despite facing challenges and temptations along the way, Jack remains focused and never gives up.

**Jill** is a red rabbit who also lives on the flower field with Jack. She is a determined and hardworking rabbit that remains kind and optimistic, always looking for new opportunities and adventures.

# Controls
- Jack controls: Arrow keys
- Jill controls: WASD keys

# Objects
Based on the number of victories the player has:
| Object        | Effects                                | 0 Victories | 1 Victory | 2 Victories |
| ------------- | -------------------------------------- | ----------- | --------- | ----------- |
| Rose          | Lose game                              | -           | -         | -           |
| Carrot        | Score 1 Point                          | -           | -         | -           |
| -             | Need ... to win the round              | 10          | 20        | 30          |
| -             | Increase enemy speed by ...            | 0x          | 1x        | 2x          |
| Green flower  | Get poisoned for 10s                   | -           | -         | -           |
| Blue flower   | Reduce player speed by ...             | 1x          | 2x        | 3x          |
| -             | Increase time left from poison by ...s | 6           | 3         | 0           |
| Pink flower   | Invert player controls for ...s        | 2           | 4         | 8           |
| -             | Invert enemy controls for ...s         | 4           | 2         | 0           |
| Yellow flower | Lose ... points                        | 1           | 2         | 3           |
| -             | Increase player speed by ...           | 3x          | 2x        | 1x          |
