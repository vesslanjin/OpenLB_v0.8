/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt
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
 * Definition of singletons: global, publicly available information.
 */
#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>

namespace olb {

namespace singleton {

class Directories {
public:
  void setOlbDir(std::string olbDir_) {
    olbDir = olbDir_;
  }
  void setOutputDir(std::string outputDir) {
    setLogOutDir(outputDir);
    setImageOutDir(outputDir);
    setVtkOutDir(outputDir);
  }
  void setLogOutDir(std::string logOutDir_) {
    logOutDir = logOutDir_;
  }
  void setImageOutDir(std::string imageOutDir_) {
    imageOutDir = imageOutDir_;
  }
  void setVtkOutDir(std::string vtkOutDir_) {
    vtkOutDir = vtkOutDir_;
  }
  std::string getOlbDir() const {
    return olbDir;
  }
  std::string getLogOutDir() const {
    return logOutDir;
  }
  std::string getImageOutDir() const {
    return imageOutDir;
  }
  std::string getVtkOutDir() const {
    return vtkOutDir;
  }
private:
  Directories() {
    setOlbDir("");
    setOutputDir("");
  }
  ~Directories() { }
private:
  std::string olbDir;
  std::string logOutDir;
  std::string imageOutDir;
  std::string vtkOutDir;

  friend Directories& directories();
};

inline Directories& directories() {
  static Directories singleton;
  return singleton;
}

}  // namespace singleton

}  // namespace olb

#endif
