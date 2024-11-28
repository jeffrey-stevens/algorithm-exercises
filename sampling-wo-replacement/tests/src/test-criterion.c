#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>


Test(misc, failing, .description = "Forcing a failure...") {
    cr_assert(false, "Forced failure.");
}

Test(misc, passing) {
    cr_assert(true, "Forced pass.");
}