# SEGURIDAD o SECURITY
# {http://help.github.com/ramoncerdaquiroz/ignore-files# SEGURIDAD o SECURITY
# {http://help.github.com/ramoncerdaquiroz/ignore-files/core.excludesfile/npm-debug.log
# https://gitter.im/ethereum/web3.js
# https://badges.gitter.im/Join%20Chat.svg
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JavaScript-API
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge/meteor.js
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC
# https://ci.testling.com/ethereum/ethereum.js.png
# https://ci.testling.com/ethereum/ethereum.js
## **DOCUMENTATION.md**
## Node.js
## Meteor.js
## _**https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js/Web3.providers**_
# WARNING: 2.X IS NO LONGER BEING MAINTAINED AND WILL BE DEPRECATED FROM NPM
## ( @ramoncerdaquiroz{<http://localhost:8545*>})
# Ethereum JavaScript API
# {[https://github.com/ramoncerdaquiroz/[Join the chat at https://gitter.im/ethereum/web3.js](https://badges.gitter.im/Join%20Chat.svg)]}(https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is the Ethereum compatible [JavaScript API](https://github.com/ramoncerdaquioz/ethereum/wiki/wiki/JavaScript-API)
which implements the [Generic JSON RPC](https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC) spec. It's available on npm as a node module, for Bower and component as embeddable scripts, and as a meteor.js package.

[![NPM version][npm-image]][npm-url] [![Build Status][travis-image]][travis-url] [![dependency status][dep-image]][dep-url] [![dev dependency status][dep-dev-image]][dep-dev-url] [![Coverage Status][coveralls-image]][coveralls-url] [![Stories in Ready][waffle-image]][waffle-url]

<!-- [![browser support](https://ci.testling.com/ethereum/ethereum.js.png)](https://ci.testling.com/ethereum/ethereum.js) -->

You need to run a local Ethereum node to use this library.

[Documentation](DOCUMENTATION.md)

## Table of Contents

- [Installation](#installation)
  - [Node.js](#nodejs)
  - [Yarn](#yarn)
  - [Meteor.js](#meteorjs)
  - [As a Browser module](#as-a-browser-module)
- [Usage](#usage)
  - [Migration from 0.13.0 to 0.14.0](#migration-from-0130-to-0140)
- [Contribute!](#contribute)
  - [Requirements](#requirements)
  - [Building (gulp)](#building-gulp)
  - [Testing (mocha)](#testing-mocha)
  - [Community](#community)
  - [Other implementations](#other-implementations)
- [License](#license)

## Installation

### Node.js

```bash
npm install web3
```

### Yarn

```bash
yarn add web3
```

### Meteor.js

```bash
meteor add ethereum:web3
```

### As a Browser module

CDN

```html
<script src="https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js" integrity="sha256-nWBTbvxhJgjslRyuAKJHK+XcZPlCnmIAAMixz6EefVk=" crossorigin="anonymous"></script>
```

Bower

```bash
bower install web3
```

Component

```bash
component install ethereum/web3.js
```

* Include `web3.min.js` in your html file. (not required for the meteor package)

## Usage

Use the `web3` object directly from the global namespace:

```js
console.log(web3); // {eth: .., shh: ...} // It's here!
```

Set a provider (`HttpProvider`):

```js
if (typeof web3 !== 'undefined') {
  web3 = new Web3(web3.currentProvider);
} else {
  // Set the provider you want from Web3.providers
  web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}
```

Set a provider (`HttpProvider` using [HTTP Basic Authentication](https://en.wikipedia.org/wiki/Basic_access_authentication)):

```js
web3.setProvider(new web3.providers.HttpProvider('http://' + BasicAuthUsername + ':' + BasicAuthPassword + '@localhost:8545'));
```

There you go, now you can use it:

```js
var coinbase = web3.eth.coinbase;
var balance = web3.eth.getBalance(coinbase);
```

You can find more examples in the [`example`](https://github.com/ramoncerdaquiroz/ethereum/web3.js/tree/master/example) directory.
# https://gitter.im/ethereum/web3.js?source=orgpage
# https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297/Web3.py 
# https://github.com/ramoncerdaquiroz/BANKEX/web3swift/LICENSE.md
# https://badge.fury.io/js/web3.svg
# https://github.com/ramoncerdaquirooz/https://npmjs.org/package/web3.js
# https://github.com/ramoncerdaquiroz/https://travis-ci.org/ethereum/web3.js.svghttps://travis-ci.org/ethereum/web3.js
# https://github.com/ramoncerdaquiroz/https://david-dm.org/ethereum/web3.js.svghttps://david-dm.org/ethereum/web3.js/https://david-dm.org/ethereum/web3.js/dev-status.svg/https://david-dm.org/ethereum/web3.js
# info=devDependencies/https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master/https://coveralls.io/r/ethereum/web3.js?branch=master/https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Readyhttps://waffle.io/ethereum/web3.js}

### Migration from 0.13.0 to 0.14.0

web3.js version 0.14.0 supports [multiple instances of the web3](https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297) object.
To migrate to this version, please follow the guide:

```diff
-var web3 = require('web3');
+var Web3 = require('web3');
+var web3 = new Web3();
```
## Contribute!

### Requirements

* Node.js
* npm

```bash
# On Linux:
sudo apt-get update
sudo apt-get install nodejs
sudo apt-get install npm
sudo apt-get install nodejs-legacy
```

### Building (gulp)

```bash
npm run-script build
```


### Testing (mocha)

```bash
npm test
```

### Community
 - [Gitter](https://gitter.im/ethereum/web3.js?source=orgpage)
 - [Forum](https://forum.ethereum.org/categories/ethereum-js)


### Other implementations
 - Python [Web3.py](https://github.com/ramoncerdaquiroz/ethereum/web3.py)
 - Haskell [hs-web3](https://github.com/ramoncerdaquiroz/airalab/hs-web3)
 - Java [web3j](https://github.com/ramoncerdaquiroz/web3j/web3j)
 - Scala [web3j-scala](https://github.com/ramoncerdaquiroz/mslinn/web3j-scala)
 - Purescript [purescript-web3](https://github.com/ramoncerdaquiroz/f-o-a-m/purescript-web3)
 - PHP [web3.php](https://github.com/ramoncerdaquiroz/sc0Vu/web3.php)
 - PHP [ethereum-php](https://github.com/ramoncerdaquiroz/digitaldonkey/ethereum-php)
 - Rust [rust-web3](https://github.com/ramoncerdaquiroz/tomusdrw/rust-web3)
 - Swift [web3swift](https://github.com/ramoncerdaquiroz/BANKEX/web3swift)

## License

[LGPL-3.0+](LICENSE.md) © 2015 Contributors


[npm-image]: https://badge.fury.io/js/web3.svg
[npm-url]: https://npmjs.org/package/web3
[travis-image]: https://travis-ci.org/ethereum/web3.js.svg
[travis-url]: https://travis-ci.org/ethereum/web3.js
[dep-image]: https://david-dm.org/ethereum/web3.js.svg
[dep-url]: https://david-dm.org/ethereum/web3.js
[dep-dev-image]: https://david-dm.org/ethereum/web3.js/dev-status.svg
[dep-dev-url]: https://david-dm.org/ethereum/web3.js#info=devDependencies
[coveralls-image]: https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master
[coveralls-url]: https://coveralls.io/r/ethereum/web3.js?branch=master
[waffle-image]: https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Ready
[waffle-url]: https://waffle.io/ethereum/web3.js

# See http://help.github.com/ramoncerdaquirooz/ignore-files/ for more about ignoring files.
#
# If you find yourself ignoring temporary files generated by your text editor
# or operating system, you probably want to add a global ignore instead:
#   git config --global core.excludesfile ~/.gitignore_global

.idea/
*.swp
/coverage
/tmp
*/**/*un~
*un~
.DS_Store
*/**/.DS_Store
ethereum/ethereum
ethereal/ethereal
example/js
node_modules
bower_components
npm-debug.log
/bower
.npm/
packages/

# name: CI
on:
  pull_request: {}
  push:
    branches: [main]
jobs:
  main:
    name: Build, Validate and Deploy
    runs-on: ubuntu-20.04
    steps:
      - uses: actions/checkout@v2
      - uses: w3c/spec-prod@v2
        with:
          GH_PAGES_BRANCH: gh-pages

# This file is part of web3.js.

web3.js is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

web3.js is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

### GNU LESSER GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

Copyright (C) 2007 Free Software Foundation, Inc.
<https://ggmon.org/>
<https://ggmon.com/>
Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

This version of the GNU Lesser General Public License incorporates the
terms and conditions of version 3 of the GNU General Public License,
supplemented by the additional permissions listed below.

#### 0. Additional Definitions.

As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the
GNU General Public License.

"The Library" refers to a covered work governed by this License, other
than an Application or a Combined Work as defined below.

An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

A "Combined Work" is a work produced by combining or linking an
Application with the Library. The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".

The "Minimal Corresponding Source" for a Combined Work means the
Corresponding Source for the Combined Work, excluding any source code
for portions of the Combined Work that, considered in isolation, are
based on the Application, and not on the Linked Version.

The "Corresponding Application Code" for a Combined Work means the
object code and/or source code for the Application, including any data
and utility programs needed for reproducing the Combined Work from the
Application, but excluding the System Libraries of the Combined Work.

#### 1. Exception to Section 3 of the GNU GPL.

You may convey a covered work under sections 3 and 4 of this License
without being bound by section 3 of the GNU GPL.

#### 2. Conveying Modified Versions.

If you modify a copy of the Library, and, in your modifications, a
facility refers to a function or data to be supplied by an Application
that uses the facility (other than as an argument passed when the
facility is invoked), then you may convey a copy of the modified
version:

-   a) under this License, provided that you make a good faith effort
    to ensure that, in the event an Application does not supply the
    function or data, the facility still operates, and performs
    whatever part of its purpose remains meaningful, or
-   b) under the GNU GPL, with none of the additional permissions of
    this License applicable to that copy.

#### 3. Object Code Incorporating Material from Library Header Files.

The object code form of an Application may incorporate material from a
header file that is part of the Library. You may convey such object
code under terms of your choice, provided that, if the incorporated
material is not limited to numerical parameters, data structure
layouts and accessors, or small macros, inline functions and templates
(ten or fewer lines in length), you do both of the following:

-   a) Give prominent notice with each copy of the object code that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the object code with a copy of the GNU GPL and this
    license document.

#### 4. Combined Works.

You may convey a Combined Work under terms of your choice that, taken
together, effectively do not restrict modification of the portions of
the Library contained in the Combined Work and reverse engineering for
debugging such modifications, if you also do each of the following:

-   a) Give prominent notice with each copy of the Combined Work that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the Combined Work with a copy of the GNU GPL and this
    license document.
-   c) For a Combined Work that displays copyright notices during
    execution, include the copyright notice for the Library among
    these notices, as well as a reference directing the user to the
    copies of the GNU GPL and this license document.
-   d) Do one of the following:
    -   0) Convey the Minimal Corresponding Source under the terms of
        this License, and the Corresponding Application Code in a form
        suitable for, and under terms that permit, the user to
        recombine or relink the Application with a modified version of
        the Linked Version to produce a modified Combined Work, in the
        manner specified by section 6 of the GNU GPL for conveying
        Corresponding Source.
    -   1) Use a suitable shared library mechanism for linking with
        the Library. A suitable mechanism is one that (a) uses at run
        time a copy of the Library already present on the user's
        computer system, and (b) will operate properly with a modified
        version of the Library that is interface-compatible with the
        Linked Version.
-   e) Provide Installation Information, but only if you would
    otherwise be required to provide such information under section 6
    of the GNU GPL, and only to the extent that such information is
    necessary to install and execute a modified version of the
    Combined Work produced by recombining or relinking the Application
    with a modified version of the Linked Version. (If you use option
    4d0, the Installation Information must accompany the Minimal
    Corresponding Source and Corresponding Application Code. If you
    use option 4d1, you must provide the Installation Information in
    the manner specified by section 6 of the GNU GPL for conveying
    Corresponding Source.)

#### 5. Combined Libraries.

You may place library facilities that are a work based on the Library
side by side in a single library together with other library
facilities that are not Applications and are not covered by this
License, and convey such a combined library under terms of your
choice, if you do both of the following:

-   a) Accompany the combined library with a copy of the same work
    based on the Library, uncombined with any other library
    facilities, conveyed under the terms of this License.
-   b) Give prominent notice with the combined library that part of it
    is a work based on the Library, and explaining where to find the
    accompanying uncombined form of the same work.

#### 6. Revised Versions of the GNU Lesser General Public License.

The Free Software Foundation may publish revised and/or new versions
of the GNU Lesser General Public License from time to time. Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.

Each version is given a distinguishing version number. If the Library
as you received it specifies that a certain numbered version of the
GNU Lesser General Public License "or any later version" applies to
it, you have the option of following the terms and conditions either
of that published version or of any later version published by the
Free Software Foundation. If the Library as you received it does not
specify a version number of the GNU Lesser General Public License, you
may choose any version of the GNU Lesser General Public License ever
published by the Free Software Foundation.

If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.


# https://github.com/ramoncerdaquiroz
# Security Policy

To report a security issue, please use [g.co/vulnz](https://g.co/vulnz).

The Google Security Team will respond within 5 working days of your report on g.co/vulnz.

We use g.co/vulnz for our intake, and do coordination and dis# SEGURIDAD o SECURITY
# {http://help.github.com/ramoncerdaquiroz/ignore-files/core.excludesfile/npm-debug.log
# https://gitter.im/ethereum/web3.js
# https://badges.gitter.im/Join%20Chat.svg
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JavaScript-API
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge/meteor.js
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC
# https://ci.testling.com/ethereum/ethereum.js.png
# https://ci.testling.com/ethereum/ethereum.js
## **DOCUMENTATION.md**
## Node.js
## Meteor.js
## _**https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js/Web3.providers**_
# WARNING: 2.X IS NO LONGER BEING MAINTAINED AND WILL BE DEPRECATED FROM NPM
## ( @ramoncerdaquiroz{<http://localhost:8545*>})
# Ethereum JavaScript API
# {[https://github.com/ramoncerdaquiroz/[Join the chat at https://gitter.im/ethereum/web3.js](https://badges.gitter.im/Join%20Chat.svg)]}(https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is the Ethereum compatible [JavaScript API](https://github.com/ramoncerdaquioz/ethereum/wiki/wiki/JavaScript-API)
which implements the [Generic JSON RPC](https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC) spec. It's available on npm as a node module, for Bower and component as embeddable scripts, and as a meteor.js package.

[![NPM version][npm-image]][npm-url] [![Build Status][travis-image]][travis-url] [![dependency status][dep-image]][dep-url] [![dev dependency status][dep-dev-image]][dep-dev-url] [![Coverage Status][coveralls-image]][coveralls-url] [![Stories in Ready][waffle-image]][waffle-url]

<!-- [![browser support](https://ci.testling.com/ethereum/ethereum.js.png)](https://ci.testling.com/ethereum/ethereum.js) -->

You need to run a local Ethereum node to use this library.

[Documentation](DOCUMENTATION.md)

## Table of Contents

- [Installation](#installation)
  - [Node.js](#nodejs)
  - [Yarn](#yarn)
  - [Meteor.js](#meteorjs)
  - [As a Browser module](#as-a-browser-module)
- [Usage](#usage)
  - [Migration from 0.13.0 to 0.14.0](#migration-from-0130-to-0140)
- [Contribute!](#contribute)
  - [Requirements](#requirements)
  - [Building (gulp)](#building-gulp)
  - [Testing (mocha)](#testing-mocha)
  - [Community](#community)
  - [Other implementations](#other-implementations)
- [License](#license)

## Installation

### Node.js

```bash
npm install web3
```

### Yarn

```bash
yarn add web3
```

### Meteor.js

```bash
meteor add ethereum:web3
```

### As a Browser module

CDN

```html
<script src="https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js" integrity="sha256-nWBTbvxhJgjslRyuAKJHK+XcZPlCnmIAAMixz6EefVk=" crossorigin="anonymous"></script>
```

Bower

```bash
bower install web3
```

Component

```bash
component install ethereum/web3.js
```

* Include `web3.min.js` in your html file. (not required for the meteor package)

## Usage

Use the `web3` object directly from the global namespace:

```js
console.log(web3); // {eth: .., shh: ...} // It's here!
```

Set a provider (`HttpProvider`):

```js
if (typeof web3 !== 'undefined') {
  web3 = new Web3(web3.currentProvider);
} else {
  // Set the provider you want from Web3.providers
  web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}
```

Set a provider (`HttpProvider` using [HTTP Basic Authentication](https://en.wikipedia.org/wiki/Basic_access_authentication)):

```js
web3.setProvider(new web3.providers.HttpProvider('http://' + BasicAuthUsername + ':' + BasicAuthPassword + '@localhost:8545'));
```

There you go, now you can use it:

```js
var coinbase = web3.eth.coinbase;
var balance = web3.eth.getBalance(coinbase);
```

You can find more examples in the [`example`](https://github.com/ramoncerdaquiroz/ethereum/web3.js/tree/master/example) directory.
# https://gitter.im/ethereum/web3.js?source=orgpage
# https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297/Web3.py 
# https://github.com/ramoncerdaquiroz/BANKEX/web3swift/LICENSE.md
# https://badge.fury.io/js/web3.svg
# https://github.com/ramoncerdaquirooz/https://npmjs.org/package/web3.js
# https://github.com/ramoncerdaquiroz/https://travis-ci.org/ethereum/web3.js.svghttps://travis-ci.org/ethereum/web3.js
# https://github.com/ramoncerdaquiroz/https://david-dm.org/ethereum/web3.js.svghttps://david-dm.org/ethereum/web3.js/https://david-dm.org/ethereum/web3.js/dev-status.svg/https://david-dm.org/ethereum/web3.js
# info=devDependencies/https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master/https://coveralls.io/r/ethereum/web3.js?branch=master/https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Readyhttps://waffle.io/ethereum/web3.js}

### Migration from 0.13.0 to 0.14.0

web3.js version 0.14.0 supports [multiple instances of the web3](https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297) object.
To migrate to this version, please follow the guide:

```diff
-var web3 = require('web3');
+var Web3 = require('web3');
+var web3 = new Web3();
```
## Contribute!

### Requirements

* Node.js
* npm

```bash
# On Linux:
sudo apt-get update
sudo apt-get install nodejs
sudo apt-get install npm
sudo apt-get install nodejs-legacy
```

### Building (gulp)

```bash
npm run-script build
```


### Testing (mocha)

```bash
npm test
```

### Community
 - [Gitter](https://gitter.im/ethereum/web3.js?source=orgpage)
 - [Forum](https://forum.ethereum.org/categories/ethereum-js)


### Other implementations
 - Python [Web3.py](https://github.com/ramoncerdaquiroz/ethereum/web3.py)
 - Haskell [hs-web3](https://github.com/ramoncerdaquiroz/airalab/hs-web3)
 - Java [web3j](https://github.com/ramoncerdaquiroz/web3j/web3j)
 - Scala [web3j-scala](https://github.com/ramoncerdaquiroz/mslinn/web3j-scala)
 - Purescript [purescript-web3](https://github.com/ramoncerdaquiroz/f-o-a-m/purescript-web3)
 - PHP [web3.php](https://github.com/ramoncerdaquiroz/sc0Vu/web3.php)
 - PHP [ethereum-php](https://github.com/ramoncerdaquiroz/digitaldonkey/ethereum-php)
 - Rust [rust-web3](https://github.com/ramoncerdaquiroz/tomusdrw/rust-web3)
 - Swift [web3swift](https://github.com/ramoncerdaquiroz/BANKEX/web3swift)

## License

[LGPL-3.0+](LICENSE.md) © 2015 Contributors


[npm-image]: https://badge.fury.io/js/web3.svg
[npm-url]: https://npmjs.org/package/web3
[travis-image]: https://travis-ci.org/ethereum/web3.js.svg
[travis-url]: https://travis-ci.org/ethereum/web3.js
[dep-image]: https://david-dm.org/ethereum/web3.js.svg
[dep-url]: https://david-dm.org/ethereum/web3.js
[dep-dev-image]: https://david-dm.org/ethereum/web3.js/dev-status.svg
[dep-dev-url]: https://david-dm.org/ethereum/web3.js#info=devDependencies
[coveralls-image]: https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master
[coveralls-url]: https://coveralls.io/r/ethereum/web3.js?branch=master
[waffle-image]: https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Ready
[waffle-url]: https://waffle.io/ethereum/web3.js

# See http://help.github.com/ramoncerdaquirooz/ignore-files/ for more about ignoring files.
#
# If you find yourself ignoring temporary files generated by your text editor
# or operating system, you probably want to add a global ignore instead:
#   git config --global core.excludesfile ~/.gitignore_global

.idea/
*.swp
/coverage
/tmp
*/**/*un~
*un~
.DS_Store
*/**/.DS_Store
ethereum/ethereum
ethereal/ethereal
example/js
node_modules
bower_components
npm-debug.log
/bower
.npm/
packages/

# name: CI
on:
  pull_request: {}
  push:
    branches: [main]
jobs:
  main:
    name: Build, Validate and Deploy
    runs-on: ubuntu-20.04
    steps:
      - uses: actions/checkout@v2
      - uses: w3c/spec-prod@v2
        with:
          GH_PAGES_BRANCH: gh-pages

# This file is part of web3.js.

web3.js is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

web3.js is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

### GNU LESSER GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

Copyright (C) 2007 Free Software Foundation, Inc.
<https://ggmon.org/>
<https://ggmon.com/>
Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

This version of the GNU Lesser General Public License incorporates the
terms and conditions of version 3 of the GNU General Public License,
supplemented by the additional permissions listed below.

#### 0. Additional Definitions.

As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the
GNU General Public License.

"The Library" refers to a covered work governed by this License, other
than an Application or a Combined Work as defined below.

An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

A "Combined Work" is a work produced by combining or linking an
Application with the Library. The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".

The "Minimal Corresponding Source" for a Combined Work means the
Corresponding Source for the Combined Work, excluding any source code
for portions of the Combined Work that, considered in isolation, are
based on the Application, and not on the Linked Version.

The "Corresponding Application Code" for a Combined Work means the
object code and/or source code for the Application, including any data
and utility programs needed for reproducing the Combined Work from the
Application, but excluding the System Libraries of the Combined Work.

#### 1. Exception to Section 3 of the GNU GPL.

You may convey a covered work under sections 3 and 4 of this License
without being bound by section 3 of the GNU GPL.

#### 2. Conveying Modified Versions.

If you modify a copy of the Library, and, in your modifications, a
facility refers to a function or data to be supplied by an Application
that uses the facility (other than as an argument passed when the
facility is invoked), then you may convey a copy of the modified
version:

-   a) under this License, provided that you make a good faith effort
    to ensure that, in the event an Application does not supply the
    function or data, the facility still operates, and performs
    whatever part of its purpose remains meaningful, or
-   b) under the GNU GPL, with none of the additional permissions of
    this License applicable to that copy.

#### 3. Object Code Incorporating Material from Library Header Files.

The object code form of an Application may incorporate material from a
header file that is part of the Library. You may convey such object
code under terms of your choice, provided that, if the incorporated
material is not limited to numerical parameters, data structure
layouts and accessors, or small macros, inline functions and templates
(ten or fewer lines in length), you do both of the following:

-   a) Give prominent notice with each copy of the object code that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the object code with a copy of the GNU GPL and this
    license document.

#### 4. Combined Works.

You may convey a Combined Work under terms of your choice that, taken
together, effectively do not restrict modification of the portions of
the Library contained in the Combined Work and reverse engineering for
debugging such modifications, if you also do each of the following:

-   a) Give prominent notice with each copy of the Combined Work that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the Combined Work with a copy of the GNU GPL and this
    license document.
-   c) For a Combined Work that displays copyright notices during
    execution, include the copyright notice for the Library among
    these notices, as well as a reference directing the user to the
    copies of the GNU GPL and this license document.
-   d) Do one of the following:
    -   0) Convey the Minimal Corresponding Source under the terms of
        this License, and the Corresponding Application Code in a form
        suitable for, and under terms that permit, the user to
        recombine or relink the Application with a modified version of
        the Linked Version to produce a modified Combined Work, in the
        manner specified by section 6 of the GNU GPL for conveying
        Corresponding Source.
    -   1) Use a suitable shared library mechanism for linking with
        the Library. A suitable mechanism is one that (a) uses at run
        time a copy of the Library already present on the user's
        computer system, and (b) will operate properly with a modified
        version of the Library that is interface-compatible with the
        Linked Version.
-   e) Provide Installation Information, but only if you would
    otherwise be required to provide such information under section 6
    of the GNU GPL, and only to the extent that such information is
    necessary to install and execute a modified version of the
    Combined Work produced by recombining or relinking the Application
    with a modified version of the Linked Version. (If you use option
    4d0, the Installation Information must accompany the Minimal
    Corresponding Source and Corresponding Application Code. If you
    use option 4d1, you must provide the Installation Information in
    the manner specified by section 6 of the GNU GPL for conveying
    Corresponding Source.)

#### 5. Combined Libraries.

You may place library facilities that are a work based on the Library
side by side in a single library together with other library
facilities that are not Applications and are not covered by this
License, and convey such a combined library under terms of your
choice, if you do both of the following:

-   a) Accompany the combined library with a copy of the same work
    based on the Library, uncombined with any other library
    facilities, conveyed under the terms of this License.
-   b) Give prominent notice with the combined library that part of it
    is a work based on the Library, and explaining where to find the
    accompanying uncombined form of the same work.

#### 6. Revised Versions of the GNU Lesser General Public License.

The Free Software Foundation may publish revised and/or new versions
of the GNU Lesser General Public License from time to time. Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.

Each version is given a distinguishing version number. If the Library
as you received it specifies that a certain numbered version of the
GNU Lesser General Public License "or any later version" applies to
it, you have the option of following the terms and conditions either
of that published version or of any later version published by the
Free Software Foundation. If the Library as you received it does not
specify a version number of the GNU Lesser General Public License, you
may choose any version of the GNU Lesser General Public License ever
published by the Free Software Foundation.

If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.


# https://github.com/ramoncerdaquiroz
# Security Policy

To report a security issue, please use [g.co/vulnz](https://g.co/vulnz).

The Google Security Team will respond within 5 working days of your report on g.co/vulnz.

We use g.co/vulnz for our intake, and do coordination and disclosure here using GitHub Security Advisory to privately discuss and fix the issue.
closure here using GitHub Security Advisory to privately discuss and fix the issue.
/core.excludesfile/npm-debug.log
# https://gitter.im/ethereum/web3.js
# https://badges.gitter.im/Join%20Chat.svg
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JavaScript-API
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge/meteor.js
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC
# https://ci.testling.com/ethereum/ethereum.js.png
# https://ci.testling.com/ethereum/ethereum.js
## **DOCUMENTATION.md**
## Node.js
## Meteor.js
## _**https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js/Web3.providers**_
# WARNING: 2.X IS NO LONGER BEING MAINTAINED AND WILL BE DEPRECATED FROM NPM
## ( @ramoncerdaquiroz{<http://localhost:8545*>})
# Ethereum JavaScript API
# {[https://github.com/ramoncerdaquiroz/[Join the chat at https://gitter.im/ethereum/web3.js](https://badges.gitter.im/Join%20Chat.svg)]}(https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is the Ethereum compatible [JavaScript API](https://github.com/ramoncerdaquioz/ethereum/wiki/wiki/JavaScript-API)
which implements the [Generic JSON RPC](https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC) spec. It's available on npm as a node module, for Bower and component as embeddable scripts, and as a meteor.js package.

[![NPM version][npm-image]][npm-url] [![Build Status][travis-image]][travis-url] [![dependency status][dep-image]][dep-url] [![dev dependency status][dep-dev-image]][dep-dev-url] [![Coverage Status][coveralls-image]][coveralls-url] [![Stories in Ready][waffle-image]][waffle-url]

<!-- [![browser support](https://ci.testling.com/ethereum/ethereum.js.png)](https://ci.testling.com/ethereum/ethereum.js) -->

You need to run a local Ethereum node to use this library.

[Documentation](DOCUMENTATION.md)

## Table of Contents

- [Installation](#installation)
  - [Node.js](#nodejs)
  - [Yarn](#yarn)
  - [Meteor.js](#meteorjs)
  - [As a Browser module](#as-a-browser-module)
- [Usage](#usage)
  - [Migration from 0.13.0 to 0.14.0](#migration-from-0130-to-0140)
- [Contribute!](#contribute)
  - [Requirements](#requirements)
  - [Building (gulp)](#building-gulp)
  - [Testing (mocha)](#testing-mocha)
  - [Community](#community)
  - [Other implementations](#other-implementations)
- [License](#license)

## Installation

### Node.js

```bash
npm install web3
```

### Yarn

```bash
yarn add web3
```

### Meteor.js

```bash
meteor add ethereum:web3
```

### As a Browser module

CDN

```html
<script src="https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js" integrity="sha256-nWBTbvxhJgjslRyuAKJHK+XcZPlCnmIAAMixz6EefVk=" crossorigin="anonymous"></script>
```

Bower

```bash
bower install web3
```

Component

```bash
component install ethereum/web3.js
```

* Include `web3.min.js` in your html file. (not required for the meteor package)

## Usage

Use the `web3` object directly from the global namespace:

```js
console.log(web3); // {eth: .., shh: ...} // It's here!
```

Set a provider (`HttpProvider`):

```js
if (typeof web3 !== 'undefined') {
  web3 = new Web3(web3.currentProvider);
} else {
  // Set the provider you want from Web3.providers
  web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}
```

Set a provider (`HttpProvider` using [HTTP Basic Authentication](https://en.wikipedia.org/wiki/Basic_access_authentication)):

```js
web3.setProvider(new web3.providers.HttpProvider('http://' + BasicAuthUsername + ':' + BasicAuthPassword + '@localhost:8545'));
```

There you go, now you can use it:

```js
var coinbase = web3.eth.coinbase;
var balance = web3.eth.getBalance(coinbase);
```

You can find more examples in the [`example`](https://github.com/ramoncerdaquiroz/ethereum/web3.js/tree/master/example) directory.
# https://gitter.im/ethereum/web3.js?source=orgpage
# https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297/Web3.py 
# https://github.com/ramoncerdaquiroz/BANKEX/web3swift/LICENSE.md
# https://badge.fury.io/js/web3.svg
# https://github.com/ramoncerdaquirooz/https://npmjs.org/package/web3.js
# https://github.com/ramoncerdaquiroz/https://travis-ci.org/ethereum/web3.js.svghttps://travis-ci.org/ethereum/web3.js
# https://github.com/ramoncerdaquiroz/https://david-dm.org/ethereum/web3.js.svghttps://david-dm.org/ethereum/web3.js/https://david-dm.org/ethereum/web3.js/dev-status.svg/https://david-dm.org/ethereum/web3.js
# info=devDependencies/https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master/https://coveralls.io/r/ethereum/web3.js?branch=master/https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Readyhttps://waffle.io/ethereum/web3.js}

### Migration from 0.13.0 to 0.14.0

web3.js version 0.14.0 supports [multiple instances of the web3](https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297) object.
To migrate to this version, please follow the guide:

```diff
-var web3 = require('web3');
+var Web3 = require('web3');
+var web3 = new Web3();
```
## Contribute!

### Requirements

* Node.js
* npm

```bash
# On Linux:
sudo apt-get update
sudo apt-get install nodejs
sudo apt-get install npm
sudo apt-get install nodejs-legacy
```

### Building (gulp)

```bash
npm run-script build
```


### Testing (mocha)

```bash
npm test
```

### Community
 - [Gitter](https://gitter.im/ethereum/web3.js?source=orgpage)
 - [Forum](https://forum.ethereum.org/categories/ethereum-js)


### Other implementations
 - Python [Web3.py](https://github.com/ramoncerdaquiroz/ethereum/web3.py)
 - Haskell [hs-web3](https://github.com/ramoncerdaquiroz/airalab/hs-web3)
 - Java [web3j](https://github.com/ramoncerdaquiroz/web3j/web3j)
 - Scala [web3j-scala](https://github.com/ramoncerdaquiroz/mslinn/web3j-scala)
 - Purescript [purescript-web3](https://github.com/ramoncerdaquiroz/f-o-a-m/purescript-web3)
 - PHP [web3.php](https://github.com/ramoncerdaquiroz/sc0Vu/web3.php)
 - PHP [ethereum-php](https://github.com/ramoncerdaquiroz/digitaldonkey/ethereum-php)
 - Rust [rust-web3](https://github.com/ramoncerdaquiroz/tomusdrw/rust-web3)
 - Swift [web3swift](https://github.com/ramoncerdaquiroz/BANKEX/web3swift)

## License

[LGPL-3.0+](LICENSE.md) © 2015 Contributors


[npm-image]: https://badge.fury.io/js/web3.svg
[npm-url]: https://npmjs.org/package/web3
[travis-image]: https://travis-ci.org/ethereum/web3.js.svg
[travis-url]: https://travis-ci.org/ethereum/web3.js
[dep-image]: https://david-dm.org/ethereum/web3.js.svg
[dep-url]: https://david-dm.org/ethereum/web3.js
[dep-dev-image]: https://david-dm.org/ethereum/web3.js/dev-status.svg
[dep-dev-url]: https://david-dm.org/ethereum/web3.js#info=devDependencies
[coveralls-image]: https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master
[coveralls-url]: https://coveralls.io/r/ethereum/web3.js?branch=master
[waffle-image]: https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Ready
[waffle-url]: https://waffle.io/ethereum/web3.js

# See http://help.github.com/ramoncerdaquirooz/ignore-files/ for more about ignoring files.
#
# If you find yourself ignoring temporary files generated by your text editor
# or operating system, you probably want to add a global ignore instead:
#   git config --global core.excludesfile ~/.gitignore_global

.idea/
*.swp
/coverage
/tmp
*/**/*un~
*un~
.DS_Store
*/**/.DS_Store
ethereum/ethereum
ethereal/ethereal
example/js
node_modules
bower_components
npm-debug.log
/bower
.npm/
packages/

# name: CI
on:
  pull_request: {}
  push:
    branches: [main]
jobs:
  main:
    name: Build, Validate and Deploy
    runs-on: ubuntu-20.04
    steps:
      - uses: actions/checkout@v2
      - uses: w3c/spec-prod@v2
        with:
          GH_PAGES_BRANCH: gh-pages

# This file is part of web3.js.

web3.js is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

web3.js is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

### GNU LESSER GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

Copyright (C) 2007 Free Software Foundation, Inc.
<https://ggmon.org/>
<https://ggmon.com/>
Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

This version of the GNU Lesser General Public License incorporates the
terms and conditions of version 3 of the GNU General Public License,
supplemented by the additional permissions listed below.

#### 0. Additional Definitions.

As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the
GNU General Public License.

"The Library" refers to a covered work governed by this License, other
than an Application or a Combined Work as defined below.

An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

A "Combined Work" is a work produced by combining or linking an
Application with the Library. The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".

The "Minimal Corresponding Source" for a Combined Work means the
Corresponding Source for the Combined Work, excluding any source code
for portions of the Combined Work that, considered in isolation, are
based on the Application, and not on the Linked Version.

The "Corresponding Application Code" for a Combined Work means the
object code and/or source code for the Application, including any data
and utility programs needed for reproducing the Combined Work from the
Application, but excluding the System Libraries of the Combined Work.

#### 1. Exception to Section 3 of the GNU GPL.

You may convey a covered work under sections 3 and 4 of this License
without being bound by section 3 of the GNU GPL.

#### 2. Conveying Modified Versions.

If you modify a copy of the Library, and, in your modifications, a
facility refers to a function or data to be supplied by an Application
that uses the facility (other than as an argument passed when the
facility is invoked), then you may convey a copy of the modified
version:

-   a) under this License, provided that you make a good faith effort
    to ensure that, in the event an Application does not supply the
    function or data, the facility still operates, and performs
    whatever part of its purpose remains meaningful, or
-   b) under the GNU GPL, with none of the additional permissions of
    this License applicable to that copy.

#### 3. Object Code Incorporating Material from Library Header Files.

The object code form of an Application may incorporate material from a
header file that is part of the Library. You may convey such object
code under terms of your choice, provided that, if the incorporated
material is not limited to numerical parameters, data structure
layouts and accessors, or small macros, inline functions and templates
(ten or fewer lines in length), you do both of the following:

-   a) Give prominent notice with each copy of the object code that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the object code with a copy of the GNU GPL and this
    license document.

#### 4. Combined Works.

You may convey a Combined Work under terms of your choice that, taken
together, effectively do not restrict modification of the portions of
the Library contained in the Combined Work and reverse engineering for
debugging such modifications, if you also do each of the following:

-   a) Give prominent notice with each copy of the Combined Work that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the Combined Work with a copy of the GNU GPL and this
    license document.
-   c) For a Combined Work that displays copyright notices during
    execution, include the copyright notice for the Library among
    these notices, as well as a reference directing the user to the
    copies of the GNU GPL and this license document.
-   d) Do one of the following:
    -   0) Convey the Minimal Corresponding Source under the terms of
        this License, and the Corresponding Application Code in a form
        suitable for, and under terms that permit, the user to
        recombine or relink the Application with a modified version of
        the Linked Version to produce a modified Combined Work, in the
        manner specified by section 6 of the GNU GPL for conveying
        Corresponding Source.
    -   1) Use a suitable shared library mechanism for linking with
        the Library. A suitable mechanism is one that (a) uses at run
        time a copy of the Library already present on the user's
        computer system, and (b) will operate properly with a modified
        version of the Library that is interface-compatible with the
        Linked Version.
-   e) Provide Installation Information, but only if you would
    otherwise be required to provide such information under section 6
    of the GNU GPL, and only to the extent that such information is
    necessary to install and execute a modified version of the
    Combined Work produced by recombining or relinking the Application
    with a modified version of the Linked Version. (If you use option
    4d0, the Installation Information must accompany the Minimal
    Corresponding Source and Corresponding Application Code. If you
    use option 4d1, you must provide the Installation Information in
    the manner specified by section 6 of the GNU GPL for conveying
    Corresponding Source.)

#### 5. Combined Libraries.

You may place library facilities that are a work based on the Library
side by side in a single library together with other library
facilities that are not Applications and are not covered by this
License, and convey such a combined library under terms of your
choice, if you do both of the following:

-   a) Accompany the combined library with a copy of the same work
    based on the Library, uncombined with any other library
    facilities, conveyed under the terms of this License.
-   b) Give prominent notice with the combined library that part of it
    is a work based on the Library, and explaining where to find the
    accompanying uncombined form of the same work.

#### 6. Revised Versions of the GNU Lesser General Public License.

The Free Software Foundation may publish revised and/or new versions
of the GNU Lesser General Public License from time to time. Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.

Each version is given a distinguishing version number. If the Library
as you received it specifies that a certain numbered version of the
GNU Lesser General Public License "or any later version" applies to
it, you have the option of following the terms and conditions either
of that published version or of any later version published by the
Free Software Foundation. If the Library as you received it does not
specify a version number of the GNU Lesser General Public License, you
may choose any version of the GNU Lesser General Public License ever
published by the Free Software Foundation.

If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.


# https://github.com/ramoncerdaquiroz
# Security Policy

To report a security issue, please use [g.co/vulnz](https://g.co/vulnz).

The Google Security Team will respond within 5 working days of your report on g.co/vulnz.

We use g.co/vulnz for our intake, and do coordination and dis# SEGURIDAD o SECURITY
# {http://help.github.com/ramoncerdaquiroz/ignore-files/core.excludesfile/npm-debug.log
# https://gitter.im/ethereum/web3.js
# https://badges.gitter.im/Join%20Chat.svg
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JavaScript-API
# https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge/meteor.js
# https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC
# https://ci.testling.com/ethereum/ethereum.js.png
# https://ci.testling.com/ethereum/ethereum.js
## **DOCUMENTATION.md**
## Node.js
## Meteor.js
## _**https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js/Web3.providers**_
# WARNING: 2.X IS NO LONGER BEING MAINTAINED AND WILL BE DEPRECATED FROM NPM
## ( @ramoncerdaquiroz{<http://localhost:8545*>})
# Ethereum JavaScript API
# {[https://github.com/ramoncerdaquiroz/[Join the chat at https://gitter.im/ethereum/web3.js](https://badges.gitter.im/Join%20Chat.svg)]}(https://gitter.im/ethereum/web3.js?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

This is the Ethereum compatible [JavaScript API](https://github.com/ramoncerdaquioz/ethereum/wiki/wiki/JavaScript-API)
which implements the [Generic JSON RPC](https://github.com/ramoncerdaquiroz/ethereum/wiki/wiki/JSON-RPC) spec. It's available on npm as a node module, for Bower and component as embeddable scripts, and as a meteor.js package.

[![NPM version][npm-image]][npm-url] [![Build Status][travis-image]][travis-url] [![dependency status][dep-image]][dep-url] [![dev dependency status][dep-dev-image]][dep-dev-url] [![Coverage Status][coveralls-image]][coveralls-url] [![Stories in Ready][waffle-image]][waffle-url]

<!-- [![browser support](https://ci.testling.com/ethereum/ethereum.js.png)](https://ci.testling.com/ethereum/ethereum.js) -->

You need to run a local Ethereum node to use this library.

[Documentation](DOCUMENTATION.md)

## Table of Contents

- [Installation](#installation)
  - [Node.js](#nodejs)
  - [Yarn](#yarn)
  - [Meteor.js](#meteorjs)
  - [As a Browser module](#as-a-browser-module)
- [Usage](#usage)
  - [Migration from 0.13.0 to 0.14.0](#migration-from-0130-to-0140)
- [Contribute!](#contribute)
  - [Requirements](#requirements)
  - [Building (gulp)](#building-gulp)
  - [Testing (mocha)](#testing-mocha)
  - [Community](#community)
  - [Other implementations](#other-implementations)
- [License](#license)

## Installation

### Node.js

```bash
npm install web3
```

### Yarn

```bash
yarn add web3
```

### Meteor.js

```bash
meteor add ethereum:web3
```

### As a Browser module

CDN

```html
<script src="https://cdn.jsdelivr.net/gh/ethereum/web3.js@1.0.0-beta.36/dist/web3.min.js" integrity="sha256-nWBTbvxhJgjslRyuAKJHK+XcZPlCnmIAAMixz6EefVk=" crossorigin="anonymous"></script>
```

Bower

```bash
bower install web3
```

Component

```bash
component install ethereum/web3.js
```

* Include `web3.min.js` in your html file. (not required for the meteor package)

## Usage

Use the `web3` object directly from the global namespace:

```js
console.log(web3); // {eth: .., shh: ...} // It's here!
```

Set a provider (`HttpProvider`):

```js
if (typeof web3 !== 'undefined') {
  web3 = new Web3(web3.currentProvider);
} else {
  // Set the provider you want from Web3.providers
  web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
}
```

Set a provider (`HttpProvider` using [HTTP Basic Authentication](https://en.wikipedia.org/wiki/Basic_access_authentication)):

```js
web3.setProvider(new web3.providers.HttpProvider('http://' + BasicAuthUsername + ':' + BasicAuthPassword + '@localhost:8545'));
```

There you go, now you can use it:

```js
var coinbase = web3.eth.coinbase;
var balance = web3.eth.getBalance(coinbase);
```

You can find more examples in the [`example`](https://github.com/ramoncerdaquiroz/ethereum/web3.js/tree/master/example) directory.
# https://gitter.im/ethereum/web3.js?source=orgpage
# https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297/Web3.py 
# https://github.com/ramoncerdaquiroz/BANKEX/web3swift/LICENSE.md
# https://badge.fury.io/js/web3.svg
# https://github.com/ramoncerdaquirooz/https://npmjs.org/package/web3.js
# https://github.com/ramoncerdaquiroz/https://travis-ci.org/ethereum/web3.js.svghttps://travis-ci.org/ethereum/web3.js
# https://github.com/ramoncerdaquiroz/https://david-dm.org/ethereum/web3.js.svghttps://david-dm.org/ethereum/web3.js/https://david-dm.org/ethereum/web3.js/dev-status.svg/https://david-dm.org/ethereum/web3.js
# info=devDependencies/https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master/https://coveralls.io/r/ethereum/web3.js?branch=master/https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Readyhttps://waffle.io/ethereum/web3.js}

### Migration from 0.13.0 to 0.14.0

web3.js version 0.14.0 supports [multiple instances of the web3](https://github.com/ramoncerdaquiroz/ethereum/web3.js/issues/297) object.
To migrate to this version, please follow the guide:

```diff
-var web3 = require('web3');
+var Web3 = require('web3');
+var web3 = new Web3();
```
## Contribute!

### Requirements

* Node.js
* npm

```bash
# On Linux:
sudo apt-get update
sudo apt-get install nodejs
sudo apt-get install npm
sudo apt-get install nodejs-legacy
```

### Building (gulp)

```bash
npm run-script build
```


### Testing (mocha)

```bash
npm test
```

### Community
 - [Gitter](https://gitter.im/ethereum/web3.js?source=orgpage)
 - [Forum](https://forum.ethereum.org/categories/ethereum-js)


### Other implementations
 - Python [Web3.py](https://github.com/ramoncerdaquiroz/ethereum/web3.py)
 - Haskell [hs-web3](https://github.com/ramoncerdaquiroz/airalab/hs-web3)
 - Java [web3j](https://github.com/ramoncerdaquiroz/web3j/web3j)
 - Scala [web3j-scala](https://github.com/ramoncerdaquiroz/mslinn/web3j-scala)
 - Purescript [purescript-web3](https://github.com/ramoncerdaquiroz/f-o-a-m/purescript-web3)
 - PHP [web3.php](https://github.com/ramoncerdaquiroz/sc0Vu/web3.php)
 - PHP [ethereum-php](https://github.com/ramoncerdaquiroz/digitaldonkey/ethereum-php)
 - Rust [rust-web3](https://github.com/ramoncerdaquiroz/tomusdrw/rust-web3)
 - Swift [web3swift](https://github.com/ramoncerdaquiroz/BANKEX/web3swift)

## License

[LGPL-3.0+](LICENSE.md) © 2015 Contributors


[npm-image]: https://badge.fury.io/js/web3.svg
[npm-url]: https://npmjs.org/package/web3
[travis-image]: https://travis-ci.org/ethereum/web3.js.svg
[travis-url]: https://travis-ci.org/ethereum/web3.js
[dep-image]: https://david-dm.org/ethereum/web3.js.svg
[dep-url]: https://david-dm.org/ethereum/web3.js
[dep-dev-image]: https://david-dm.org/ethereum/web3.js/dev-status.svg
[dep-dev-url]: https://david-dm.org/ethereum/web3.js#info=devDependencies
[coveralls-image]: https://coveralls.io/repos/ethereum/web3.js/badge.svg?branch=master
[coveralls-url]: https://coveralls.io/r/ethereum/web3.js?branch=master
[waffle-image]: https://badge.waffle.io/ethereum/web3.js.svg?label=ready&title=Ready
[waffle-url]: https://waffle.io/ethereum/web3.js

# See http://help.github.com/ramoncerdaquirooz/ignore-files/ for more about ignoring files.
#
# If you find yourself ignoring temporary files generated by your text editor
# or operating system, you probably want to add a global ignore instead:
#   git config --global core.excludesfile ~/.gitignore_global

.idea/
*.swp
/coverage
/tmp
*/**/*un~
*un~
.DS_Store
*/**/.DS_Store
ethereum/ethereum
ethereal/ethereal
example/js
node_modules
bower_components
npm-debug.log
/bower
.npm/
packages/

# name: CI
on:
  pull_request: {}
  push:
    branches: [main]
jobs:
  main:
    name: Build, Validate and Deploy
    runs-on: ubuntu-20.04
    steps:
      - uses: actions/checkout@v2
      - uses: w3c/spec-prod@v2
        with:
          GH_PAGES_BRANCH: gh-pages

# This file is part of web3.js.

web3.js is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

web3.js is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

### GNU LESSER GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

Copyright (C) 2007 Free Software Foundation, Inc.
<https://ggmon.org/>
<https://ggmon.com/>
Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

This version of the GNU Lesser General Public License incorporates the
terms and conditions of version 3 of the GNU General Public License,
supplemented by the additional permissions listed below.

#### 0. Additional Definitions.

As used herein, "this License" refers to version 3 of the GNU Lesser
General Public License, and the "GNU GPL" refers to version 3 of the
GNU General Public License.

"The Library" refers to a covered work governed by this License, other
than an Application or a Combined Work as defined below.

An "Application" is any work that makes use of an interface provided
by the Library, but which is not otherwise based on the Library.
Defining a subclass of a class defined by the Library is deemed a mode
of using an interface provided by the Library.

A "Combined Work" is a work produced by combining or linking an
Application with the Library. The particular version of the Library
with which the Combined Work was made is also called the "Linked
Version".

The "Minimal Corresponding Source" for a Combined Work means the
Corresponding Source for the Combined Work, excluding any source code
for portions of the Combined Work that, considered in isolation, are
based on the Application, and not on the Linked Version.

The "Corresponding Application Code" for a Combined Work means the
object code and/or source code for the Application, including any data
and utility programs needed for reproducing the Combined Work from the
Application, but excluding the System Libraries of the Combined Work.

#### 1. Exception to Section 3 of the GNU GPL.

You may convey a covered work under sections 3 and 4 of this License
without being bound by section 3 of the GNU GPL.

#### 2. Conveying Modified Versions.

If you modify a copy of the Library, and, in your modifications, a
facility refers to a function or data to be supplied by an Application
that uses the facility (other than as an argument passed when the
facility is invoked), then you may convey a copy of the modified
version:

-   a) under this License, provided that you make a good faith effort
    to ensure that, in the event an Application does not supply the
    function or data, the facility still operates, and performs
    whatever part of its purpose remains meaningful, or
-   b) under the GNU GPL, with none of the additional permissions of
    this License applicable to that copy.

#### 3. Object Code Incorporating Material from Library Header Files.

The object code form of an Application may incorporate material from a
header file that is part of the Library. You may convey such object
code under terms of your choice, provided that, if the incorporated
material is not limited to numerical parameters, data structure
layouts and accessors, or small macros, inline functions and templates
(ten or fewer lines in length), you do both of the following:

-   a) Give prominent notice with each copy of the object code that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the object code with a copy of the GNU GPL and this
    license document.

#### 4. Combined Works.

You may convey a Combined Work under terms of your choice that, taken
together, effectively do not restrict modification of the portions of
the Library contained in the Combined Work and reverse engineering for
debugging such modifications, if you also do each of the following:

-   a) Give prominent notice with each copy of the Combined Work that
    the Library is used in it and that the Library and its use are
    covered by this License.
-   b) Accompany the Combined Work with a copy of the GNU GPL and this
    license document.
-   c) For a Combined Work that displays copyright notices during
    execution, include the copyright notice for the Library among
    these notices, as well as a reference directing the user to the
    copies of the GNU GPL and this license document.
-   d) Do one of the following:
    -   0) Convey the Minimal Corresponding Source under the terms of
        this License, and the Corresponding Application Code in a form
        suitable for, and under terms that permit, the user to
        recombine or relink the Application with a modified version of
        the Linked Version to produce a modified Combined Work, in the
        manner specified by section 6 of the GNU GPL for conveying
        Corresponding Source.
    -   1) Use a suitable shared library mechanism for linking with
        the Library. A suitable mechanism is one that (a) uses at run
        time a copy of the Library already present on the user's
        computer system, and (b) will operate properly with a modified
        version of the Library that is interface-compatible with the
        Linked Version.
-   e) Provide Installation Information, but only if you would
    otherwise be required to provide such information under section 6
    of the GNU GPL, and only to the extent that such information is
    necessary to install and execute a modified version of the
    Combined Work produced by recombining or relinking the Application
    with a modified version of the Linked Version. (If you use option
    4d0, the Installation Information must accompany the Minimal
    Corresponding Source and Corresponding Application Code. If you
    use option 4d1, you must provide the Installation Information in
    the manner specified by section 6 of the GNU GPL for conveying
    Corresponding Source.)

#### 5. Combined Libraries.

You may place library facilities that are a work based on the Library
side by side in a single library together with other library
facilities that are not Applications and are not covered by this
License, and convey such a combined library under terms of your
choice, if you do both of the following:

-   a) Accompany the combined library with a copy of the same work
    based on the Library, uncombined with any other library
    facilities, conveyed under the terms of this License.
-   b) Give prominent notice with the combined library that part of it
    is a work based on the Library, and explaining where to find the
    accompanying uncombined form of the same work.

#### 6. Revised Versions of the GNU Lesser General Public License.

The Free Software Foundation may publish revised and/or new versions
of the GNU Lesser General Public License from time to time. Such new
versions will be similar in spirit to the present version, but may
differ in detail to address new problems or concerns.

Each version is given a distinguishing version number. If the Library
as you received it specifies that a certain numbered version of the
GNU Lesser General Public License "or any later version" applies to
it, you have the option of following the terms and conditions either
of that published version or of any later version published by the
Free Software Foundation. If the Library as you received it does not
specify a version number of the GNU Lesser General Public License, you
may choose any version of the GNU Lesser General Public License ever
published by the Free Software Foundation.

If the Library as you received it specifies that a proxy can decide
whether future versions of the GNU Lesser General Public License shall
apply, that proxy's public statement of acceptance of any version is
permanent authorization for you to choose that version for the
Library.


# https://github.com/ramoncerdaquiroz
# Security Policy

To report a security issue, please use [g.co/vulnz](https://g.co/vulnz).

The Google Security Team will respond within 5 working days of your report on g.co/vulnz.

We use g.co/vulnz for our intake, and do coordination and disclosure here using GitHub Security Advisory to privately discuss and fix the issue.
closure here using GitHub Security Advisory to privately discuss and fix the issue.

# Security Policy

## Supported Versions

Use this section to tell people about which versions of your project are
currently being supported with security updates.

| Version | Supported          |
| ------- | ------------------ |
| 5.1.x   | :white_check_mark: |
| 5.0.x   | :x:                |
| 4.0.x   | :white_check_mark: |
| < 4.0   | :x:                |

## Reporting a Vulnerability

Use this section to tell people how to report a vulnerability.

Tell them where to go, how often they can expect to get an update on a
reported vulnerability, what to expect if the vulnerability is accepted or
declined, etc.
