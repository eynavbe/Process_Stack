# Process_Stack
Include a stack server that implements multiple memory and multiple processes and lock routines
The code is written in c but the file name will be * .cpp.
To embed a cartridge using POSIX methods, your cartridge must contain a null string variable.
 - The commands requested from client- as input to server, the stack is in server-.
   - PUSH command - will push <Text> into the stack.
   - POP command - will bounce text from the stack.
   - TOP command - will display (output) the top of the cartridge. After sending TOP to the server will send to the client-output so that it starts with the OUTPUT prefix ":".
   - EXIT command - exits the server and client.
   - If a non-existent command is sent, it will be printed on the screen in the ERROR server ":" and the name of the command sent.
   - If there is a runtime error then send will be printed on the screen "DEBUG:" then place the error type.
 - that the server receives a number of clients that transmit the stack command,
 - Apply a lock now as you may receive a number of stack-to-stack commands on different connections. Using fcntl lock.
 - Implement new methods for maneuvering memory (malloc, free) in a multi-process environment. Use MAP_SHARED shared memory for malloc application.
 - Merge the server implemented in 4 with the components developed in section 5.
 - Implementing the Unix domain sockets (DGRAM) interface in addition to TCP sockets - located in the clientUnix.cpp and serverUnix.cpp files.
  
  
## Through the run:
### Option 1: Without using makefile:
Open terminal 2 (or more if you want more than one client) in Linux routed to the folder where the files are located.
2. In terminal 1: g ++ server.cpp -o s
3. In Terminal 1: ./s
4. In terminal 2: g ++ client.cpp -o c1
5. In Terminal 2: ./c1
6. In terminal 3 or higher: g ++ client.cpp -o c2
7. In terminal 3 or more: ./ c2

### Option 2: Using makefile:
Open terminal 2 in Linux routed to the folder where the files are located.
2. make all
In terminal 1: ./runS (runs the server-)
In Terminal 2: ./runC (running the client)

### Run the test.cpp test file:
1. Open a terminal in Linux routed to the folder where the files are located.
2. g ++ test.cpp -lpthread -o t
3. ./t

### Running the clientUnix.cpp and serverUnix.cpp bonus files:
Open terminal 2 (or more if you want more than one client) in Linux routed to the folder where the files are located.
2. In terminal 1: g ++ serverUnix.cpp -o s
3. In Terminal 1: ./s
4. In terminal 2: g ++ clientUnix.cpp -o c1
5. In Terminal 2: ./c1
6. In terminal 3 or higher: g ++ clientUnix.cpp -o c2
7. In terminal 3 or more: ./ c2
