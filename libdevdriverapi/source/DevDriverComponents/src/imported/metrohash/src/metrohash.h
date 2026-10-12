// Compatibility shim: redirect to the packaged MetroHash header. It declares
// the hash classes in the global namespace while the bundled copy declares
// them in Util.
//
#pragma once

#include <metrohash/metrohash.h>

namespace Util
{
  using ::MetroHash64;
  using ::MetroHash128;
}
