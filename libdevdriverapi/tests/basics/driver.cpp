#include <cstddef>
#include <cstdint>

#include <DevDriverAPI.h>

#undef NDEBUG
#include <cassert>

int main ()
{
  // Invalid function table requests.
  //
  {
    assert (DevDriverGetFuncTable (nullptr) == DEV_DRIVER_STATUS_NULL_POINTER);

    DevDriverAPI t {};
    t.majorVersion = DEV_DRIVER_API_MAJOR_VERSION + 1;
    assert (DevDriverGetFuncTable (&t) ==
            DEV_DRIVER_STATUS_INVALID_MAJOR_VERSION);
  }

  // Function table. Without a developer mode driver the context cannot be
  // initialized, so only check that the functions reject a null context.
  //
  {
    DevDriverAPI t {};
    t.majorVersion = DEV_DRIVER_API_MAJOR_VERSION;
    t.minorVersion = DEV_DRIVER_API_MINOR_VERSION;

    assert (DevDriverGetFuncTable (&t) == DEV_DRIVER_STATUS_SUCCESS);
    assert (t.majorVersion == DEV_DRIVER_API_MAJOR_VERSION);
    assert (t.minorVersion == DEV_DRIVER_API_MINOR_VERSION);

    assert (t.DevDriverInit        != nullptr &&
            t.DevDriverFinish      != nullptr &&
            t.TriggerRgpProfile    != nullptr &&
            t.IsRgpProfileCaptured != nullptr &&
            t.GetRgpProfileName    != nullptr &&
            t.GetDriverVersion     != nullptr &&
            t.GetFullDriverVersion != nullptr);

    RGPProfileOptions o {};
    const char* n (nullptr);
    unsigned int ma (0), mi (0), sm (0);

    assert (t.DevDriverFinish (nullptr) == DEV_DRIVER_STATUS_NULL_POINTER);

    assert (t.TriggerRgpProfile (nullptr, &o) ==
            DEV_DRIVER_STATUS_NULL_POINTER);

    assert (t.IsRgpProfileCaptured (nullptr) ==
            DEV_DRIVER_STATUS_NULL_POINTER);

    assert (t.GetRgpProfileName (nullptr, &n) ==
            DEV_DRIVER_STATUS_NULL_POINTER && n == nullptr);

    assert (t.GetDriverVersion (nullptr, ma, mi) ==
            DEV_DRIVER_STATUS_NULL_POINTER);

    assert (t.GetFullDriverVersion (nullptr, &ma, &mi, &sm) ==
            DEV_DRIVER_STATUS_NULL_POINTER);
  }

  // Clients built against an older version (with a smaller table) only get
  // the functions their table has room for.
  //
  {
    const uint32_t v (offsetof (DevDriverAPI, TriggerRgpProfile));

    DevDriverAPI t {};
    t.majorVersion = DEV_DRIVER_API_MAJOR_VERSION;
    t.minorVersion = v;

    assert (DevDriverGetFuncTable (&t) == DEV_DRIVER_STATUS_SUCCESS);
    assert (t.minorVersion == v);
    assert (t.DevDriverFinish != nullptr && t.TriggerRgpProfile == nullptr);
  }
}
