# MC AntiBackdoor Scanner
MC AntiBackdoor Scanner is a tool for scanning plugins for servers in Minecraft for backdoors. The plugin is analyzed for the presence of methods from the file signatures.txt . Each method found adds 1 level of danger. If the level is too high (for example >2), then there may be a backdoor in the plugin.

### Build
```
make
```

### Usage
```
./mc-scanner [plugin jar]
```