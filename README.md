# WindowPong
#### A new take on the classic game of Pong where each sprite is an application window

Window Pong is a personal exploration into using the WindowsAPI for non conventional applications such as moving windows automatically or in response to user input that is more complex than simply dragging and dropping. Perhaps the ability to have more control over the function of an application window is useful for providing a smoother user experience. For example, if a window pops up and the user's mouse is right where it needs to be to click a particular button. Since this application uses the WindowsAPI, it only works on Windows.

Some design considerations:
- The ball is given a consistent x velocity (which increases every hit). Each time the ball hits a paddle, it is given a random y velocity. This makes the ball travel at different speeds, but makes the required reaction time consistent since the amount of time that each player has to react is only dependent on the horiztonal speed of the ball.
- The bounding box of each paddle is thinner than the paddle's window to make sure the ball does not bounce off the top or bottom of the paddle

Gameplay:
- Q to quit (the x button on the window is disabled)

Left paddle controls
- W (up)
- S (down)
- D (launch ball)

Right paddle controls
- Up Arrow (up)
- Down Arrow (down)
- Left Arror (launch ball)

Future Changes/Problems to Solve:
- Add AI
- Needs a score board
- Can put fun designs into each window to add more visual interest and clarity of what each window functions as in the game.
- Needs a start menu
- Needs a game over menu
- Allow the speed of the paddles to increase over time as the ball speed increases so the limiting factor is the player's skill not the game being unable to keep up with the speed of the gameplay.
