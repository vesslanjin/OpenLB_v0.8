/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Bernd Stahl and Jonas Latt
 *  Address: Battelle Batiment A, Route de Drize 7, 1227 Carouge, Switzerland
 *  E-mail: bernd.stahl@cui.unige.ch
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
 * Utilities for 3D multi data distributions -- implementation.
 */

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiDataUtilities3D.h"
#include "core/dataFields3D.hh" // neded for template instantiation
#include "utilities/olbAlgorithms.h"

namespace olb {

////////////////////// function createRegularDataDistribution /////////////////////

MultiDataDistribution3D createRegularDataDistribution (
  int nx, int ny, int nz, int numBlocksX, int numBlocksY, int numBlocksZ,
  int envelopeWidth )
{
  MultiDataDistribution3D dataDistribution(nx, ny, nz);
  int posX = 0;
  int iBlock = 0;
  for (int iBlockX=0; iBlockX<numBlocksX; ++iBlockX) {
    int lx = nx / numBlocksX;
    if (iBlockX < nx%numBlocksX) ++lx;
    int posY = 0;
    for (int iBlockY=0; iBlockY<numBlocksY; ++iBlockY) {
      int ly = ny / numBlocksY;
      if (iBlockY < ny%numBlocksY) ++ly;
      int posZ = 0;
      for (int iBlockZ=0; iBlockZ<numBlocksZ; ++iBlockZ) {
        int lz = nz / numBlocksZ;
        if (iBlockZ < nz%numBlocksZ) ++lz;
        dataDistribution.addBlock(posX, posX+lx-1, posY, posY+ly-1, posZ, posZ+lz-1,
                                  envelopeWidth, iBlock++);
        posZ += lz;
      }
      posY += ly;
    }
    posX += lx;
  }
  return dataDistribution;
}

MultiDataDistribution3D createRegularDataDistribution(int nx, int ny, int nz, int envelopeWidth) {
  std::vector<int> repartition = algorithm::evenRepartition(singleton::mpi().getSize(), 3);
  return createRegularDataDistribution ( nx, ny, nz,
                                         repartition[0], repartition[1], repartition[2],
                                         envelopeWidth );
}


// template instantiation for CellTypeField3D
template class ScalarField3D<unsigned char>;

MultiDataDistribution3D createXSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField,
  int numBlocks,
  int envelopeWidth )
{
  int nX = cellTypeField.getNx();
  int nY = cellTypeField.getNy();
  int nZ = cellTypeField.getNz();

  std::vector<int> numActivePerSlice;
  int numActiveTotal = 0;
  for(int iX=0; iX<nX; iX++) {
    int numActiveCurrentSlice = 0;
    for (int iY=0; iY<nY; iY++) {
      for (int iZ=0; iZ<nZ; iZ++) {
        if (cellTypeField.get(iX,iY,iZ) > 0) numActiveCurrentSlice++;
      }
    }
    numActivePerSlice.push_back(numActiveCurrentSlice);
    numActiveTotal += numActiveCurrentSlice;
  }
  int numActivePerBlock = numActiveTotal / numBlocks;

  MultiDataDistribution3D dataDistribution(nX, nY, nZ);

  int iX=0;
  for (int iBlock=0; iBlock<numBlocks; ++iBlock) {
    int posX = iX;
    int numActiveCurrentBlock = 0;
    while (numActiveCurrentBlock<numActivePerBlock && iX<nX) {
      numActiveCurrentBlock += numActivePerSlice[iX];
      iX++;
    }
    dataDistribution.addBlock(posX, iX-1, 0, nY-1, 0, nZ-1, envelopeWidth, iBlock);
  }
  return dataDistribution;
}

MultiDataDistribution3D createYSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField,
  int numBlocks,
  int envelopeWidth )
{
  int nX = cellTypeField.getNx();
  int nY = cellTypeField.getNy();
  int nZ = cellTypeField.getNz();

  std::vector<int> numActivePerSlice;
  int numActiveTotal = 0;
  for (int iY=0; iY<nY; iY++) {
    int numActiveCurrentSlice = 0;
    for(int iX=0; iX<nX; iX++) {
      for(int iZ=0; iZ<nZ; iZ++) {
        if (cellTypeField.get(iX,iY,iZ) > 0) numActiveCurrentSlice++;
      }
    }
    numActivePerSlice.push_back(numActiveCurrentSlice);
    numActiveTotal += numActiveCurrentSlice;
  }
  int numActivePerBlock = numActiveTotal / numBlocks;

  MultiDataDistribution3D dataDistribution(nX, nY, nZ);

  int iY=0;
  for (int iBlock=0; iBlock<numBlocks; ++iBlock) {
    int posY = iY;
    int numActiveCurrentBlock = 0;
    while (numActiveCurrentBlock<numActivePerBlock && iY<nY) {
      numActiveCurrentBlock += numActivePerSlice[iY];
      iY++;
    }
    dataDistribution.addBlock( 0, nX-1, posY, iY-1, 0, nZ-1, envelopeWidth, iBlock);
  }
  return dataDistribution;
}

MultiDataDistribution3D createZSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField,
  int numBlocks,
  int envelopeWidth )
{
  int nX = cellTypeField.getNx();
  int nY = cellTypeField.getNy();
  int nZ = cellTypeField.getNz();

  std::vector<int> numActivePerSlice;
  int numActiveTotal = 0;
  for(int iZ=0; iZ<nZ; iZ++) {
    int numActiveCurrentSlice = 0;
    for(int iX=0; iX<nX; iX++) {
      for (int iY=0; iY<nY; iY++) {
        if (cellTypeField.get(iX,iY,iZ) > 0) numActiveCurrentSlice++;
      }
    }
    numActivePerSlice.push_back(numActiveCurrentSlice);
    numActiveTotal += numActiveCurrentSlice;
  }
  int numActivePerBlock = numActiveTotal / numBlocks;

  MultiDataDistribution3D dataDistribution(nX, nY, nZ);

  int iZ=0;
  for (int iBlock=0; iBlock<numBlocks; ++iBlock) {
    int posZ = iZ;
    int numActiveCurrentBlock = 0;
    while (numActiveCurrentBlock<numActivePerBlock && iZ<nZ) {
      numActiveCurrentBlock += numActivePerSlice[iZ];
      iZ++;
    }
    dataDistribution.addBlock( 0, nX-1, 0, nY-1, posZ, iZ-1, envelopeWidth, iBlock);
  }
  return dataDistribution;
}

MultiDataDistribution3D createXSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField, int envelopeWidth)
{
  return createXSlicedDataDistribution3D(cellTypeField, singleton::mpi().getSize(), envelopeWidth);
}

MultiDataDistribution3D createYSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField, int envelopeWidth)
{
  return createYSlicedDataDistribution3D(cellTypeField, singleton::mpi().getSize(), envelopeWidth);
}

MultiDataDistribution3D createZSlicedDataDistribution3D (
  CellTypeField3D const& cellTypeField, int envelopeWidth)
{
  return createZSlicedDataDistribution3D(cellTypeField, singleton::mpi().getSize(), envelopeWidth);
}

}  // namespace olb
