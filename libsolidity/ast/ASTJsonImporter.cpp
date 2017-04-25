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

#include <libsolidity/ast/ASTJsonImporter.h>
#include <json/json.h>

using namespace std;

namespace dev
{
namespace solidity
{

ASTJsonImporter::ASTJsonImporter(
		Json::Value const& _ast
) : m_json(_ast)
{
}

ASTPointer<ASTNode> ASTJsonImporter::convertJsonToASTNode(Json::Value const& _ast){
	//pseudocode
	if (_ast["nodeType"] == "SourceUnit")
	    return createSourceUnit(_ast);
	if (_ast["nodeType"].asString() == "PragmaDirective")
	    return createPragmaDirective(_ast);
//	if (_ast["nodeType"].asString() == "ImportDirective")
//	    return createImportDirective(_ast);
//	if (_ast["nodeType"].asString() == "ContractDefinition")
//	    return createContractDefinition(_ast);
//	if (_ast["nodeType"].asString() == "InheritanceSpecifier")
//	    return createInheritanceSpecifier(_ast);
//	if (_ast["nodeType"].asString() == "UsingForDirective")
//		return createUsingForDirective(_ast);
	//add more cases here...
//		return createStructDefinition(_ast);
	else BOOST_THROW_EXCEPTION(InternalCompilerError() << errinfo_comment("type of JsonValue is unknown."));
}

SourceLocation ASTJsonImporter::getSourceLocation(Json::Value _node){
	string srcString = _node["src"].asString();
	auto firstColon = srcString.find(":");
	auto secondColon = srcString.find(":", firstColon+1);
	shared_ptr<string const> source = make_shared<string const>(srcString.substr(secondColon));
	return SourceLocation(
	    std::stoi(srcString.substr(0,firstColon)),
	    std::stoi(srcString.substr(firstColon, secondColon)),
	    source
	);
}

//ASTPointer<ASTNode> createX(Json::Value _node){
    //create args for the constructor of the node && see how they are filled in parser.cpp
    //copy from constructor in ast.h
    //create node
    //ASTPointer<ASTNode> tmp = make_shared<X>();
    //tmp->setId(_node["id"])
    //tmp->
    //return tmp;
    //}

ASTPointer<ASTNode> ASTJsonImporter::createSourceUnit(Json::Value const& _node){
	//create args for constructor
	SourceLocation const& location = getSourceLocation(_node);
	vector<ASTPointer<ASTNode>> nodes;
	for (auto& child : _node["nodes"])
		nodes.push_back(convertJsonToASTNode(child));
	//create node
	ASTPointer<ASTNode> tmp = make_shared<SourceUnit>(location, nodes);
//	tmp->setId(_node["id"]); //TODO write setId() for ASTNode

//	//fill the annotation
////	map<ASTString, vector<Declaration const*>> exportedSymbols;
////	for (auto& tuple : _node["exportedSymbols"])
////		exportedSymbols.insert({tuple.first, tuple.second});
////	tmp->annotation.exportedSymbols = exportedSymbols;
////	tmp->annotation().path = _node["absolutePath"];
	return tmp;
}



ASTPointer<ASTNode> ASTJsonImporter::createPragmaDirective(Json::Value const& _node) //help
{
	vector<Token::Value> tokens;//here
	vector<ASTString> literals;
	for (auto const& lit : _node["literals"])
	    literals.push_back(lit.asString()); //fixtype
	SourceLocation const& location = getSourceLocation(_node);
	ASTPointer<ASTNode> tmp = make_shared<PragmaDirective>(location, tokens, literals);
	//setID
	return tmp;
}

//ASTPointer<ASTNode> ASTJsonImporter::createImportDirective(Json::Value const& _node){
//    //create args for the fields of the node
//    ASTPointer<ASTString> path = make_shared<ASTString>(_node["file"]);
//    ASTPointer<ASTString> unitAlias = make_shared<ASTString>(_node["unitAlias"]);
//    std::vector<std::pair<ASTPointer<Identifier>, ASTPointer<ASTString>>> symbolAliases;
//    for (auto& tuple : _node["symbolAliases"])
//    {
//	symbolAliases.push_back(make_pair(
//		make_shared<Identifier>(tuple.first),
//		make_shared<ASTString>(tuple.second)
//	));
//    }
//    //create node
//    ASTNode tmp = make_shared<ImportDirective>(path, unitAlias,symbolAliases);
//    //fill the annotation
//    tmp.annotation.absolutePath = make_shared<ASTString>(_node["absolutePath"]);
//    //tmp.annotation.sourceUnit = _node(&createSourceUnit(????)) -> how to deal with pointers from the annotation?
//    //tmp.annotation.scope = make_shared<Identifier> ??
//    return tmp;
//    //}
//}

//ASTNode ASTJsonImporter::createContractDefinition(Json::Value _node){
//    //create args for the constructor of the node
//    SourceLocation const& location = getSourceLocation(_node);
//    ASTPointer<ASTString> const& _documentation = make_shared<ASTString>(""); //postponed
//    ASTPointer<ASTString> name = make_shared<ASTString>(_node["name"]);
//    std::vector<ASTPointer<InheritanceSpecifier>> const& baseContracts;
//    for (auto& base : _node["baseContracts"])
//	baseContracts.append(createInheritanceSpecifier(base));
//    std::vector<ASTPointer<ASTNode>> const& _subNodes;
//    for (auto& subnode : _node["nodes"])
//	subNodes.append(convertJsonToASTNode(subnode));
//    bool _isLibrary = _node["isLibrary"];
//    //create node
//    ASTPointer<ASTNode> tmp = make_shared<ContractDefinition>(
//		name,
//		docString,
//		baseContracts,
//		subNodes,
//		_isLibrary
//     );
//    //fill the annotation
//    tmp->annotation.isFullyImplemented = _node["isFullyImplemented"];
//    //tmp->annotation
//    return *tmp
//    }

//ASTPointer<ASTNode> ASTJsonImporter::createInheritanceSpecifier(Json::Value _node){
//    //create args for the constructor of the node && see how they are filled in parser.cpp
//    SourceLocation const& location = getSourceLocation(_node);
//    ASTPointer<UserDefinedTypeName> const& baseName = createUserDefinedTypeName(_node["baseName"]);
//    std::vector<ASTPointer<Expression>> arguments;
//    for (auto& arg : _node["arguments"])
//	arguments.push_back(createExpression(arg));
//    //    create node
//    ASTPointer<ASTNode> tmp = make_shared<InheritanceSpecifier>(
//	location,
//	basename,
//	arguments
//    );
//    //fill the annotation
//    return tmp;
//    }

    //create args for the constructor of the node && see how they are filled in parser.cpp
    //copy from constructor in ast.h
    //create node
    //ASTPointer<ASTNode> tmp = make_shared<X>();
    //tmp->setId(_node["id"])
    //fill the annotation
    //tmp->
    //return tmp;
    //}

//	ASTPointer<ASTNode> ASTJsonImporter::createUsingForDirective(Json::Value _node){ }
//	ASTPointer<ASTNode> ASTJsonImporter::createStructDefinition const& _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createEnumDefinition const& _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createEnumValue const& _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createParameterList const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createFunctionDefinition const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createVariableDeclaration const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createModifierDefinition const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createModifierInvocation const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createEventDefinition const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createTypeName const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createElementaryTypeName const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createUserDefinedTypeASTPointer<ASTNode>  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createFunctionTypeName const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createMapping const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createArrayTypeName const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createInlineAssembly const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createBlock const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createPlaceholderStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createIfStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createWhileStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createForStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createContinue const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createBreak const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createReturn const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createThrow const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createVariableDeclarationStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createExpressionStatement const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createConditional const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createAssignment const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createTupleExpression const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createUnaryOperation const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createBinaryOperation const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createFunctionCall const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createNewExpression const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createMemberAccess const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createIndexAccess const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createIdentifier const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createElementaryTypeNameExpression const&  _node){}
//	ASTPointer<ASTNode> ASTJsonImporter::createLiteral const&  _node){}



}
}
