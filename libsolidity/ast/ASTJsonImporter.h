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
#include <vector>
#include <libsolidity/ast/AST.h>
#include <json/json.h>
#include <libsolidity/ast/ASTAnnotations.h>
#include <libevmasm/SourceLocation.h>

using namespace std;

namespace dev
{
namespace solidity
{
/**
 * takes an AST in Json Format and recreates it with AST-Nodes
 */

class ASTJsonImporter: public ASTConstVisitor
{
public:
	/// Create an Importer to import a given abstract syntax tree in Json format to an ASTNode
	explicit ASTJsonImporter(
		Json::Value const& _ast
		//std::map<std::string, unsigned> _sourceIndices = std::map<std::string, unsigned>()
	);

	//converts a given json node into its respective ASTNode-class
	ASTNode convertJsonToASTNode(Json::Value const& _ast);

	//instantiate the AST-Nodes with the information from the Json-nodes
	ASTPointer<ASTNode> createSourceUnit(Json::Value const& _node);
	ASTPointer<ASTNode> createPragmaDirective (const Json::Value &_node);
	ASTPointer<ASTNode> createImportDirective const& _node) override;
	ASTPointer<ASTNode> createContractDefinition const& _node) override;
	ASTPointer<ASTNode> createInheritanceSpecifier const& _node) override;
	ASTPointer<ASTNode> createUsingForDirective const& _node) override;
	ASTPointer<ASTNode> createStructDefinition const& _node) override;
	ASTPointer<ASTNode> createEnumDefinition const& _node) override;
	ASTPointer<ASTNode> createEnumValue const& _node) override;
	ASTPointer<ASTNode> createParameterList const& _node) override;
	ASTPointer<ASTNode> createFunctionDefinition const& _node) override;
	ASTPointer<ASTNode> createVariableDeclaration const& _node) override;
	ASTPointer<ASTNode> createModifierDefinition const& _node) override;
	ASTPointer<ASTNode> createModifierInvocation const& _node) override;
	ASTPointer<ASTNode> createEventDefinition const& _node) override;
	ASTPointer<ASTNode> createTypeName const& _node) override;
	ASTPointer<ASTNode> createElementaryTypeName const& _node) override;
	ASTPointer<ASTNode> createUserDefinedTypeASTPointer<ASTNode> _node) override;
	ASTPointer<ASTNode> createFunctionTypeName const& _node) override;
	ASTPointer<ASTNode> createMapping const& _node) override;
	ASTPointer<ASTNode> createArrayTypeName const& _node) override;
	ASTPointer<ASTNode> createInlineAssembly const& _node) override;
	ASTPointer<ASTNode> createBlock const& _node) override;
	ASTPointer<ASTNode> createPlaceholderStatement const& _node) override;
	ASTPointer<ASTNode> createIfStatement const& _node) override;
	ASTPointer<ASTNode> createWhileStatement const& _node) override;
	ASTPointer<ASTNode> createForStatement const& _node) override;
	ASTPointer<ASTNode> createContinue const& _node) override;
	ASTPointer<ASTNode> createBreak const& _node) override;
	ASTPointer<ASTNode> createReturn const& _node) override;
	ASTPointer<ASTNode> createThrow const& _node) override;
	ASTPointer<ASTNode> createVariableDeclarationStatement const& _node) override;
	ASTPointer<ASTNode> createExpressionStatement const& _node) override;
	ASTPointer<ASTNode> createConditional const& _node) override;
	ASTPointer<ASTNode> createAssignment const& _node) override;
	ASTPointer<ASTNode> createTupleExpression const& _node) override;
	ASTPointer<ASTNode> createUnaryOperation const& _node) override;
	ASTPointer<ASTNode> createBinaryOperation const& _node) override;
	ASTPointer<ASTNode> createFunctionCall const& _node) override;
	ASTPointer<ASTNode> createNewExpression const& _node) override;
	ASTPointer<ASTNode> createMemberAccess const& _node) override;
	ASTPointer<ASTNode> createIndexAccess const& _node) override;
	ASTPointer<ASTNode> createIdentifier const& _node) override;
	ASTPointer<ASTNode> createElementaryTypeNameExpression const& _node) override;
	ASTPointer<ASTNode> createLiteral const& _node) override;

private:


ASTNode convertJsonToASTNode(Json::Value const& _ast){
    //pseudocode
    switch (_ast["nodeType"])
    {
        case "SourceUnit":
            return createSourceUnit(_ast);
        case "PragmaDirective":
            return createPragmaDirective(_ast);
        case "ImportDirective":
            return createImportDirective(_ast);
        case "ContractDefinition":
            return createContractDefinition(_ast);
        case "InheritanceSpecifier":
            return createInheritanceSpecifier(_ast);
        case "UsingForDirective":
            return createStructDefinition(_ast);
        //add more cases here...
        default:
            someError(string("type of JsonValue is unknown."))
    }
}

//ASTPointer<ASTNode> createX(Json::Value _node){
    //create args for the constructor of the node && see how they are filled in parser.cpp
    //copy from constructor in ast.h
    //create node
    //ASTPointer<ASTNode> tmp = make_shared<X>();
    //tmp->setId(_node["id"])
    //fill the annotation
    //tmp->
    //return tmp;
    //}


}
