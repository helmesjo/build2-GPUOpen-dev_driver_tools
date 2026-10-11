# GPUOpen-dev_driver_tools - <SUMMARY>

This is a `build2` package repository for [`GPUOpen-dev_driver_tools`](https://<UPSTREAM-URL>),
a <SUMMARY-OF-FUNCTIONALITY>.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`GPUOpen-dev_driver_tools` in your `build2`-based project, then instead see the accompanying
[`PACKAGE-README.md`](<PACKAGE>/PACKAGE-README.md) file.

The development setup for `GPUOpen-dev_driver_tools` uses the standard `bdep`-based workflow.
For example:

```
git clone .../GPUOpen-dev_driver_tools.git
cd GPUOpen-dev_driver_tools

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
