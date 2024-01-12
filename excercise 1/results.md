3. variable sharing
When running increment and decrement tasks simultaniously the global variable, i, ends up with a different value each time the program is ran. This is due to both threads trying to edit the memory at the same time, and since the scheduler wont make the each routine run the same time every time they will essentially randomly overwrite eachothers work as its not synchronized or handled in any way.

