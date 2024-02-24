X1coin
=============

Setup
---------------------
X1coin is the original X1coin client and it builds the backbone of the network. It downloads and, by default, stores the entire history of X1coin transactions, which requires a few hundred gigabytes of disk space. Depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download X1coin, visit [x1coincore.org](https://bitcoincore.org/en/download/).

Running
---------------------
The following are some helpful notes on how to run X1coin on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/x1coin-qt` (GUI) or
- `bin/x1coind` (headless)

### Windows

Unpack the files into a directory, and then run x1coin-qt.exe.

### macOS

Drag X1coin to your applications folder, and then run X1coin.

### Need Help?

* See the documentation at the [X1coin Wiki](https://en.x1coin.it/wiki/Main_Page)
for help and more information.
* Ask for help on [X1coin StackExchange](https://x1coin.stackexchange.com).
* Ask for help on #x1coin on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#x1coin).
* Ask for help on the [X1coinTalk](https://x1cointalk.org/) forums, in the [Technical Support board](https://x1cointalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build X1coin on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [Dependencies](dependencies.md)
- [macOS Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [FreeBSD Build Notes](build-freebsd.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [NetBSD Build Notes](build-netbsd.md)
- [Android Build Notes](build-android.md)

Development
---------------------
The X1coin repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Productivity Notes](productivity.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://doxygen.x1coincore.org/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [JSON-RPC Interface](JSON-RPC-interface.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)
- [Internal Design Docs](design/)

### Resources
* Discuss on the [X1coinTalk](https://x1cointalk.org/) forums, in the [Development & Technical Discussion board](https://x1cointalk.org/index.php?board=6.0).
* Discuss project-specific development on #x1coin-core-dev on Libera Chat. If you don't have an IRC client, you can use [web.libera.chat](https://web.libera.chat/#x1coin-core-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [x1coin.conf Configuration File](x1coin-conf.md)
- [CJDNS Support](cjdns.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [I2P Support](i2p.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [Managing Wallets](managing-wallets.md)
- [Multisig Tutorial](multisig-tutorial.md)
- [P2P bad ports definition and list](p2p-bad-ports.md)
- [PSBT support](psbt.md)
- [Reduce Memory](reduce-memory.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Transaction Relay Policy](policy/README.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
