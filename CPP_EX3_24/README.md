# Catan & Algorithms

This project implements a series of algorithms for the Catan game using representations of the game board, players, and other elements.

## Overview

The project comprises three main components: `Board.cpp`, `Player.cpp`, and `Catan.cpp`, supplemented by a demonstration file `Demo.cpp`. Comprehensive unit tests are provided in the `tests` directory.

### `Board.cpp`

This file contains the implementation of the `Board` class, which represents the Catan game board. Key functionalities include:

- `distributeResources`: Randomly distributes resources and numbers across the board.
- `setupManualBoard`: Allows manual setup of the board with specified resources and numbers.
- `getLandPlots`: Returns the current state of the land plots on the board.
- `addPlayerSettlement`: Adds a settlement for a player at specified locations.
- `addPlayerRoad`: Adds a road for a player between specified locations.
- `addPlayerCity`: Adds a city for a player at specified locations.
- `getPlayerSettlements`: Returns the settlements of all players.
- `getPlayerRoads`: Returns the roads of all players.
- `getPlayerCities`: Returns the cities of all players.

### `Player.cpp`

This file contains the implementation of the `Player` class, which manages player resources, development cards, points, and game actions. Key functionalities include:

- `addResource`: Adds resources to the player's inventory.
- `useResource`: Uses specified resources from the player's inventory.
- `getResourceCount`: Returns the count of a specified resource type.
- `placeSettlement`: Places a settlement for the player.
- `placeRoad`: Places a road for the player.
- `placeCity`: Upgrades a settlement to a city for the player.
- `buyDevelopmentCard`: Buys a development card for the player.
- `rollDice`: Simulates rolling dice and distributes resources accordingly.
- `trade`: Trades resources with another player.
- `endTurn`: Ends the player's turn.
- `printPoints`: Prints the player's points.
- `print`: Prints the player's details.

### `Catan.cpp`

This file contains the implementation of the `Catan` class, which manages the overall game, including players and the game board. Key functionalities include:

- `ChooseStartingPlayer`: Chooses the starting player.
- `getCurrentPlayer`: Returns the current player.
- `nextTurn`: Moves to the next player's turn.
- `printWinner`: Prints the winner of the game.

### `Demo.cpp`

Provides examples demonstrating the usage of the implemented game functionalities to showcase their practical applications.

## Usage

To compile and run the demo program:

<div dir='ltr'>
  
    make demo && ./demo
    
</div>

To compile and run the test program:

<div dir='ltr'>
  
    make test && ./test
    make valgrind
    make tidy
    
</div>

