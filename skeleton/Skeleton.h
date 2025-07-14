#include "llvm/IR/PassManager.h"

namespace llvm {
struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM);

private:
  // Check that the function is the 'fib' that we expect - i.e. that it has the
  // correct name and signature (takes an i32, returns an i32).
  bool isFibFunction(Function *F) const;

  // Returns the value of the \p n'th Fibonacci number.
  int fib(int n);
};
} // namespace llvm
