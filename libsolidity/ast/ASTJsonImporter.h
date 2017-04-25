/*
    This file is part of solidity.

    solidity is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    solidity is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @author julius <djudju@protonmail.com>
 * @date 2017
 * Converts an AST from json format to an ASTNode
 */

#pragma once

#include <vector>
#include <libsolidity/ast/AST.h>
#include <json/json.h>
#include <libsolidity/ast/ASTAnnotations.h>
#include <libevmasm/SourceLocation.h>

namespace dev
{
namespace solidity
{

/**
 * takes an AST in Json Format and recreates it with AST-Nodes
 */
class ASTJsonImporter
{
public:
	/// Create an Importer to import a given abstract syntax tree in Json format to an ASTNode
	ASTJsonImporter( Json::Value const& _ast);

	//converts a given json node into its respective ASTNode-class
	ASTPointer<ASTNode> convertJsonToASTNode(Json::Value const& _ast);
	SourceLocation getSourceLocation(Json::Value _node);

	//instantiate the AST-Nodes with the information from the Json-nodes
	ASTPointer<ASTNode> createSourceUnit(Json::Value const& _node);
	ASTPointer<ASTNode> createPragmaDirective(Json::Value const& _node);
//	ASTPointer<ASTNode> createImportDirective(Json::Value const& _node);
//	ASTPointer<ASTNode> createContractDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createInheritanceSpecifier(Json::Value const _node);
//	ASTPointer<ASTNode> createUsingForDirective(Json::Value const _node);
//	ASTPointer<ASTNodeASTJ> createStructDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createEnumDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createEnumValue(Json::Value const& _node);
//	ASTPointer<ASTNode> createParameterList(Json::Value const& _node);
//	ASTPointer<ASTNode> createFunctionDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createVariableDeclaration(Json::Value const& _node);
//	ASTPointer<ASTNode> createModifierDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createModifierInvocation(Json::Value const& _node);
//	ASTPointer<ASTNode> createEventDefinition(Json::Value const& _node);
//	ASTPointer<ASTNode> createTypeName(Json::Value const& _node);
//	ASTPointer<ASTNode> createElementaryTypeName(Json::Value const& _node);
//	ASTPointer<ASTNode> createUserDefinedTypeASTPointer<ASTNod _node);
//	ASTPointer<ASTNode> createFunctionTypeName(Json::Value const& _node);
//	ASTPointer<ASTNode> createMapping(Json::Value const& _node);
//	ASTPointer<ASTNode> createArrayTypeName(Json::Value const& _node);
//	ASTPointer<ASTNode> createInlineAssembly(Json::Value const& _node);
//	ASTPointer<ASTNode> createBlock(Json::Value const& _node);
//	ASTPointer<ASTNode> createPlaceholderStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createIfStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createWhileStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createForStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createContinue(Json::Value const& _node);
//	ASTPointer<ASTNode> createBreak(Json::Value const& _node);
//	ASTPointer<ASTNode> createReturn(Json::Value const& _node);
//	ASTPointer<ASTNode> createThrow(Json::Value const& _node);
//	ASTPointer<ASTNode> createVariableDeclarationStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createExpressionStatement(Json::Value const& _node);
//	ASTPointer<ASTNode> createConditional(Json::Value const& _node);
//	ASTPointer<ASTNode> createAssignment(Json::Value const& _node);
//	ASTPointer<ASTNode> createTupleExpression(Json::Value const& _node);
//	ASTPointer<ASTNode> createUnaryOperation(Json::Value const& _node);
//	ASTPointer<ASTNode> createBinaryOperation(Json::Value const& _node);
//	ASTPointer<ASTNode> createFunctionCall(Json::Value const& _node);
//	ASTPointer<ASTNode> createNewExpression(Json::Value const& _node);
//	ASTPointer<ASTNode> createMemberAccess(Json::Value const& _node);
//	ASTPointer<ASTNode> createIndexAccess(Json::Value const& _node);
//	ASTPointer<ASTNode> createIdentifier(Json::Value const& _node);
//	ASTPointer<ASTNode> createElementaryTypeNameExpression(Json::Value const& _node);
//	ASTPointer<ASTNode> createLiteral(Json::Value const& _node);

private:

	Json::Value m_json;


};

}
}

