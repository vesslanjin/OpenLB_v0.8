/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2010 Jonas Latt, Jonas Fietz, Mathias Krause
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

/** \file
 * Input/Output in XML format -- non-generic code.
 */

#include "io/xmlReader.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace olb {

XMLreader XMLreader::notFound;

XMLreader::XMLreader()
  : clout(std::cout,"XMLreader") {
  name = "XML node not found";
  warningsOn = true;
}

XMLreader::XMLreader( TiXmlNode* pParent)
  : clout(std::cout,"XMLreader") {
    warningsOn = true;
  if (singleton::mpi().isMainProcessor()) {
    mainProcessorIni(pParent);
  }
  else {
    slaveProcessorIni();
  }
}

XMLreader::XMLreader(const std::string& fName)
  : clout(std::cout,"XMLreader") {
    warningsOn = true;
  TiXmlDocument* doc = 0;
  int loadOK = false;
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  if (singleton::mpi().isMainProcessor()) {
#endif
    doc = new TiXmlDocument(fName.c_str());
    loadOK = doc->LoadFile();
    if(!loadOK) {
      clout << std::string("Problem processing input XML file ") << fName << std::endl;
    }
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  }
  if (singleton::mpi().isMainProcessor()) {
#endif
    mainProcessorIni(doc);
    delete doc;
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  }
  else {
    slaveProcessorIni();
  }
#endif
}

XMLreader::~XMLreader() {
  for (unsigned int iNode=0; iNode<children.size(); ++iNode) {
    delete children[iNode];
  }
}

void XMLreader::mainProcessorIni( TiXmlNode* pParent ) {
  assert (pParent->Type()==TiXmlNode::TINYXML_DOCUMENT || pParent->Type()==TiXmlNode::TINYXML_ELEMENT );
  if (pParent->Type() == TiXmlNode::TINYXML_DOCUMENT) {
    // ignore the surrounding PARAM-block
    pParent = pParent->FirstChildElement();
  }

  name = pParent->ValueStr();
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  singleton::mpi().bCast(&name,1);
#endif

  TiXmlAttribute* attr = pParent->ToElement()->FirstAttribute();
  while(attr != 0) {
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  int size = 0;
  std::string* key = const_cast<std::string*>(&attr->NameTStr());
  singleton::mpi().bCast(key, size);
  std::string* value = const_cast<std::string*>(&attr->ValueStr());
  singleton::mpi().bCast(value, size);
#endif
	  attributes[attr->NameTStr()] = attr->ValueStr();
	  attr = attr->Next();
  }
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  std::string tmpstr = "";
  int size = 0;
  singleton::mpi().bCast(&tmpstr, size);
  singleton::mpi().bCast(&tmpstr, size);
#endif


  TiXmlNode * pChild;
  int type = 0;
  for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
  {
    type = pChild->Type();
#ifdef PARALLEL_MODE_MPI  // parallel program execution
    singleton::mpi().bCast(&type, 1);
#endif
    if ( type==TiXmlNode::TINYXML_ELEMENT ) {
      children.push_back( new XMLreader( pChild ) );
    }
    else if ( type==TiXmlNode::TINYXML_TEXT ) {
      text = pChild->ToText()->ValueStr();
#ifdef PARALLEL_MODE_MPI  // parallel program execution
      singleton::mpi().bCast(&text,1);
#endif
    }
  }
  type = TiXmlNode::TINYXML_UNKNOWN;
#ifdef PARALLEL_MODE_MPI  // parallel program execution
  singleton::mpi().bCast(&type, 1);
#endif
}

void XMLreader::slaveProcessorIni()
{
#ifdef PARALLEL_MODE_MPI  // parallel program execution

  singleton::mpi().bCast(&name,1);
  std::string key = "";
  std::string value = "";
  int size = int();
  do {
	  singleton::mpi().bCast(&key, size);
	  singleton::mpi().bCast(&value, size);
	  attributes[key] = value;
  } while(key != "");
#endif

  int type=0;
  do {
#ifdef PARALLEL_MODE_MPI  // parallel program execution
    singleton::mpi().bCast(&type, 1);
#endif
    if ( type==TiXmlNode::TINYXML_ELEMENT ) {
      children.push_back( new XMLreader( 0 ) );
    }
    else if ( type==TiXmlNode::TINYXML_TEXT ) {
#ifdef PARALLEL_MODE_MPI  // parallel program execution
      singleton::mpi().bCast(&text,1);
#endif
    }
  }
  while (type != TiXmlNode::TINYXML_UNKNOWN);
}

void XMLreader::print(int indent) const {
  std::string indentStr(indent, ' ');
  clout << indentStr << "[" << name << "]" << std::endl;
  if (!text.empty()) {
    clout << indentStr << "  " << text << std::endl;
  }
  for (unsigned int iNode=0; iNode<children.size(); ++iNode) {
    children[iNode]->print(indent+2);
  }
}

XMLreader const& XMLreader::operator[] (std::string name) const
{
  for (unsigned int iNode=0; iNode<children.size(); ++iNode) {
    if (children[iNode]->name == name) {
      return *children[iNode];
    }
  }
  if ( warningsOn ) {
    clout << "Warning: cannot read value from node \"" << name << "\"" << std::endl;
  }
  return notFound;
}

std::vector<XMLreader*>::const_iterator XMLreader::begin() const {
  return children.begin();
}

std::vector<XMLreader*>::const_iterator XMLreader::end() const {
  return children.end();
}

std::string XMLreader::getName() const {
  return name;
}

void XMLreader::setWarningsOn(bool warnings) const {
  warningsOn = warnings;
  for (unsigned int iNode=0; iNode<children.size(); ++iNode) {
    children[iNode]->setWarningsOn(warnings);
  }
}

template <>
bool XMLreader::read<bool>(bool& value, bool verboseOn) const {
  std::stringstream valueStr(text);
  std::string word;
  valueStr >> word;
  // Transform to lower-case, so that "true" and "false" are case-insensitive.
  std::transform(word.begin(), word.end(), word.begin(), ::tolower);
  if (!word.compare("true") || (word=="1")) {
    value = true;
    return true;
  }
  else if (!word.compare("false") || (word=="0")) {
    value=false;
    return true;
  }
  else {
    if ( verboseOn ) {
      clout << std::string("Error: Cannot read boolean value from XML element ") << name << std::endl;
    }
  }
  return false;
}

template <>
bool XMLreader::read<int>(int& value, bool verboseOn) const {
  std::stringstream valueStr(text);
  int tmp = int();
  if (!(valueStr >> tmp)) {
    if ( verboseOn ) {
      clout << std::string("Error: cannot read value from XML element ") << name << std::endl;
    }
    return false;
  }
  value = tmp;
  return true;
}

template <>
bool XMLreader::read<double>(double& value, bool verboseOn) const {
  std::stringstream valueStr(text);
  double tmp = double();
  if (!(valueStr >> tmp)) {
    if ( verboseOn ) {
      clout << std::string("Error: cannot read value from XML element ") << name << std::endl;
    }
    return false;
  }
  value = tmp;
  return true;
}

template <>
bool XMLreader::read<std::string>(std::string& entry, bool verboseOn) const {
  if(name == "XML node not found") {
    return false;
  }

  entry = text;
  return true;
}

std::string XMLreader::getAttribute(const std::string& aName) const {
	std::map<std::string, std::string>::const_iterator it = attributes.find(aName);
	if ( it == attributes.end()) {
		return "Attribute not found.";
	}
	return it->second;
	//return attributes[aName];
}

}  // namespace olb
