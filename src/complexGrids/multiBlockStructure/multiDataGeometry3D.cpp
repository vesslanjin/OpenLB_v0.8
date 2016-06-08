/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt and Bernd Stahl
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
 * Geometry specifications for 3D multiblocks -- implementation.
 */

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiDataGeometry3D.h"
#include "core/olbDebug.h"

namespace olb {



////////////////////// Class BlockParameters3D /////////////////////////////

BlockParameters3D::BlockParameters3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                                     int envelopeWidth_, int procId_,
                                     bool leftX, bool rightX, bool leftY, bool rightY, bool leftZ, bool rightZ)
  : envelopeWidth(envelopeWidth_),
    procId(procId_),
    bulk(x0_, x1_, y0_, y1_, z0_, z1_),
    envelope(x0_-envelopeWidth, x1_+envelopeWidth, y0_-envelopeWidth,
             y1_+envelopeWidth, z0_-envelopeWidth, z1_+envelopeWidth),
    nonPeriodicEnvelope(envelope)
{
  if (leftX) {
    nonPeriodicEnvelope.x0 += envelopeWidth;
  }
  if (rightX) {
    nonPeriodicEnvelope.x1 -= envelopeWidth;
  }

  if (leftY) {
    nonPeriodicEnvelope.y0 += envelopeWidth;
  }
  if (rightY) {
    nonPeriodicEnvelope.y1 -= envelopeWidth;
  }
  if (leftZ) {
    nonPeriodicEnvelope.z0 += envelopeWidth;
  }
  if (rightZ) {
    nonPeriodicEnvelope.z1 -= envelopeWidth;
  }
}


////////////////////// Class MultiDataDistribution3D /////////////////////

MultiDataDistribution3D::MultiDataDistribution3D(int nx_, int ny_, int nz_)
  : nx(nx_), ny(ny_), nz(nz_)
{ }

MultiDataDistribution3D& MultiDataDistribution3D::operator=(MultiDataDistribution3D const& rhs) {
  nx = rhs.nx;
  ny = rhs.ny;
  nz = rhs.nz;
  blocks = rhs.blocks;
  normalOverlaps = rhs.normalOverlaps;
  periodicOverlaps = rhs.periodicOverlaps;
  return (*this);
}


BlockParameters3D const& MultiDataDistribution3D::getBlockParameters(int whichBlock) const {
  OLB_PRECONDITION( whichBlock < getNumBlocks() );
  return blocks[whichBlock];
}
Overlap3D const& MultiDataDistribution3D::getNormalOverlap(int whichOverlap) const {
  OLB_PRECONDITION( whichOverlap < getNumNormalOverlaps() );
  return normalOverlaps[whichOverlap];
}
Overlap3D const& MultiDataDistribution3D::getPeriodicOverlap(int whichOverlap) const {
  OLB_PRECONDITION( whichOverlap < getNumPeriodicOverlaps() );
  return periodicOverlaps[whichOverlap];
}

void MultiDataDistribution3D::addBlock(int x0, int x1, int y0, int y1, int z0, int z1,
                                       int envelopeWidth, int procId)
{
  OLB_PRECONDITION( x0>=0 && y0>=0 && z0>=0);
  OLB_PRECONDITION( x1<nx && y1<ny && z1<nz);
  OLB_PRECONDITION( x0 <= x1 && y0 <= y1 && z0 <= z1);

  BlockParameters3D newBlock(x0, x1, y0, y1, z0, z1, envelopeWidth, procId,
                             x0==0, x1==nx-1, y0==0, y1==ny-1, z0==0, z1==nz-1);

  computeNormalOverlaps(newBlock);
  blocks.push_back(newBlock);
  computePeriodicOverlaps();
}

int MultiDataDistribution3D::locate(int x, int y, int z, int guess) const {
  OLB_PRECONDITION( x>=0 && x < nx );
  OLB_PRECONDITION( y>=0 && y < ny );
  OLB_PRECONDITION( z>=0 && z < nz );
  OLB_PRECONDITION( guess < getNumBlocks() );

  for (int iBlock=0; iBlock<(int)getNumBlocks(); ++iBlock, guess = (guess+1)%blocks.size()) {
    BlockCoordinates3D const& coord = blocks[guess].getBulk();
    if (util::contained(x, y, z, coord.x0, coord.x1, coord.y0, coord.y1, coord.z0, coord.z1)) {
      return guess;
    }
  }
  return -1;
}

int MultiDataDistribution3D::locateInEnvelopes(int x, int y, int z,
    std::vector<int>& foundId, int guess) const {
  OLB_PRECONDITION( x>=0 && x < nx );
  OLB_PRECONDITION( y>=0 && y < ny );
  OLB_PRECONDITION( z>=0 && z < nz );

  int found = locate(x,y,z, guess);
  if (found == -1) {
    found = 0;
  }
  else {
    foundId.push_back(found);
    for (int iNeighbor=0; iNeighbor < (int)neighbors[found].size(); ++iNeighbor) {
      int nextNeighbor = neighbors[found][iNeighbor];
      BlockCoordinates3D const& coord = blocks[nextNeighbor].getEnvelope();
      if (util::contained(x, y, z, coord.x0, coord.x1, coord.y0, coord.y1, coord.z0, coord.z1)) {
        foundId.push_back(nextNeighbor);
      }
    }
  }
  return found;
}

void MultiDataDistribution3D::computeNormalOverlaps(BlockParameters3D const& newBlock) {
  neighbors.resize(getNumBlocks()+1);
  BlockCoordinates3D intersection;
  int iNew = getNumBlocks();
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (util::intersect(blocks[iBlock].getBulk(), newBlock.getNonPeriodicEnvelope(), intersection)) {
      normalOverlaps.push_back(Overlap3D(iBlock, iNew, intersection));
      neighbors[iBlock].push_back(iNew);
    }
    if (util::intersect(newBlock.getBulk(), blocks[iBlock].getNonPeriodicEnvelope(), intersection)) {
      normalOverlaps.push_back(Overlap3D(iNew, iBlock, intersection));
      neighbors[iNew].push_back(iBlock);
    }
  }
}

void MultiDataDistribution3D::computePeriodicOverlaps() {
  int iNew = getNumBlocks()-1;
  BlockParameters3D const& newBlock = blocks[iNew];
  BlockCoordinates3D intersection;
  for (int dx=-1; dx<=+1; dx+=1) {
    for (int dy=-1; dy<=+1; dy+=1) {
      for (int dz=-1; dz<=+1; dz+=1) {
        if (dx!=0 || dy!=0 || dz!=0) {
          int shiftX = dx*getNx();
          int shiftY = dy*getNy();
          int shiftZ = dz*getNz();
          BlockCoordinates3D newBulk(newBlock.getBulk().shift(shiftX,shiftY,shiftZ));
          BlockCoordinates3D newEnvelope(newBlock.getEnvelope().shift(shiftX,shiftY,shiftZ));
          for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
            if (util::intersect(blocks[iBlock].getBulk(), newEnvelope, intersection)) {
              periodicOverlaps.push_back( Overlap3D(iBlock, iNew, intersection,
                                                    shiftX, shiftY, shiftZ) );
              neighbors[iBlock].push_back(iNew);
            }
            if (!(iBlock==iNew) &&
                util::intersect(newBulk, blocks[iBlock].getEnvelope(), intersection))
            {
              intersection = intersection.shift(-shiftX,-shiftY, -shiftZ);
              periodicOverlaps.push_back( Overlap3D(iNew, iBlock, intersection,
                                                    -shiftX, -shiftY, -shiftZ) );
              neighbors[iNew].push_back(iBlock);
            }
          }
        }
      }
    }
  }
}

size_t MultiDataDistribution3D::getNumAllocatedBulkCells() const {
  int numCells = 0;
  for (unsigned iBlock=0; iBlock<blocks.size(); ++iBlock) {
    numCells += (size_t)blocks[iBlock].getBulkLx() *
                (size_t)blocks[iBlock].getBulkLy() *
                (size_t)blocks[iBlock].getBulkLz();
  }
  return numCells;
}

bool MultiDataDistribution3D::getNextChunkX(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const {
  nextLattice = locate(iX,iY,iZ);
  if (nextLattice == -1) {
    int exploreX = iX+1;
    while(exploreX<getNx() && locate(exploreX,iY,iZ)==-1) {
      ++exploreX;
    }
    nextChunkSize = exploreX-iX;
    return false;
  }
  else {
    nextChunkSize = blocks[nextLattice].getBulk().x1-iX+1;
    return true;
  }
}

bool MultiDataDistribution3D::getNextChunkY(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const {
  nextLattice = locate(iX,iY,iZ);
  if (nextLattice == -1) {
    int exploreY = iY+1;
    while(exploreY<getNy() && locate(iX,exploreY,iZ)==-1) {
      ++exploreY;
    }
    nextChunkSize = exploreY-iY;
    return false;
  }
  else {
    nextChunkSize = blocks[nextLattice].getBulk().y1-iY+1;
    return true;
  }
}

bool MultiDataDistribution3D::getNextChunkZ(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const {
  nextLattice = locate(iX,iY,iZ);
  if (nextLattice == -1) {
    int exploreZ = iZ+1;
    while(exploreZ<getNz() && locate(iX,iY,exploreZ)==-1) {
      ++exploreZ;
    }
    nextChunkSize = exploreZ-iZ;
    return false;
  }
  else {
    nextChunkSize = blocks[nextLattice].getBulk().z1-iZ+1;
    return true;
  }
}

RelevantIndexes3D::RelevantIndexes3D(int numBlocks, int numNormalOverlaps,
                                     int numPeriodicOverlaps, int nx, int ny, int nz)
{
  listAllIndexes(numBlocks, numNormalOverlaps, numPeriodicOverlaps, nx, ny, nz);
}

RelevantIndexes3D::RelevantIndexes3D(MultiDataDistribution3D const& dataDistribution, int whichRank) {
  computeRelevantIndexesInParallel(dataDistribution, whichRank);
}

void RelevantIndexes3D::listAllIndexes (
  int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny, int nz)
{
  myBlocks.resize(numBlocks);
  nearbyBlocks.resize(numBlocks);
  for (int iBlock=0; iBlock<numBlocks; ++iBlock) {
    myBlocks[iBlock]     = iBlock;
    nearbyBlocks[iBlock] = iBlock;
  }
  normalOverlaps.resize(numNormalOverlaps);
  for (int iOverlap=0; iOverlap<numNormalOverlaps; ++iOverlap) {
    normalOverlaps[iOverlap] = iOverlap;
  }
  periodicOverlaps.resize(numPeriodicOverlaps);
  periodicOverlapWithMe.resize(numPeriodicOverlaps);
  for (int iOverlap=0; iOverlap<numPeriodicOverlaps; ++iOverlap) {
    periodicOverlaps[iOverlap] = iOverlap;
    periodicOverlapWithMe[iOverlap] = iOverlap;
  }
  boundingBox = BlockCoordinates3D(0,nx-1, 0,ny-1, 0,nz-1);
}

void RelevantIndexes3D::computeRelevantIndexesInParallel(MultiDataDistribution3D const& dataDistribution,
    int whichRank)
{
  for (int iBlock=0; iBlock<dataDistribution.getNumBlocks(); ++iBlock) {
    if (dataDistribution.getBlockParameters(iBlock).getProcId() == whichRank) {
      BlockCoordinates3D const& newBlock = dataDistribution.getBlockParameters(iBlock).getEnvelope();
      if (myBlocks.empty()) {
        boundingBox = newBlock;
      }
      else {
        if (newBlock.x0 < boundingBox.x0) boundingBox.x0 = newBlock.x0;
        if (newBlock.x1 > boundingBox.x1) boundingBox.x1 = newBlock.x1;
        if (newBlock.y0 < boundingBox.y0) boundingBox.y0 = newBlock.y0;
        if (newBlock.y1 > boundingBox.y1) boundingBox.y1 = newBlock.y1;
        if (newBlock.z0 < boundingBox.z0) boundingBox.z0 = newBlock.z0;
        if (newBlock.z1 > boundingBox.z1) boundingBox.z1 = newBlock.z1;
      }
      myBlocks.push_back(iBlock);
      nearbyBlocks.push_back(iBlock);
    }
  }
  for (int iOverlap=0; iOverlap<dataDistribution.getNumNormalOverlaps(); ++iOverlap) {
    Overlap3D const& overlap = dataDistribution.getNormalOverlap(iOverlap);
    int originalProc = dataDistribution.getBlockParameters(overlap.getOriginalId()).getProcId();
    int overlapProc = dataDistribution.getBlockParameters(overlap.getOverlapId()).getProcId();
    if (originalProc == whichRank) {
      nearbyBlocks.push_back( overlap.getOverlapId() );
    }
    if (originalProc == whichRank || overlapProc == whichRank) {
      normalOverlaps.push_back(iOverlap);
    }
  }
  for (int iOverlap=0; iOverlap<dataDistribution.getNumPeriodicOverlaps(); ++iOverlap) {
    Overlap3D const& overlap = dataDistribution.getPeriodicOverlap(iOverlap);
    int originalProc = dataDistribution.getBlockParameters(overlap.getOriginalId()).getProcId();
    int overlapProc = dataDistribution.getBlockParameters(overlap.getOverlapId()).getProcId();
    if (originalProc == whichRank) {
      nearbyBlocks.push_back( overlap.getOverlapId() );
    }
    if (overlapProc == whichRank) {
      periodicOverlapWithMe.push_back(iOverlap);
    }
    if (originalProc == whichRank || overlapProc == whichRank) {
      periodicOverlaps.push_back(iOverlap);
    }
  }
  // Erase duplicates in nearbyBlocks
  std::sort(nearbyBlocks.begin(), nearbyBlocks.end());
  std::vector<int>::iterator newEnd = unique(nearbyBlocks.begin(), nearbyBlocks.end());
  nearbyBlocks.erase(newEnd, nearbyBlocks.end());
}

}  // namespace olb
