# libdevdriverapi - AMD Developer Driver API (DevDriverAPI) C++ library

This is a `build2` package for the
[`dev_driver_tools`](https://github.com/GPUOpen-Tools/dev_driver_tools) C++
library. It provides the AMD Developer Driver API (DevDriverAPI) library,
which applications use to take Radeon GPU Profiler (RGP) profiles of
themselves with the AMD developer mode driver.


## Usage

To start using `libdevdriverapi` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libdevdriverapi ^1.7.0
```

Then import the library in your `buildfile`:

```
import libs = libdevdriverapi%lib{DevDriverAPI}
```


## Importable targets

This package provides the following importable targets:

```
lib{DevDriverAPI}
```

The DevDriverAPI library. Its interface is the `DevDriverAPI.h` header
(`#include <DevDriverAPI.h>`) of the `libdevdriverapi-headers` package, an
interface dependency of this library. The library exports a single
function, `DevDriverGetFuncTable()`, which fills in a table with the other
API functions (`DevDriverInit()`, `TriggerRgpProfile()`, etc), since
applications normally resolve it after loading the library at runtime. The
package version is the version of the upstream Developer Driver Tools
release (`1.7.0` is `V1.7`).

As in upstream, the shared library of a release is named
`DevDriverAPI-x64.dll` on 64-bit Windows and `libDevDriverAPI.so` on Linux,
the names under which applications load it at runtime. Unlike in upstream,
the Windows DLL does not embed a version information resource.

Only Linux and Windows are supported, as in upstream, and on Windows only
MSVC and Clang (not MinGW GCC). The RapidJSON and MetroHash libraries that upstream bundles are provided by
the `librapidjson` and `libmetrohash` packages, and the AMD Display Library
(ADL) headers that upstream fetches separately (used on Windows to query the
driver version) by the `libadl` package.


## Configuration variables

This package provides no configuration variables.
