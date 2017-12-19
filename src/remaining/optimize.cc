#include "optimize.hh"

/*** This file contains all code pertaining to AST optimisation. It currently
 implements a simple optimisation called "constant folding". Most of the
 methods in this file are empty, or just relay optimize calls downward
 in the AST. If a more powerful AST optimization scheme were to be
 implemented, only methods in this file should need to be changed. ***/

ast_optimizer *optimizer = new ast_optimizer();

/* The optimizer's interface method. Starts a recursive optimize call down
 the AST nodes, searching for binary operators with constant children. */
void ast_optimizer::do_optimize(ast_stmt_list *body) {
	if (body != NULL) {
		body->optimize();
	}
}

/* Returns 1 if an AST expression is a subclass of ast_binaryoperation,
 ie, eligible for constant folding. */
bool ast_optimizer::is_binop(ast_expression *node) {
	switch (node->tag) {
	case AST_ADD:
	case AST_SUB:
	case AST_OR:
	case AST_AND:
	case AST_MULT:
	case AST_DIVIDE:
	case AST_IDIV:
	case AST_MOD:
		return true;
	default:
		return false;
	}
}

/* We overload this method for the various ast_node subclasses that can
 appear in the AST. By use of virtual (dynamic) methods, we ensure that
 the correct method is invoked even if the pointers in the AST refer to
 one of the abstract classes such as ast_expression or ast_statement. */
void ast_node::optimize() {
	fatal("Trying to optimize abstract class ast_node.");
}

void ast_statement::optimize() {
	fatal("Trying to optimize abstract class ast_statement.");
}

void ast_expression::optimize() {
	fatal("Trying to optimize abstract class ast_expression.");
}

void ast_lvalue::optimize() {
	fatal("Trying to optimize abstract class ast_lvalue.");
}

void ast_binaryoperation::optimize() {
	fatal("Trying to optimize abstract class ast_binaryoperation.");
}

void ast_binaryrelation::optimize() {
	fatal("Trying to optimize abstract class ast_binaryrelation.");
}

/*** The optimize methods for the concrete AST classes. ***/

/* Optimize a statement list. */
void ast_stmt_list::optimize() {
	if (preceding != NULL) {
		preceding->optimize();
	}
	if (last_stmt != NULL) {
		last_stmt->optimize();
	}
}

/* Optimize a list of expressions. */
void ast_expr_list::optimize() {
	//simple recursive optimization
	if (preceding != NULL) {
		preceding->optimize();
	}
	if (optimizer->is_binop(last_expr)) {
		last_expr = optimizer->fold_constants(last_expr);
	}
}

/* Optimize an elsif list. */
void ast_elsif_list::optimize() {
	//more or less same as expression optimization
	if (preceding != NULL) {
		preceding->optimize();
	}
	if (last_elsif != NULL) {
		last_elsif->optimize();
	}
}

/* An identifier's value can change at run-time, so we can't perform
 constant folding optimization on it unless it is a constant.
 Thus we just do nothing here. It can be treated in the fold_constants()
 method, however. */
void ast_id::optimize() {
}

void ast_indexed::optimize() {
	if (optimizer->is_binop(index)) {
		index = optimizer->fold_constants(index);
	}
}

/* This convenience method is used to apply constant folding to all
 binary operations. It returns either the resulting optimized node or the
 original node if no optimization could be performed. */
ast_expression *ast_optimizer::fold_constants(ast_expression *node) {
	if(!(node->tag==AST_ADD||node->tag==AST_SUB||node->tag==AST_OR||node->tag==AST_AND||node->tag==AST_MULT||node->tag==AST_DIVIDE||node->tag==AST_IDIV||node->tag==AST_MOD)){
		return node;
	}

	//get operation
	ast_binaryoperation* binop = node->get_ast_binaryoperation();

	//Optimize left node though recursion
	if (is_binop(binop->left)) {
		binop->left = 	(binop->left);
	}
	//Optimize right node though recursion
	if (is_binop(binop->right)) {
		binop->right = fold_constants(binop->right);
	}
	std::vector<ast_expression*> leftright;
	leftright.push_back(binop->left);
	leftright.push_back(binop->right);
	std::vector<double> results;
	bool is_real = false;
	for (auto it = leftright.begin(); it != leftright.end(); it++) {
		//simple integer case
		if ((*it)->get_ast_integer()) {
			results.push_back((double) (*it)->get_ast_integer()->value);
		}
		//simple real case
		else if ((*it)->get_ast_real()) {
			results.push_back((double) (*it)->get_ast_real()->value);
			is_real = true;
		}
		//if it is a variable
		else if ((*it)->get_ast_id()) {
			sym_index sym_p = (*it)->get_ast_id()->sym_p;
			//get symbol
			symbol* sym = sym_tab->get_symbol(sym_p);
			//check if it is CONST
			if (sym->tag != SYM_CONST) {
				return binop;
			}
			//if it is integer
			if (sym_tab->get_symbol_type(sym_p) == integer_type) {
				results.push_back(
						(double) sym->get_constant_symbol()->const_value.ival);
			}
			//if it is real
			else {
				results.push_back(sym->get_constant_symbol()->const_value.rval);
			}
		} else {
			return binop;
		}

	}
	//this should never happen
	if (results.size() != 2) {
		return binop;
	}
	double return_value;
	switch (binop->tag) {
	case AST_ADD:
		return_value = results[0] + results[1];
		break;
	case AST_SUB:
		return_value = results[0] - results[1];
		break;
	case AST_OR:
		return_value = (long) results[0] || (long) results[1];
		break;
	case AST_AND:
		return_value = (long) results[0] && (long) results[1];
		break;
	case AST_MULT:
		return_value = results[0] * results[1];
		break;
	case AST_DIVIDE:
		if (results[0] == 0.0) {
			error(node->pos) << "Division by zero" << std::endl;
			abort();
		}
		return_value = results[0] / results[1];
		is_real = true;
		break;
	case AST_IDIV:
		return_value = (int) results[0] / (int) results[1];
		break;
	case AST_MOD:
		return_value = (int) results[0] % (int) results[1];
		break;
	default:
		fatal("Error in fold constants");
		return NULL;
	}
	if (is_real) {
		return new ast_real(binop->pos, return_value);
	} else {
		return new ast_integer(binop->pos, (long) return_value);
	}
}

/* All the binary operations should already have been detected in their parent
 nodes, so we don't need to do anything at all here. */
void ast_add::optimize() {
	/* Your code here */
}

void ast_sub::optimize() {
	/* Your code here */
}

void ast_mult::optimize() {
	/* Your code here */
}

void ast_divide::optimize() {
	/* Your code here */
}

void ast_or::optimize() {
	/* Your code here */
}

void ast_and::optimize() {
	/* Your code here */
}

void ast_idiv::optimize() {
	/* Your code here */
}

void ast_mod::optimize() {
	/* Your code here */
}

/* We can apply constant folding to binary relations as well. */
void ast_equal::optimize() {
	if (optimizer->is_binop(left)) {
		left = optimizer->fold_constants(left);
	}
	if (optimizer->is_binop(right)) {
		right = optimizer->fold_constants(right);
	}
}

void ast_notequal::optimize() {
	if (optimizer->is_binop(left)) {
		left = optimizer->fold_constants(left);
	}
	if (optimizer->is_binop(right)) {
		right = optimizer->fold_constants(right);
	}
}

void ast_lessthan::optimize() {
	if (optimizer->is_binop(left)) {
		left = optimizer->fold_constants(left);
	}
	if (optimizer->is_binop(right)) {
		right = optimizer->fold_constants(right);
	}
}

void ast_greaterthan::optimize() {
	if (optimizer->is_binop(left)) {
		left = optimizer->fold_constants(left);
	}
	if (optimizer->is_binop(right)) {
		right = optimizer->fold_constants(right);
	}
}

/*** The various classes derived from ast_statement. ***/

void ast_procedurecall::optimize() {
	if (parameter_list != NULL) {
		parameter_list->optimize();
	}
}

void ast_assign::optimize() {
	if (optimizer->is_binop(rhs)) {
		rhs = optimizer->fold_constants(rhs);
	}
}

void ast_while::optimize() {
	condition->optimize();
	if (optimizer->is_binop(condition)) {
		condition = optimizer->fold_constants(condition);
	}
	body->optimize();
}

void ast_if::optimize() {
	condition->optimize();
	if (optimizer->is_binop(condition)) {
		condition = optimizer->fold_constants(condition);
	}
	body->optimize();
	if (elsif_list != NULL) {
		elsif_list->optimize();
	}
	if (else_body != NULL) {
		else_body->optimize();
	}
}

void ast_return::optimize() {
	if(this->value != NULL){
		this->value->optimize();
		this->value = optimizer->fold_constants(this->value);
}
}

void ast_functioncall::optimize() {
	if (parameter_list != NULL) {
		parameter_list->optimize();
	}
}

void ast_uminus::optimize() {
	if (optimizer->is_binop(expr)) {
		expr = optimizer->fold_constants(expr);
	}
}

void ast_not::optimize() {
	if (optimizer->is_binop(expr)) {
		expr = optimizer->fold_constants(expr);
	}
}

void ast_elsif::optimize() {
	condition->optimize();
	if (optimizer->is_binop(condition)) {
		condition = optimizer->fold_constants(condition);
	}
	if (body != NULL) {
		body->optimize();
	}
}

void ast_integer::optimize() {
	/* Your code here */
}

void ast_real::optimize() {
	/* Your code here */
}

/* Note: See the comment in fold_constants() about casts and folding. */
void ast_cast::optimize() {
	/* Your code here */
}

void ast_procedurehead::optimize() {
	fatal("Trying to call ast_procedurehead::optimize()");
}

void ast_functionhead::optimize() {
	fatal("Trying to call ast_functionhead::optimize()");
}
