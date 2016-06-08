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
 * Geometry specifications for 2D multiblocks -- header file.
 */

#ifndef MULTI_DATA_GEOMETRY_2D_H
#define MULTI_DATA_GEOMETRY_2D_H

#include <vector>
#include "core/util.h"

namespace olb {

/// Coordinates of a single BlockStructure within a MultiBlock
struct BlockCoordinates2D {
  BlockCoordinates2D() : x0(), x1(), y0(), y1() { }
  BlockCoordinates2D(int x0_, int x1_, int y0_, int y1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_)
  { }
  BlockCoordinates2D shift(int deltaX, int deltaY) const {
    return BlockCoordinates2D(x0+deltaX, x1+deltaX, y0+deltaY, y1+deltaY);
  }
  int x0, x1, y0, y1;
};

namespace util {

inline bool intersect (
  BlockCoordinates2D const& block1,
  BlockCoordinates2D const& block2,
  BlockCoordinates2D& inters )
{
  return intersect(block1.x0, block1.x1, block1.y0, block1.y1,
                   block2.x0, block2.x1, block2.y0, block2.y1,
                   inters.x0, inters.x1, inters.y0, inters.y1);
}

inline bool contained(int iX, int iY, BlockCoordinates2D const& block) {
  return contained(iX,iY, block.x0, block.x1, block.y0, block.y1);
}

}

class BlockParameters2D {
public:
  BlockParameters2D(int x0_, int x1_, int y0_, int y1_, int envelopeWidth_, int procId_,
                    bool leftX, bool rightX, bool leftY, bool rightY);
  int getEnvelopeWidth()                             const { return envelopeWidth; }
  int getProcId()                                    const { return procId; }
  BlockCoordinates2D const& getBulk()                const { return bulk; }
  BlockCoordinates2D const& getEnvelope()            const { return envelope; }
  BlockCoordinates2D const& getNonPeriodicEnvelope() const { return nonPeriodicEnvelope; }
  int getBulkLx() const { return bulk.x1-bulk.x0+1; }
  int getBulkLy() const { return bulk.y1-bulk.y0+1; }
  int getEnvelopeLx() const { return envelope.x1-envelope.x0+1; }
  int getEnvelopeLy() const { return envelope.y1-envelope.y0+1; }
  int toLocalX(int iX) const { return iX-envelope.x0; }
  int toLocalY(int iY) const { return iY-envelope.y0; }
  BlockCoordinates2D toLocal(BlockCoordinates2D const& coord) const {
    return BlockCoordinates2D(coord.shift(-envelope.x0, -envelope.y0));
  }
private:
  int envelopeWidth, procId;
  BlockCoordinates2D bulk, envelope, nonPeriodicEnvelope;
};

class Overlap2D {
public:
  Overlap2D(int originalId_, int overlapId_, BlockCoordinates2D const& intersection_)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(intersection_),
      overlapRegion(intersection_)
  { }
  Overlap2D(int originalId_, int overlapId_,
            BlockCoordinates2D const& originalRegion_,
            int shiftX, int shiftY)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(originalRegion_),
      overlapRegion(originalRegion.shift(-shiftX, -shiftY))
  { }
  int getOriginalId() const { return originalId; }
  int getOverlapId()  const { return overlapId; }
  BlockCoordinates2D const& getOriginalCoordinates() const { return originalRegion; }
  BlockCoordinates2D const& getOverlapCoordinates() const  { return overlapRegion; }
  int getShiftX() const { return originalRegion.x0 - overlapRegion.x0; }
  int getShiftY() const { return originalRegion.y0 - overlapRegion.y0; }
private:
  int originalId, overlapId;
  BlockCoordinates2D originalRegion, overlapRegion;
};

class MultiDataDistribution2D {
public:
  MultiDataDistribution2D(int nx_, int ny_);
  MultiDataDistribution2D& operator=(MultiDataDistribution2D const& rhs);
  int getNx() const { return nx; }
  int getNy() const { return ny; }
  int getNumBlocks()           const { return blocks.size(); }
  int getNumNormalOverlaps()   const { return normalOverlaps.size(); }
  int getNumPeriodicOverlaps() const { return periodicOverlaps.size(); }
  void addBlock(int x0, int x1, int y0, int y1, int envelopeWidth, int procId=0);
  BlockParameters2D const& getBlockParameters(int whichBlock) const;
  Overlap2D   const& getNormalOverlap(int whichOverlap) const;
  Overlap2D const& getPeriodicOverlap(int whichOverlap) const;
  int locate(int iX, int iY, int guess=0) const;
  int locateInEnvelopes(int iX, int iY, std::vector<int>& foundId, int guess=0) const;
  size_t getNumAllocatedBulkCells() const;
  bool getNextChunkX(int iX, int iY, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkY(int iX, int iY, int& nextLattice, int& nextChunkSize) const;
private:
  void computeNormalOverlaps(BlockParameters2D const& newBlock);
  void computePeriodicOverlaps();
private:
  int nx, ny;
  std::vector<BlockParameters2D> blocks;
  std::vector<Overlap2D> normalOverlaps;
  std::vector<Overlap2D> periodicOverlaps;
  std::vector<std::vector<int> > neighbors;
};

/// Indexes of Blocks and Overlaps which are relevant in the parallel case
class RelevantIndexes2D {
public:
  /// Constructor for the serial case: list all blocks and overlaps
  RelevantIndexes2D(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny);
  /// Constructor for the parallel case
  RelevantIndexes2D(MultiDataDistribution2D const& dataDistribution, int whichRank);
  /// Index of all blocks local to current processor
  std::vector<int> const& getBlocks()                const { return myBlocks; }
  /// Index of all blocks with which current processor has communication
  std::vector<int> const& getNearbyBlocks()          const { return nearbyBlocks; }
  /// Index of all overlaps for which original or overlap data are on current processor
  std::vector<int> const& getNormalOverlaps()        const { return normalOverlaps; }
  /// Index of all periodic overlaps for which original or overlap data are on current processor
  std::vector<int> const& getPeriodicOverlaps()      const { return periodicOverlaps; }
  /// Index of all periodic overlaps for which overlap data are on current processor
  std::vector<int> const& getPeriodicOverlapWithMe() const { return periodicOverlapWithMe; }
  /// Bounding box for the envelope of all blocks which are on current processor
  BlockCoordinates2D const& getBoundingBox()         const { return boundingBox; }
private:
  void listAllIndexes(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny);
  void computeRelevantIndexesInParallel(MultiDataDistribution2D const& dataDistribution, int whichRank);
private:
  std::vector<int> myBlocks;
  std::vector<int> nearbyBlocks;
  std::vector<int> normalOverlaps;
  std::vector<int> periodicOverlaps;
  std::vector<int> periodicOverlapWithMe;
  BlockCoordinates2D boundingBox;
};

}  // namespace olb


#endif
