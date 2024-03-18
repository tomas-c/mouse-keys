# What is this?

A program written in C allows you to control the mouse using F13-F16 and F17-F20 keys. It was written to replace the mouse control logic that's running on the CharaChorder One.

The CharaChorder One has mouse switches for the left hand and the right hand. If you press the left mouse switch on the left side, then the mouse starts moving slowly to the left. If you then additionally press the left mouse switch on the right side, the mouse starts moving faster.

I found it frustrating that just tapping the second mouse switch would immediately cause the mouse to jump a large distance. Because the CharaChorder One is closed-source, I couldn't modify its source code. Instead, I remapped the left mouse buttons to F13-F16 and the right mouse buttons to F17-F20, and wrote this C program that I run on my Mac. It watches for key presses and starts moving the mouse in a similar way as the CharaChorder One itself would, but instead of making the mouse jump, it gradually ramps up the mouse speed.

# Warning

It's been a while since I had to write an C / C++ and this was hacked together very quickly. I didn't have time to clean it up or make sure it doesn't have any memory leaks.

# Compiling

```bash
mkdir -p ./build  && gcc -Wall -o ./build/main main.c -framework ApplicationServices
```

# Running

After compiling you can start it without any arguments

```bash
./build/main
```

# Permissions

The application needs the Accessibility permission. When executed from terminal, it may appear that the terminal itself is requeting Accessibility permission. 

If the permisison request dialog does not appear, permission can be givven from Settings > Privacy & Security > Accessiblity.

# Clash with brightness control

One of the F14 and F15 keys clashe with Mac brigtness controll shortcuts. Yoy may want to disable those from Settings -> Keyboard -> Keyboard Shortcuts > Display.

# Inspiration

https://github.com/caseyscarborough/keylogger

https://github.com/symless/synergy-core/blob/master/src/lib/platform/OSXScreen.mm