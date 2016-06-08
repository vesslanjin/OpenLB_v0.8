/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * Geometry specifications for 2D multiblocks -- implementation.
 */

#include "multiDataGeometry2D.h"
#include "core/olbDebug.h"


namespace olb {

////////////////////// Class BlockParameters2D /////////////////////////////

BlockParameters2D::BlockParameters2D(int x0_, int x1_, int y0_, int y1_,
                                     int envelopeWidth_, int procId_,
                                     bool leftX, bool rightX, bool leftY, bool rightY)
  : envelopeWidth(envelopeWidth_),
    procId(procId_),
    bulk(x0_, x1_, y0_, y1_),
    envelope(x0_-envelopeWidth, x1_+envelopeWidth, y0_-envelopeWidth, y1_+envelopeWidth),
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
}


////////////////////// Class MultiDataDistribution2D /////////////////////

MultiDataDistribution2D::MultiDataDistribution2D(int nx_, int ny_)
  : nx(nx_), ny(ny_)
{ }

MultiDataDistribution2D& MultiDataDistribution2D::operator=(MultiDataDistribution2D const& rhs) {
  nx = rhs.nx;
  ny = rhs.ny;
  blocks = rhs.blocks;
  normalOverlaps = rhs.normalOverlaps;
  periodicOverlaps = rhs.periodicOverlaps;
  return *this;
}


BlockParameters2D const& MultiDataDistribution2D::getBlockParameters(int whichBlock) const {
  OLB_PRECONDITION( whichBlock < getNumBlocks() );
  return blocks[whichBlock];
}
Overlap2D const& MultiDataDistribution2D::getNormalOverlap(int whichOverlap) const {
  OLB_PRECONDITION( whichOverlap < getNumNormalOverlaps() );
  return normalOverlaps[whichOverlap];
}
Overlap2D const& MultiDataDistribution2D::getPeriodicOverlap(int whichOverlap) const {
  OLB_PRECONDITION( whichOverlap < getNumPeriodicOverlaps() );
  return periodicOverlaps[whichOverlap];
}

void MultiDataDistribution2D::addBlock(int x0, int x1, int y0, int y1, int envelopeWidth, int procId) {
  OLB_PRECONDITION( x0>=0 && y0>=0 );
  OLB_PRECONDITION( x1<nx && y1<ny );
  OLB_PRECONDITION( x0 <= x1 && y0 <= y1 );

  BlockParameters2D newBlock(x0, x1, y0, y1, envelopeWidth, procId,
                             x0==0, x1==nx-1, y0==0, y1==ny-1);
  computeNormalOverlaps(newBlock);
  blocks.push_back(newBlock);
  computePeriodicOverlaps();
}

int MultiDataDistribution2D::locate(int x, int y, int guess) const {
  OLB_PRECONDITION( x>=0 && x < nx );
  OLB_PRECONDITION( y>=0 && y < ny );
  OLB_PRECONDITION( guess < getNumBlocks() );

  for (int iBlock=0; iBlock<(int)blocks.size(); ++iBlock, guess = (guess+1)%blocks.size()) {
    BlockCoordinates2D const& coord = blocks[guess].getBulk();
    if (util::contained(x, y, coord.x0, coord.x1, coord.y0, coord.y1)) {
      return guess;
    }
  }
  return -1;
}

int MultiDataDistribution2D::locateInEnvelopes(int x, int y,
    std::vector<int>& foundId, int guess) const
{
  OLB_PRECONDITION( x>=0 && x < nx );
  OLB_PRECONDITION( y>=0 && y < ny );

  int found = locate(x,y, guess);
  if (found == -1) {
    found = 0;
  }
  else {
    foundId.push_back(found);
    for (int iNeighbor=0; iNeighbor < (int)neighbors[found].size(); ++iNeighbor) {
      int nextNeighbor = neighbors[found][iNeighbor];
      BlockCoordinates2D const& coord = blocks[nextNeighbor].getEnvelope();
      if (util::contained(x, y, coord.x0, coord.x1, coord.y0, coord.y1)) {
        foundId.push_back(nextNeighbor);
      }
    }
  }
  return found;
}

void MultiDataDistribution2D::computeNormalOverlaps(BlockParameters2D const& newBlock) {
  neighbors.resize(getNumBlocks()+1);
  BlockCoordinates2D intersection;
  int iNew = getNumBlocks();
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (util::intersect(blocks[iBlock].getBulk(), newBlock.getNonPeriodicEnvelope(), intersection)) {
      normalOverlaps.push_back(Overlap2D(iBlock, iNew, intersection));
      neighbors[iBlock].push_back(iNew);
    }
    if (util::intersect(newBlock.getBulk(), blocks[iBlock].getNonPeriodicEnvelope(), intersection)) {
      normalOverlaps.push_back(Overlap2D(iNew, iBlock, intersection));
      neighbors[iNew].push_back(iBlock);
    }
  }
}

void MultiDataDistribution2D::computePeriodicOverlaps() {
  int iNew = getNumBlocks()-1;
  BlockParameters2D const& newBlock = blocks[iNew];
  BlockCoordinates2D intersection;
  for (int dx=-1; dx<=+1; dx+=1) {
    for (int dy=-1; dy<=+1; dy+=1) {
      if (dx!=0 || dy!=0) {
        int shiftX = dx*getNx();
        int shiftY = dy*getNy();
        BlockCoordinates2D newBulk(newBlock.getBulk().shift(shiftX,shiftY));
        BlockCoordinates2D newEnvelope(newBlock.getEnvelope().shift(shiftX,shiftY));
        for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
          if (util::intersect(blocks[iBlock].getBulk(), newEnvelope, intersection)) {
            periodicOverlaps.push_back( Overlap2D(iBlock, iNew, intersection, shiftX, shiftY) );
            neighbors[iBlock].push_back(iNew);
          }
          if (!(iBlock==iNew) &&
              util::intersect(newBulk, blocks[iBlock].getEnvelope(), intersection))
          {
            intersection = intersection.shift(-shiftX,-shiftY);
            periodicOverlaps.push_back( Overlap2D(iNew, iBlock, intersection, -shiftX, -shiftY) );
            neighbors[iNew].push_back(iBlock);
          }
        }
      }
    }
  }
}

size_t MultiDataDistribution2D::getNumAllocatedBulkCells() const {
  size_t numCells = 0;
  for (unsigned iBlock=0; iBlock<blocks.size(); ++iBlock) {
    numCells += (size_t)blocks[iBlock].getBulkLx() * (size_t)blocks[iBlock].getBulkLy();
  }
  return numCells;
}

bool MultiDataDistribution2D::getNextChunkX(int iX, int iY, int& nextLattice, int& nextChunkSize) const {
  nextLattice = locate(iX,iY);
  if (nextLattice == -1) {
    int exploreX = iX+1;
    while(exploreX<getNx() && locate(exploreX,iY)==-1) {
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

bool MultiDataDistribution2D::getNextChunkY(int iX, int iY, int& nextLattice, int& nextChunkSize) const {
  nextLattice = locate(iX,iY);
  if (nextLattice == -1) {
    int exploreY = iY+1;
    while(exploreY<getNy() && locate(iX,exploreY)==-1) {
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


RelevantIndexes2D::RelevantIndexes2D(int numBlocks, int numNormalOverlaps,
                                     int numPeriodicOverlaps, int nx, int ny)
{
  listAllIndexes(numBlocks, numNormalOverlaps, numPeriodicOverlaps, nx, ny);
}

RelevantIndexes2D::RelevantIndexes2D(MultiDataDistribution2D const& dataDistribution, int whichRank) {
  computeRelevantIndexesInParallel(dataDistribution, whichRank);
}

void RelevantIndexes2D::listAllIndexes (
  int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny)
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
  boundingBox = BlockCoordinates2D(0,nx-1, 0,ny-1);
}

void RelevantIndexes2D::computeRelevantIndexesInParallel(MultiDataDistribution2D const& dataDistribution,
    int whichRank)
{
  for (int iBlock=0; iBlock<dataDistribution.getNumBlocks(); ++iBlock) {
    if (dataDistribution.getBlockParameters(iBlock).getProcId() == whichRank) {
      BlockCoordinates2D const& newBlock = dataDistribution.getBlockParameters(iBlock).getEnvelope();
      if (myBlocks.empty()) {
        boundingBox = newBlock;
      }
      else {
        if (newBlock.x0 < boundingBox.x0) boundingBox.x0 = newBlock.x0;
        if (newBlock.x1 > boundingBox.x1) boundingBox.x1 = newBlock.x1;
        if (newBlock.y0 < boundingBox.y0) boundingBox.y0 = newBlock.y0;
        if (newBlock.y1 > boundingBox.y1) boundingBox.y1 = newBlock.y1;
      }
      myBlocks.push_back(iBlock);
      nearbyBlocks.push_back(iBlock);
    }
  }
  for (int iOverlap=0; iOverlap<dataDistribution.getNumNormalOverlaps(); ++iOverlap) {
    Overlap2D const& overlap = dataDistribution.getNormalOverlap(iOverlap);
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
    Overlap2D const& overlap = dataDistribution.getPeriodicOverlap(iOverlap);
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
