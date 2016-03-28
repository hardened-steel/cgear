// Project: CGear
//
//  Created on: 31.10.2015
//      Author: K.Pinegin
//       email: keldgaden@gmail.com
//

#include "context.h"

#include "ast/function/function.h"
#include "ast/function/prototype.h"
#include "ast/function/definition.h"
#include "ast/function/visitor.h"

#include "ast/operators/operator.h"
#include "ast/operators/block.h"
#include "ast/operators/calc.h"
#include "ast/operators/if.h"
//#include "grammar/ast/operators/repeat.h"
#include "ast/operators/return.h"
#include "ast/operators/variable.h"
#include "ast/operators/while.h"
#include "ast/operators/nope.h"
#include "ast/operators/visitor.h"

#include "ast/operations/operation.h"
#include "ast/operations/binary.h"
#include "ast/operations/call.h"
//#include "grammar/ast/operations/ternary.h"
//#include "grammar/ast/operations/unary.h"
#include "ast/operations/variable.h"
#include "ast/operations/literal.h"
#include "ast/operations/visitor.h"

#include "ast/types/type.h"
//#include "grammar/ast/types/name.h"
#include "ast/types/int.h"
//#include "grammar/ast/types/tuple.h"
#include "ast/types/visitor.h"

#include "ast/module.h"
#include "ast/visitor.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/TargetRegistry.h>

#include "type.h"

/*
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
		void visit(const ast::operation::binary&) override {
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
			llvm::Value* var = builder.CreateAlloca(type.get(variable.type), nullptr, variable.id.get());
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
			llvm::Function* function = llvm::Function::Create(function_t, llvm::Function::ExternalLinkage, prototype.name.get(), &module);
			for(auto &arg : function->args()) {
				arg.setName(prototype.parameters[arg.getArgNo()].name.get());
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
*/

class generator
{
public:
	class context;
	class type;
	class value;
	class expression;
	class instruction;
};

class generator::value
{
public:
	using instance = instance_t<generator::value>;
	virtual generator::type& get_type() const = 0;
	virtual ~value() {}
};

class generator::expression: public generator::value
{
public:
	using instance = instance_t<generator::expression>;
	virtual generator::value::instance& get_value(const generator::value::instance& parameters) const = 0;
};

class generator::instruction
{
public:
	using instance = instance_t<generator::instruction>;
	virtual void get_code() = 0;
	virtual ~instruction() {}
};

class generator::type
{
public:
	using instance = instance_t<generator::type>;
	std::multimap<ast::operation::code, generator::expression::instance> operations;
	std::multimap<token::identifier, generator::expression::instance> methods;
};

class generator::context
{
public:
	std::map<token::identifier, generator::type::instance> names;
};

class ast::visitor: public ast::module::visitor
{
	generator::context context;

	class type: public ast::type::visitor
	{
		generator::context& context;
	private:
		//type
		void visit(const ast::type::t_int& type) override {
			class binary_plus: public generator::expression
			{
			public:
				using instance = instance_t<binary_plus>;
				generator::value::instance& get_value(const generator::value::instance& parameters) const override {

				}
			};
			generator::type::instance int_type;
		}
	public:
		type(generator::context& context): context(context) {}
	};

	class operation: public ast::operation::visitor
	{
		generator::context& context;
	private:
		//operations
		void visit(const ast::operation::binary&) override {
		}
		void visit(const ast::operation::variable&) override {
		}
		void visit(const ast::operation::call& operation) override {
		}
		void visit(const ast::operation::literal&) override {
		}
	public:
		operation(generator::context& context): context(context) {}
	};

	class instruction: public ast::instruction::visitor
	{
		generator::context& context;
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
		void visit(const ast::instruction::return_i&) override {
		}
		void visit(const ast::instruction::block& block) override {
		}
		void visit(const ast::instruction::variable& variable) override {
		}
	public:
		instruction(generator::context& context): context(context) {}
		void process(const ast::instruction::instance& instance) {
			instance->accept(*this);
		}
	};

	class function: public ast::function::visitor
	{
		generator::context& context;
	private:
		//function
		void visit(const ast::function::prototype& prototype) override {
			//const std::string& name = prototype.name.get();
		}
		void visit(const ast::function::definition& definition) override {
			class fparameter: public generator::value
			{
			public:

			};
			generator::context context;
			for(auto& parameter: definition.prototype->parameters) {
			}
			instruction instr(context);
			instr.process(definition.body);
		}
	public:
		function(generator::context& context): context(context) {}
		void codegen(const ast::function::instance& instance) {
			instance->accept(*this);
		}
	};

public:
	visitor() {}
public:
	//module
	void visit(const ast::function::instance& instance) override {
		ast::visitor::function function(context);
		function.codegen(instance);
	}
	void visit(const ast::type::instance& type) override {
		//ast::visitor::type visitor;
		//type->accept(visitor);
	}
};

void visit_all(ast::module m) {
	ast::visitor v;
	m.accept(v);
}
