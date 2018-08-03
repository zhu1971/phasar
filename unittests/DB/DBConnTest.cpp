#include <gtest/gtest.h>
#include <phasar/DB/DBConn.h>
#include <phasar/DB/ProjectIRDB.h>

using namespace std;
using namespace psr;

class DBConnTest : public ::testing::Test {
protected:
  const std::string pathToLLFiles =
      PhasarDirectory + "build/test/llvm_test_code/";
};

TEST_F(DBConnTest, HandleLTHStoreWithMultipleProjects) {
  ProjectIRDB firstIRDB({pathToLLFiles + "module_wise/module_wise_13/src1.ll",
                         pathToLLFiles + "module_wise/module_wise_13/src2.ll",
                         pathToLLFiles + "module_wise/module_wise_13/main.ll"});
  ProjectIRDB secondIRDB(
      {pathToLLFiles + "module_wise/module_wise_14/src1.ll",
       pathToLLFiles + "module_wise/module_wise_14/src2.ll",
       pathToLLFiles + "module_wise/module_wise_14/main.ll"});

  DBConn &db = DBConn::getInstance();
  LLVMTypeHierarchy TH1(firstIRDB);
  LLVMTypeHierarchy TH2(secondIRDB);
  std::cout << "\n\n";
  TH1.print();
  std::cout << "\n\n";
  TH2.print();
  db.storeProjectIRDB("first_project", firstIRDB);
  db.storeProjectIRDB("second_project", secondIRDB);
}

// TEST_F(DBConnTest, HandleLTHWriteToHex) {
//   ProjectIRDB IRDB({pathToLLFiles + "module_wise/module_wise_9/src1.ll",
//                     pathToLLFiles + "module_wise/module_wise_9/src2.ll",
//                     pathToLLFiles + "module_wise/module_wise_9/src3.ll"});
//   DBConn &db = DBConn::getInstance();
//   db.storeProjectIRDB("phasardbtest", IRDB);
//   LLVMTypeHierarchy TH(IRDB);
//   std::cout << "\n\n";
//   TH.print();
//   std::cout << '\n';
//   db.storeLLVMTypeHierarchy(TH, "phasardbtest", true);
// }

TEST_F(DBConnTest, HandleLTHWriteToDot) {
  ProjectIRDB IRDB({pathToLLFiles + "module_wise/module_wise_9/src1.ll",
                    pathToLLFiles + "module_wise/module_wise_9/src2.ll",
                    pathToLLFiles + "module_wise/module_wise_9/src3.ll"});
  DBConn &db = DBConn::getInstance();
  db.storeProjectIRDB("phasardbtest", IRDB);
  LLVMTypeHierarchy TH(IRDB);
  std::cout << '\n';
  TH.print();
  std::cout << '\n';
  db.storeLLVMTypeHierarchy(TH, "phasardbtest", false);
}

TEST_F(DBConnTest, StoreProjectIRDBTest) {
  ProjectIRDB IRDB({pathToLLFiles + "module_wise/module_wise_9/src1.ll",
                    pathToLLFiles + "module_wise/module_wise_9/src2.ll",
                    pathToLLFiles + "module_wise/module_wise_9/src3.ll"});
  DBConn &db = DBConn::getInstance();
  db.storeProjectIRDB("phasardbtest", IRDB);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
