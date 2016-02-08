// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "context.h"

#include "grammar/ast/function/function.h"
#include "grammar/ast/function/prototype.h"
#include "grammar/ast/function/definition.h"
#include "grammar/ast/function/visitor.h"

#include "grammar/ast/operators/operator.h"
#include "grammar/ast/operators/block.h"
#include "grammar/ast/operators/calc.h"
#include "grammar/ast/operators/if.h"
#include "grammar/ast/operators/repeat.h"
#include "grammar/ast/operators/return.h"
#include "grammar/ast/operators/variable.h"
#include "grammar/ast/operators/while.h"
#include "grammar/ast/operators/nope.h"
#include "grammar/ast/operators/visitor.h"

#include "grammar/ast/operations/operation.h"
#include "grammar/ast/operations/binary.h"
#include "grammar/ast/operations/call.h"
#include "grammar/ast/operations/ternary.h"
#include "grammar/ast/operations/unary.h"
#include "grammar/ast/operations/variable.h"
#include "grammar/ast/operations/literal.h"
#include "grammar/ast/operations/visitor.h"

#include "grammar/ast/types/type.h"
#include "grammar/ast/types/name.h"
#include "grammar/ast/types/int.h"
#include "grammar/ast/types/tuple.h"
#include "grammar/ast/types/visitor.h"

#include "grammar/ast/module.h"
#include "grammar/ast/visitor.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/TargetRegistry.h>

class ast::visitor: public ast::module::visitor
{
	class type: public ast::type::visitor
	{
		llvm::LLVMContext& context;
		llvm::Type* result = nullptr;
	private:
		//type
		void visit(const ast::type::t_int& type) override {
			result = llvm::Type::getInt32Ty(context);
		}
		void visit(const ast::type::tuple& type) override {
		}
		void visit(const ast::type::name& type) override {
		}
	public:
		type(llvm::LLVMContext& context): context(context) {}
		llvm::Type* get(const ast::type::instance& instance) {
			instance->accept(*this);
			return result;
		}
	};

	class operation: public ast::operation::visitor
	{
		llvm::LLVMContext& context;
		llvm::BasicBlock& block;
		llvm::Value* result = nullptr;
	private:
		//operations
		void visit(const ast::operation::unary&) override {
		}
		void visit(const ast::operation::binary&) override {
		}
		void visit(const ast::operation::ternary&) override {
		}
		void visit(const ast::operation::variable&) override {
		}
		void visit(const ast::operation::call&) override {
		}
		void visit(const ast::operation::literal&) override {
		}
	public:
		operation(llvm::LLVMContext& context, llvm::BasicBlock& block): context(context), block(block) {}
		llvm::Value* insert(const ast::operation::instance& instance) {
			instance->accept(*this);
			return result;
		}
	};

	class instruction: public ast::instruction::visitor
	{
		llvm::LLVMContext& context;
		llvm::BasicBlock& block;
		llvm::Value* result = nullptr;
	private:
		//operators
		void visit(const ast::instruction::calc&) override {
		}
		void visit(const ast::instruction::if_i&) override {
		}
		void visit(const ast::instruction::ifelse_i&) override {
		}
		void visit(const ast::instruction::while_i&) override {
		}
		void visit(const ast::instruction::repeat_i&) override {
		}
		void visit(const ast::instruction::return_i&) override {
		}
		void visit(const ast::instruction::block& block) override {
			for(const auto& instruction: block.instructions) {
				insert(instruction);
			}
		}
		void visit(const ast::instruction::variable& variable) override {
			ast::visitor::type type(context);
			llvm::IRBuilder<> builder(&block);
			llvm::Value* var = builder.CreateAlloca(type.get(variable.type), nullptr, (const std::string&)variable.id);
			ast::visitor::operation operation(context, block);
			if(llvm::Value* value = operation.insert(variable.init)) {
				builder.CreateStore(var, value, false);
			}
		}
	public:
		instruction(llvm::LLVMContext& context, llvm::BasicBlock& block): context(context), block(block) {}
		llvm::Value* insert(const ast::instruction::instance& instance) {
			instance->accept(*this);
			return result;
		}
	};

	class function: public ast::function::visitor
	{
		llvm::LLVMContext& context;
		llvm::Module& module;
		llvm::Function* result = nullptr;
	private:
		//function
		void visit(const ast::function::prototype& prototype) override {
			ast::visitor::type type(context);

			std::vector<llvm::Type*> parameters_t;
			parameters_t.reserve(prototype.parameters.size());
			for(auto& parameter: prototype.parameters) {
				parameters_t.push_back(type.get(parameter.type));
			}
			llvm::FunctionType* function_t = llvm::FunctionType::get(type.get(prototype.returnType), parameters_t, false);
			llvm::Function* function = llvm::Function::Create(function_t, llvm::Function::ExternalLinkage, (const std::string&)prototype.name, &module);
			for(auto &arg : function->args()) {
				arg.setName((const std::string&)prototype.parameters[arg.getArgNo()].name);
			}
			result = function;
		}
		void visit(const ast::function::definition& definition) override {
			llvm::Function* function = this->get(definition.prototype);
			llvm::BasicBlock *block = llvm::BasicBlock::Create(context, "entry", function);
			ast::visitor::instruction instruction(context, *block);
			instruction.insert(definition.body);
		}
	public:
		function(llvm::LLVMContext& context, llvm::Module& module): context(context), module(module) {}
		llvm::Function* get(const ast::function::instance& instance) {
			instance->accept(*this);
			return result;
		}
	};

	llvm::LLVMContext& context;
	llvm::Module& module;
	llvm::IRBuilder<>& builder;
public:
	visitor(llvm::LLVMContext& context, llvm::Module& module, llvm::IRBuilder<>& builder): context(context), module(module), builder(builder) {}
public:
	//module
	void visit(const ast::function::instance& instance) override {
		ast::visitor::function function(context, module);
		function.get(instance);
	}
	void visit(const ast::type::instance& type) override {
		//ast::visitor::type visitor;
		//type->accept(visitor);
	}
};

#include <iostream>

void visit_all(ast::module m) {
	llvm::LLVMContext context;
	llvm::IRBuilder<> builder {context};
	llvm::Module module {"module", context};
	ast::visitor v{context, module, builder};
	m.accept(v);
	module.dump();
}
