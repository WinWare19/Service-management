# Service-management
- This is a simple console application i built for managing both user mode services and driver services, it includes many features, you can use it to register/Unregister both types, controlling their states and changing their configuration information ( executable, display name, type, start type ...etc ).
- It can be used to load kernel drivers also by starting a registered driver service, howerver testsigning option must be enabled, use this command to set it to on : BCDEdit /set testsigning on and reboot your system if required.
