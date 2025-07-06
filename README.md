# chan_dongle_ng

`chan_dongle_ng` is a modernized Asterisk channel driver that allows GSM dongles (3G/4G USB modems) to be used for calls and SMS. It is an actively maintained fork intended to replace older "chan_dongle" implementations with a cleaner code base and improved reliability.

## Project Goals

The goal of this project is to provide an easy way to interface consumer USB modems with Asterisk. By handling voice and SMS functions over GSM, `chan_dongle_ng` lets you use inexpensive hardware as a trunk in your PBX.

## Prerequisites

- Asterisk development headers (tested with Asterisk 16+)
- `libusb-1.0` and its development files
- A C compiler (e.g., GCC) and standard build tools
- USB modem(s) that expose an AT command interface

Ubuntu/Debian users can install the prerequisites with:

```bash
sudo apt-get install build-essential libusb-1.0-0-dev asterisk asterisk-dev
```

## Building

This repository contains a standard Makefile. To build the module run:

```bash
make
```

After a successful build, install the module into your Asterisk modules directory with:

```bash
sudo make install
```

Reload or restart Asterisk so the new module is loaded.

## Basic Configuration

Edit or create `/etc/asterisk/dongle.conf` and define each connected modem. Example:

```ini
[general]
device=/dev/ttyUSB0

[usb0]
; audio and data ports are detected automatically
imei=123456789012345
imsi=123456789012345
``` 

Load the module by adding to `modules.conf`:

```ini
load => chan_dongle_ng.so
```

## Dialplan Example

Use the `Dongle/` technology in your dialplan to place or receive calls. A simple outgoing call example in `extensions.conf`:

```asterisk
[outgoing]
exten => _X.,1,Dial(Dongle/usb0/${EXTEN})
```

Incoming calls can be handled similarly:

```asterisk
[dongle-in]
exten => s,1,Answer()
 same => n,Dial(SIP/myphone)
```

## Further Reading

Refer to the comments in `dongle.conf` and `extensions.conf` for advanced options such as SMS handling, USSD, and audio settings. Additional documentation and support can be found in the project wiki.

