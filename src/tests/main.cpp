#include <gtest/gtest.h>

using namespace testing;

int main(int argc, char* argv[])
{
    InitGoogleTest(&argc, argv);

    for (int idx = 1; idx < argc; ++idx)
    {
        if (std::strcmp(argv[idx], "--no-output") == 0)
        { // NOLINT
            auto& listeners = UnitTest::GetInstance()->listeners();
            delete listeners.Release(listeners.default_result_printer()); // NOLINT
            break;
        }
    }

    auto const res = RUN_ALL_TESTS();
    return res;
}