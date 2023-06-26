<!-- Documentation des communication server -> GUI/AI -->

# Documentation

## How to use

### Server

To launch the server, you need to run the following command:

```bash
./zappy_server -p PORT -x MAP_WIDTH -y MAP_HEIGHT -n TEAM_NAME ... -c CLIENTSNB -f FREQUENCE
```

<br/><br/>

### Client

To launch the GUI client, you need to run the following command:

```bash
./zappy_gui -p PORT -h MACHINE_IP
```

<br/><br/>

### AI

To launch the AI, you need to run the following command:

```bash
./zappy_ai -p PORT -n TEAM_NAME -h MACHINE_IP
```

<br/><br/>
<br/><br/>

## Communication

Communication between the server and the GUI/AI exemple:
```bash
    -> GUI/AI to server
    <- server to GUI
```

All commands are case sensitive and must be followed by a newline.

<br/><br/>

### Connection

The GUI and the AI connect to the server using a TCP connection.
Once connected, the server sends the following message to the client:

```bash
    -> WELCOME
```

Then the client sends the following message to the server:

To connect as a GUI:
```bash
    -> GRAPHIC
```

To connect as an AI:
```bash
    -> TEAM_NAME
```

<!-- Server GUI Comunication -->
<br/><br/>

### Server / GUI Comunication

Once connected, the server sends the following messages to the GUI:

```bash
    <- msz WIDTH HEIGHT
    <- sgt FREQUENCE
    <- bct X Y q0 q1 q2 q3 q4 q5 q6
    <- tna TEAM_NAME
    <- pnw PLAYER_ID X Y ORIENTATION LEVEL TEAM_NAME
    <- enw EGG_ID PLAYER_ID X Y
```

The GUI can send the following messages to the server:

Get the map size:
```bash
    -> msz
    <- msz WIDTH HEIGHT
```

Get the content of a tile:
```bash
    -> bct X Y
    <- bct X Y q0 q1 q2 q3 q4 q5 q6
```

Get the content of the whole map:
```bash
    -> mct
    <- bct X Y q0 q1 q2 q3 q4 q5 q6
    <- bct X Y q0 q1 q2 q3 q4 q5 q6
    <- ...
```

Get the name of all the teams:
```bash
    -> tna
    <- tna TEAM_NAME
    <- tna TEAM_NAME
    <- ...
```

Get the position and orientation of a player:
```bash
    -> ppo PLAYER_ID
    <- ppo PLAYER_ID X Y ORIENTATION
```

Get the level of a player:
```bash
    -> plv PLAYER_ID
    <- plv PLAYER_ID LEVEL
```

Get the inventory of a player:
```bash
    -> pin PLAYER_ID
    <- pin PLAYER_ID X Y q0 q1 q2 q3 q4 q5 q6 q7 q8
```

Get the frequency of the server:
```bash
    -> sgt
    <- sgt FREQUENCE
```

Set the frequency of the server:
```bash
    -> sst FREQUENCE
    <- sst FREQUENCE
```

If the command is not recognized:
```bash
    <- suc
```

The server can also send events to the GUI:

A tile content changes:
```bash
    <- bct X Y q0 q1 q2 q3 q4 q5 q6
```

A player is born:
```bash
    <- pnw PLAYER_ID X Y ORIENTATION LEVEL TEAM_NAME
```

A player moves:
```bash
    <- ppo PLAYER_ID X Y ORIENTATION
```

A player changes level:
```bash
    <- plv PLAYER_ID LEVEL
```

A player inventory changes:
```bash
    <- pin PLAYER_ID X Y q0 q1 q2 q3 q4 q5 q6 q7 q8
```

A player expulses other(s) player(s):
```bash
    <- pex PLAYER_ID
```

A player broadcast a message:
```bash
    <- pbc PLAYER_ID MESSAGE
```

A player starts an incantation:
```bash
    <- pic X Y LEVEL PLAYER_ID PLAYER_ID ...
```

A player ends an incantation:
```bash
    <- pie X Y RESULT
```

A player lays an egg:
```bash
    <- pfk PLAYER_ID
```

A player drops an object:
```bash
    <- pdr PLAYER_ID OBJECT
```

A player takes an object:
```bash
    <- pgt PLAYER_ID OBJECT
```

A player dies:
```bash
    <- pdi PLAYER_ID
```

An egg is laid:
```bash
    <- enw EGG_ID PLAYER_ID X Y
```

A player is connected to an egg:
```bash
    <- ebp EGG_ID
```

An egg hatches:
```bash
    <- eht EGG_ID
```

An egg dies:
```bash
    <- edi EGG_ID
```

The game is over:
```bash
    <- seg TEAM_NAME
```

The server send a message to the gui:
```bash
    <- smg MESSAGE
```

<!-- Server AI Comunication -->
<br/><br/>

### Server / AI Comunication

Once connected, the server sends the following messages to the AI:

```bash
    -> REMAINING_SLOTS_IN_TEAM
    -> WIDTH HEIGHT
```

The AI can send the following messages to the server:

Move forward:
```bash
    -> Forward
    <- ok
```

Turn left:
```bash
    -> Left
    <- ok
```

Turn right:
```bash
    -> Right
    <- ok
```

Look around:
```bash
    -> Look
    <- [tile1, tile2, ...]
```

Get the current inventory:
```bash
    -> Inventory
    <- [food q0, linemate q1, ...]
```

Send a message to the team:
```bash
    -> Broadcast MESSAGE
    <- ok
```

Get the remaining slots in the team:
```bash
    -> Connect_nbr
    <- REMAINING_SLOTS_IN_TEAM
```

Fork a new player:
```bash
    -> Fork
    <- ok
```

Eject players from the tile:
```bash
    -> Eject
    <- ok/ko
```

Death of the player:
```bash
    <- dead
```

Take an object from the tile:
```bash
    -> Take OBJECT
    <- ok/ko
```

Drop an object on the tile:
```bash
    -> Set OBJECT
    <- ok/ko
```

Incantation:
```bash
    -> Incantation
    <- Elevation underway/ko
    <- Current level: k/ko
```

If the command is not recognized:
```bash
    <- ko
```
