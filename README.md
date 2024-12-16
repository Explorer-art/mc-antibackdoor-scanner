# MC AntiBackdoor Scanner
MC AntiBackdoor Scanner is a tool for scanning plugins for servers in Minecraft for backdoors. The plugin is analyzed for the presence of methods from the file signatures.txt . Each method found adds 1 level of danger. If the level is too high (for example >2), then there may be a backdoor in the plugin.

### WARNING!
This is only a prototype scanner, it has many flaws and can give false positives and false negative results. In order to be sure of the reliability of the plugin, you need to independently check its code through the decompiler.

### Build
```
make
```

### Usage
Scanning a singe plugin:
```
./mc-scanner [plugin jar]
```

Scanning multiple plugins
```
./mc-scanner [plugin jar 1] [plugin jar 2] [plugin jar 3]
```