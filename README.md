# C-Racer
Essential race game in C.

# Build
(Raylib is needed)

Linux   : Execute "build.sh"
Windows : ```gcc src/*.c -o course.exe -lraylib -lm -Ofast```

# TODO
- User interface system
- User interface :
```
      - Pause menu
           - Controls menu
               - Change control buttons
               - Back button
           - Network menu
               - Host button
               - Join menu
                   - IP text field
                   - Port text field
                   - Connect button
                   - Cancel button
               - Back button
           - Quit button
           - Resume button
```
- Fix DrawCircuitView()
- Network
