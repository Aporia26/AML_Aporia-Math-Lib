#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

namespace AML_Test {
    // Basic test metadata storage
    struct TestInstance {
        std::string testSuite;
        std::string testName;
        void (*testFunc)();
    };

    // Central registry for self-contained test execution
    inline std::vector<TestInstance>& GetRegistry() {
        static std::vector<TestInstance> registry;
        return registry;
    }

    inline int& GetFailedCount() {
        static int failedCount = 0;
        return failedCount;
    }

    // Helper macro to register tests automatically before main runs
    struct TestRegistrar {
        TestRegistrar(const std::string& suite, const std::string& name, void (*func)()) {
            GetRegistry().push_back({suite, name, func});
        }
    };

    // Runner function executed inside main()
    inline int RunAllTests() {
        auto& registry = GetRegistry();
        int total = registry.size();
        int passed = 0;
        GetFailedCount() = 0;

        std::cout << "[====================] Running " << total << " tests...\n";

        for (const auto& test : registry) {
            std::cout << "[ RUN        ] " << test.testSuite << "." << test.testName << "\n";
            int beforeFailures = GetFailedCount();
            
            try {
                test.testFunc();
            } catch (const std::exception& e) {
                std::cout << "  ❌ Catastrophic crash: " << e.what() << "\n";
                GetFailedCount()++;
            } catch (...) {
                std::cout << "  ❌ Unknown exception thrown!\n";
                GetFailedCount()++;
            }

            if (GetFailedCount() == beforeFailures) {
                std::cout << "[       OK   ] " << test.testSuite << "." << test.testName << "\n";
                passed++;
            } else {
                std::cout << "[    FAILED  ] " << test.testSuite << "." << test.testName << "\n";
            }
        }

        std::cout << "[====================] Test Summary: " << passed << "/" << total << " passed.\n";
        return GetFailedCount() == 0 ? 0 : 1;
    }
}

// -------------------------------------------------------------------------
// TESTING MACROS
// -------------------------------------------------------------------------
#define AML_TEST(TestSuite, TestName) \
    void TestSuite##_##TestName##_Func(); \
    static AML_Test::TestRegistrar TestSuite##_##TestName##_Instance(#TestSuite, #TestName, TestSuite##_##TestName##_Func); \
    void TestSuite##_##TestName##_Func()

#define AML_EXPECT_EQ(val1, val2) \
    if ((val1) != (val2)) { \
        std::cout << "  ❌ Assertion Failed line " << __LINE__ << ": Expected (" << #val1 << " == " << #val2 << ") -> Got: [" << (val1) << " != " << (val2) << "]\n"; \
        AML_Test::GetFailedCount()++; \
    }

#define AML_EXPECT_NEAR(val1, val2, abs_error) \
    if (std::abs((val1) - (val2)) > (abs_error)) { \
        std::cout << "  ❌ Precision Error line " << __LINE__ << ": Expected " << #val1 << " (" << (val1) << ") to be within " << (abs_error) << " of " << #val2 << " (" << (val2) << ")\n"; \
        AML_Test::GetFailedCount()++; \
    }

#define AML_EXPECT_TRUE(condition) \
    if (!(condition)) { \
        std::cout << "  ❌ Boolean Error line " << __LINE__ << ": Expected (" << #condition << ") to be true\n"; \
        AML_Test::GetFailedCount()++; \
    }

#define AML_EXPECT_FALSE(condition) \
    if ((condition)) { \
        std::cout << "  ❌ Boolean Error line " << __LINE__ << ": Expected (" << #condition << ") to be false\n"; \
        AML_Test::GetFailedCount()++; \
    }
