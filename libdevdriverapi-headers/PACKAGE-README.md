# libdevdriverapi-headers - AMD Developer Driver API (DevDriverAPI) C++ header

This is a `build2` package for the
[`dev_driver_tools`](https://github.com/GPUOpen-Tools/dev_driver_tools) C++
library. It provides the header of the AMD Developer Driver API
(DevDriverAPI), which applications use to take Radeon GPU Profiler (RGP)
profiles of themselves with the AMD developer mode driver.


## Usage

To start using `libdevdriverapi-headers` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libdevdriverapi-headers ^1.7.0
```

Then import the library in your `buildfile`:

```
import libs = libdevdriverapi-headers%lib{devdriverapi-headers}
```


## Importable targets

This package provides the following importable targets:

```
lib{devdriverapi-headers}
```

The DevDriverAPI header, included without a subdirectory prefix
(`#include <DevDriverAPI.h>`), as in the upstream releases. The header
requires C++ (one of its function pointer types has reference parameters).
The package version is the version of the upstream Developer Driver Tools
release (`1.7.0` is `V1.7`).

This package is headers only and supports all platforms. As in upstream,
applications load the DevDriverAPI library at runtime (`DevDriverAPI-x64.dll`
on 64-bit Windows and `libDevDriverAPI.so` on Linux), resolve its
`DevDriverGetFuncTable()` function, and call the functions of the table that
it fills in. The library itself is provided by the `libdevdriverapi`
package.


## Configuration variables

This package provides no configuration variables.
