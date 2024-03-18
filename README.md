# Compiling

```bash
mkdir ./build -p && gcc -Wall -o ./build/main main.c -framework ApplicationServices
```

# Permissions

The application needs access Accessibility permission. If run from terminal, it will appear that the terminal itself is requeting Accessibility permission.

Permission can be givven from Settings > Privacy & Security > Accessiblity

# Inspiration

https://github.com/caseyscarborough/keylogger
https://github.com/symless/synergy-core/blob/master/src/lib/platform/OSXScreen.mm