#include "llvm/Transforms/Scalar/Skeleton.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "skeleton"

using namespace llvm;

PreservedAnalyses SkeletonPass::run(Function &F, FunctionAnalysisManager &FAM) {
  LLVM_DEBUG(dbgs() << "I saw a function called " << F.getName() << "!\n");

  // TODO 1: Dump all instructions in F
  // TODO 2: Dump only the calls in F
  // TODO 3: Dump only calls to the "fib" function with constant parameters
  // TODO 4: Replace constant calls to fib with the result

  // Inform the pass manager which analyses are still valid after our pass.
  // Since we're not changing anything yet, we can say we preserve everything.
  return PreservedAnalyses::all();
}

bool SkeletonPass::isFibFunction(Function *F) const {
  auto *FTy = F->getFunctionType();

  return F->getName() == "fib" && FTy->getNumParams() == 1 &&
         FTy->getReturnType()->isIntegerTy(32) &&
         FTy->getParamType(0)->isIntegerTy(32);
}

int SkeletonPass::fib(int n) {
  // Precomputed Fibonacci numbers F0 up to F46. This implementation assumes
  // that the size n of the input array fits in 4 bytes. Note that
  // F46=1836311903 is the largest Fibonacci number that is less or equal to the
  // 4-byte INT_MAX (=2147483647). The next Fibonacci number, i.e. F47, is
  // 2971215073 and is larger than INT_MAX, implying that it does not fit in a 4
  // byte integer.
  const static int Fib[] = {
      0,         1,         1,         2,          3,         5,
      8,         13,        21,        34,         55,        89,
      144,       233,       377,       610,        987,       1597,
      2584,      4181,      6765,      10946,      17711,     28657,
      46368,     75025,     121393,    196418,     317811,    514229,
      832040,    1346269,   2178309,   3524578,    5702887,   9227465,
      14930352,  24157817,  39088169,  63245986,   102334155, 165580141,
      267914296, 433494437, 701408733, 1134903170, 1836311903};
  const int max = sizeof(Fib) / sizeof(*Fib);

  if (n <= 0)
    return 0;

  if (n >= max)
    return INT_MAX;

  return Fib[n];
}
