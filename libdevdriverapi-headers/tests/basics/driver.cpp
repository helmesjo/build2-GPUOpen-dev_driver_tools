#include <cstdint>
#include <type_traits>

#include <DevDriverAPI.h>

#undef NDEBUG
#include <cassert>

// Stand-in for the library DevDriverGetFuncTable() function that the
// application obtains by name after loading the library.
//
static DevDriverStatus DEV_DRIVER_API_CALL
get_func_table (void* p)
{
  if (p == nullptr)
    return DEV_DRIVER_STATUS_NULL_POINTER;

  DevDriverAPI* t (static_cast<DevDriverAPI*> (p));

  if (t->majorVersion != DEV_DRIVER_API_MAJOR_VERSION)
    return DEV_DRIVER_STATUS_INVALID_MAJOR_VERSION;

  *t = DevDriverAPI {};
  t->majorVersion = DEV_DRIVER_API_MAJOR_VERSION;
  t->minorVersion = DEV_DRIVER_API_MINOR_VERSION;
  return DEV_DRIVER_STATUS_SUCCESS;
}

int main ()
{
  using namespace std;

  // Version.
  //
  {
    assert (DEV_DRIVER_API_MAJOR_VERSION == 1);
    assert (DEV_DRIVER_API_MINOR_VERSION == sizeof (DevDriverAPI));
  }

  // Status codes.
  //
  {
    assert (DEV_DRIVER_STATUS_SUCCESS == 0);
    assert (DEV_DRIVER_STATUS_INVALID_PARAMETERS < DEV_DRIVER_STATUS_ERROR);
  }

  // Features.
  //
  {
    DevDriverFeatures fs[] = {
      {DEV_DRIVER_FEATURE_ENABLE_RGP, sizeof (DevDriverFeatureRGP), {}}};

    assert (fs[0].m_option == DEV_DRIVER_FEATURE_ENABLE_RGP);
    assert (fs[0].m_size == sizeof (fs[0].m_featureRGP));
  }

  // Function table.
  //
  {
    using get_func_table_fn = DevDriverStatus (DEV_DRIVER_API_CALL*) (void*);

    static_assert (
      is_same<decltype (&DevDriverGetFuncTable), get_func_table_fn>::value,
      "unexpected DevDriverGetFuncTable() type");

    static_assert (
      is_same<DevDriverFnInit,
              DevDriverStatus (DEV_DRIVER_API_CALL*) (const DevDriverFeatures[],
                                                      uint32_t,
                                                      DevDriverAPIContext*)>::value,
      "unexpected DevDriverFnInit type");

    get_func_table_fn f (&get_func_table);

    DevDriverAPI t {};
    assert (f (nullptr) == DEV_DRIVER_STATUS_NULL_POINTER);
    assert (f (&t) == DEV_DRIVER_STATUS_INVALID_MAJOR_VERSION);

    t.majorVersion = DEV_DRIVER_API_MAJOR_VERSION;
    assert (f (&t) == DEV_DRIVER_STATUS_SUCCESS);
    assert (t.minorVersion == DEV_DRIVER_API_MINOR_VERSION);
    assert (t.DevDriverInit == nullptr);
  }
}
