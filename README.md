# vest backend

This is the core repository for the Moduex App backend

*This is a wip project and some aspects may be broken at times*

-----------------------------

Eventually I hope to support:
 * C++ Lib
 * Unity
 * Unreal

# features

- Bluetooth | 
Low latency BLE system using SimpleBLE to reduce complexity

- Websockets | 
Websockets to communicate between the eventual library and the app, allows for asset streaming and commands

- Storage and Parsing | 
Storage for haptic files ".mod" that will be loaded into a hash map on boot and parsed on demand.
