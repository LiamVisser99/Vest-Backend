# vest backend

Work in Progress (WIP): This is an active development repository. Some features may be unstable or broken at times as core functionality is prioritised.

# Fetures

* Low-Latency Bluetooth (BLE): Uses the SimpleBLE stack alongside support for the Tp-Link UB500 BLE dongle to maintian maximum efficiency, responsiveness, and small overhead.
* Low-Latency Websocket: Allows for asset streaming via the Moduex haptic library *coming soon* to store, hash, and trigger haptic files when starting a game.
* Dynamic Motor Mapping: Implements haptic files (".mod" files) to enable playback of custom haptic effects via a custom file parser and engine.
* File Storage: Implements full non-volatile file storage of haptic files that are parsed and hashed upon startup.

# Future Integrations

* Custom haptic library for C++
* Native Unity and Unreal Engine SDK integration
* Advanced directional pattern playback
* Haptic pattern studio to make custom patterns
