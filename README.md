# GPUOpen-dev_driver_tools - AMD Developer Driver API (DevDriverAPI) C++ library

This is a `build2` package repository for
[`dev_driver_tools`](https://github.com/GPUOpen-Tools/dev_driver_tools),
the AMD Developer Driver Tools, whose Developer Driver API (DevDriverAPI)
library lets applications take Radeon GPU Profiler (RGP) profiles of
themselves with the AMD developer mode driver.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`libdevdriverapi` (the library) or `libdevdriverapi-headers` (its header
only) in your `build2`-based project, then instead see the accompanying
[`libdevdriverapi/PACKAGE-README.md`](libdevdriverapi/PACKAGE-README.md)
and
[`libdevdriverapi-headers/PACKAGE-README.md`](libdevdriverapi-headers/PACKAGE-README.md)
files.

The development setup for `GPUOpen-dev_driver_tools` uses the standard
`bdep`-based workflow. The library is only supported on Linux and Windows
(with MSVC or Clang). For example:

```
git clone .../GPUOpen-dev_driver_tools.git
cd GPUOpen-dev_driver_tools

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
