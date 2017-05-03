[![Build Status](https://travis-ci.org/bitprim/bitprim-explorer.svg?branch=master)](https://travis-ci.org/bitprim/bitprim-explorer)

*The automated build often fails on generating test metrics due to performance limits on Travis.*

# Bitprim Explorer

*The Bitcoin Command Line Tool*

**License Overview**

All files in this repository fall under the license specified in [COPYING](https://github.com/libbitcoin/libbitcoin-explorer/blob/version2/COPYING). The project is licensed as [AGPL with a lesser clause](https://wiki.unsystem.net/en/index.php/Libbitcoin/License). It may be used within a proprietary project, but the core library and any changes to it must be published on-line. Source code for this library must always remain free for everybody to access.

**About Bitprim**

The bitprim toolkit is a set of cross platform C++ libraries for building bitcoin applications. The toolkit consists of several libraries, most of which depend on the foundational [bitprim-core](https://github.com/bitprim/bitprim-core) library.

**About Bitprim Explorer**

BX is a command line tool for working with Bitcoin. It can be built as a single portable executable for Linux, OSX or Windows. BX exposes over 80 commands and supports network communication with [bitprim-server](https://github.com/bitprim/bitprim-server) or its predecessor [Obelisk](https://github.com/spesmilo/obelisk), and the P2P Bitcoin network. BX is well documented and supports simple and advanced scenarios, including stealth and multisig.

## Installation

Make sure you have installed [bitprim-core](https://github.com/bitprim/bitprim-core), [bitprim-network](https://github.com/bitprim/bitprim-network), [bitprim-protocol](https://github.com/bitprim/bitprim-protocol) and [bitprim-client](https://github.com/bitprim/bitprim-client) beforehand according to its build instructions.

```
$ git clone https://github.com/bitprim/bitprim-explorer.git
$ cd bitprim-explorer
$ mkdir build
$ cd build
$ cmake .. -DWITH_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++11" 
$ make -j2
$ sudo make install
```
