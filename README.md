# Magical band in C

### The story behind the homework

David has discovered a very interesting method for efficiently storing information using a magic band. He needs to perform various operations with this band while storing diverse data. The band can be considered indexed (initially having only one character, '#', at position 1). Each position can hold a single character (letters, digits, keyboard symbols). David enjoys inspecting the content of the band by tracing different values with his finger.

#### Operations

David can move his finger left, right, or directly to an element equal to a specific symbol on the band. Here are the operations he can perform:

- **Move Left:** David moves his finger to the left position on the band.
- **Move Right:** David moves his finger to the right position on the band.
- **Move to Symbol:** David moves his finger to the next occurrence of a specific symbol on the band.

### Implemented Functions:

#### MOVE_LEFT
- Moves the current position one cell to the left.
- If it's the first element in the list, remains in place.
- Adds the command to the EXECUTE queue.

#### MOVE_RIGHT
- Moves the current position one cell to the right.
- If the current position is the last, adds a new cell with '#' (effectively executes WRITE #).
- Adds the command to the EXECUTE queue.

#### MOVE_LEFT_CHAR <c>
- Searches for character `c` and stops when found, including the current position.
- Sets the current position to where character `c` is found.
- Returns an error if it reaches the first element without finding `c` and does not change the current position.
- Adds the command to the EXECUTE queue.

#### MOVE_RIGHT_CHAR <c>
- Searches for character `c` and stops when found, including the current position.
- Sets the current position to where character `c` is found.
- If it reaches the last element without finding `c`, adds a new cell with '#' and sets the current position to it.
- Adds the command to the EXECUTE queue.

#### WRITE <c>
- Writes character `c` at the current position.
- Adds the command to the EXECUTE queue.

#### INSERT_LEFT <c> (MOVE_LEFT + WRITE <c>)
- Inserts character `c` to the left (effectively adds a new character behind `c`).
- Moves the current position accordingly.
- Returns an error if at the first character and does not modify the current position.
- Adds the command to the EXECUTE queue.

#### INSERT_RIGHT <c> (MOVE_RIGHT + WRITE <c>)
- Inserts character `c` to the right (effectively adds a new character after `c`).
- Moves the current position accordingly.
- Does nothing if at the last cell in the list.
- Adds the command to the EXECUTE queue.

#### SHOW_CURRENT
- Executes immediately without adding to the EXECUTE queue.
- Displays the element at the current position.

#### SHOW
- Executes immediately without adding to the EXECUTE queue.
- Displays the entire content of the list with '|' indicating the current position.

#### UNDO
- Executes immediately without adding to the EXECUTE queue.
- Adjusts the finger position using a stack (no insertions).
- Pops the current finger position to the REDO stack.

#### REDO
- Executes immediately without adding to the EXECUTE queue.
- Pops the last finger position from the REDO stack.
