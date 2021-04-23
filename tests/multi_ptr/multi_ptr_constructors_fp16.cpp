/*******************************************************************************
//
//  SYCL 2020 Conformance Test Suite
//
//  Provide multi_ptr constructors' tests for fp16 types
//
*******************************************************************************/

#include "../common/common.h"
#include "multi_ptr_constructors_common.h"

#define TEST_NAME multi_ptr_constructors_fp16

namespace TEST_NAMESPACE {
using namespace multi_ptr_constructors_common;
using namespace sycl_cts;

/** tests the constructors for explicit pointers
 */
class TEST_NAME : public util::test_base {
 public:
  /** return information about this test
   */
  void get_info(test_base::info &out) const override {
    set_test_info(out, TOSTRING(TEST_NAME), TEST_FILE);
  }

  /** execute this test
   */
  void run(util::logger &log) override {
    try {
      auto queue = util::get_cts_object::queue();

      if (!queue.get_device().has_extension("cl_khr_fp16")) {
        log.note(
            "Device does not support half precision floating point operations");
        return;
      }

      pointer_ctors<half, void> halfVoidTests;
      halfVoidTests(queue);

      pointer_ctors<const half, const void> constHalfVoidTests;
      constHalfVoidTests(queue);

      pointer_ctors<half> halfTests;
      halfTests(queue);

      pointer_ctors<const half> constHalfTests;
      constHalfTests(queue);

      queue.wait_and_throw();
    } catch (const cl::sycl::exception &e) {
      log_exception(log, e);
      cl::sycl::string_class errorMsg =
          "a SYCL exception was caught: " + cl::sycl::string_class(e.what());
      FAIL(log, errorMsg.c_str());
    }
  }
};

// register this test with the test_collection
util::test_proxy<TEST_NAME> proxy;

} /* namespace TEST_NAMESPACE */
