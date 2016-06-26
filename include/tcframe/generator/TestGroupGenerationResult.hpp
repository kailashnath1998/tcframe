#pragma once

#include <vector>

#include "TestCaseGenerationResult.hpp"
#include "tcframe/failure.hpp"

using std::vector;

namespace tcframe {

struct TestGroupGenerationResult {
private:
    Failure* testGroupFailure_;
    vector<TestCaseGenerationResult> testCaseResults_;

public:
    TestGroupGenerationResult(
            Failure* testGroupFailure,
            const vector<TestCaseGenerationResult>& testCaseResults)
            : testGroupFailure_(testGroupFailure)
            , testCaseResults_(testCaseResults)
    {}

    Failure* testGroupFailure() const {
        return testGroupFailure_;
    }

    const vector<TestCaseGenerationResult>& testCaseResults() const {
        return testCaseResults_;
    }

    bool isSuccessful() const {
        if (testGroupFailure_ != nullptr) {
            return false;
        }
        for (auto testCaseResult : testCaseResults_) {
            if (!testCaseResult.isSuccessful()) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const TestGroupGenerationResult& o) const {
        if (testGroupFailure_ != o.testGroupFailure_) {
            return false;
        }
        if (testGroupFailure_ != nullptr && o.testGroupFailure_ != nullptr) {
            if (!testGroupFailure_->equals(o.testGroupFailure_)) {
                return false;
            }
        }
        return testCaseResults_ == o.testCaseResults_;
    }
};

}