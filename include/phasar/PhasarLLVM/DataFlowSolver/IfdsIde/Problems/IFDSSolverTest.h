/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

#ifndef PHASAR_PHASARLLVM_IFDSIDE_PROBLEMS_IFDSSOLVERTEST_H_
#define PHASAR_PHASARLLVM_IFDSIDE_PROBLEMS_IFDSSOLVERTEST_H_

#include <initializer_list>
#include <map>
#include <memory>
#include <set>
#include <string>

#include <phasar/PhasarLLVM/DataFlowSolver/IfdsIde/IFDSTabulationProblem.h>

namespace llvm {
class Instruction;
class Function;
class Value;
} // namespace llvm

namespace psr {

class LLVMBasedICFG;

class IFDSSolverTest
    : public IFDSTabulationProblem<const llvm::Instruction *,
                                   const llvm::Value *, const llvm::Function *,
                                   LLVMBasedICFG> {
public:
  typedef const llvm::Value *d_t;
  typedef const llvm::Instruction *n_t;
  typedef const llvm::Function *m_t;

  IFDSSolverTest(const ProjectIRDB *IRDB, const TypeHierarchy *TH,
                const LLVMBasedICFG *ICF, const PointsToInfo *PT,
                std::initializer_list<std::string> EntryPoints = {"main"});

  ~IFDSSolverTest() override = default;

  std::shared_ptr<FlowFunction<d_t>> getNormalFlowFunction(n_t curr,
                                                           n_t succ) override;

  std::shared_ptr<FlowFunction<d_t>> getCallFlowFunction(n_t callStmt,
                                                         m_t destMthd) override;

  std::shared_ptr<FlowFunction<d_t>> getRetFlowFunction(n_t callSite,
                                                        m_t calleeMthd,
                                                        n_t exitStmt,
                                                        n_t retSite) override;

  std::shared_ptr<FlowFunction<d_t>>
  getCallToRetFlowFunction(n_t callSite, n_t retSite,
                           std::set<m_t> callees) override;

  std::shared_ptr<FlowFunction<d_t>>
  getSummaryFlowFunction(n_t callStmt, m_t destMthd) override;

  std::map<n_t, std::set<d_t>> initialSeeds() override;

  d_t createZeroValue() const override;

  bool isZeroValue(d_t d) const override;

  void printNode(std::ostream &os, n_t n) const override;

  void printDataFlowFact(std::ostream &os, d_t d) const override;

  void printMethod(std::ostream &os, m_t m) const override;
};

} // namespace psr

#endif
