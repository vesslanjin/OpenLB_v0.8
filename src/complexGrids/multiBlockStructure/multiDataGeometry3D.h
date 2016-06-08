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
 * Geometry specifications for 3D multiblocks -- header file.
 */

#ifndef MULTI_DATA_GEOMETRY_3D_H
#define MULTI_DATA_GEOMETRY_3D_H

#include <vector>
#include "core/util.h"

namespace olb {

/// Coordinates of a single BlockStructure within a MultiBlock
struct BlockCoordinates3D {
  BlockCoordinates3D() : x0(), x1(), y0(), y1(), z0(), z1() { }
  BlockCoordinates3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
    : x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_)
  { }
  BlockCoordinates3D shift(int deltaX, int deltaY, int deltaZ) const {
    return BlockCoordinates3D(x0+deltaX, x1+deltaX, y0+deltaY, y1+deltaY, z0+deltaZ, z1+deltaZ);
  }
  int x0, x1, y0, y1, z0, z1;
};

namespace util {

inline bool intersect (
  BlockCoordinates3D const& block1,
  BlockCoordinates3D const& block2,
  BlockCoordinates3D& inters )
{
  return intersect(block1.x0, block1.x1, block1.y0, block1.y1, block1.z0, block1.z1,
                   block2.x0, block2.x1, block2.y0, block2.y1, block2.z0, block2.z1,
                   inters.x0, inters.x1, inters.y0, inters.y1, inters.z0, inters.z1);
}

inline bool contained(int iX, int iY, int iZ, BlockCoordinates3D const& block) {
  return contained(iX,iY,iZ, block.x0, block.x1, block.y0, block.y1, block.z0, block.z1);
}

}


class BlockParameters3D {
public:
  BlockParameters3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                    int envelopeWidth_, int procId_,
                    bool leftX, bool rightX, bool leftY, bool rightY, bool leftZ, bool rightZ);
  int getEnvelopeWidth()                             const { return envelopeWidth; }
  int getProcId()                                    const { return procId; }
  BlockCoordinates3D const& getBulk()                const { return bulk; }
  BlockCoordinates3D const& getEnvelope()            const { return envelope; }
  BlockCoordinates3D const& getNonPeriodicEnvelope() const { return nonPeriodicEnvelope; }
  int getBulkLx() const { return bulk.x1-bulk.x0+1; }
  int getBulkLy() const { return bulk.y1-bulk.y0+1; }
  int getBulkLz() const { return bulk.z1-bulk.z0+1; }
  int getEnvelopeLx() const { return envelope.x1-envelope.x0+1; }
  int getEnvelopeLy() const { return envelope.y1-envelope.y0+1; }
  int getEnvelopeLz() const { return envelope.z1-envelope.z0+1; }
  int toLocalX(int iX) const { return iX-envelope.x0; }
  int toLocalY(int iY) const { return iY-envelope.y0; }
  int toLocalZ(int iZ) const { return iZ-envelope.z0; }
  BlockCoordinates3D toLocal(BlockCoordinates3D const& coord) const {
    return BlockCoordinates3D(coord.shift(-envelope.x0, -envelope.y0, -envelope.z0));
  }
private:
  int envelopeWidth, procId;
  BlockCoordinates3D bulk, envelope, nonPeriodicEnvelope;
};

class Overlap3D {
public:
  Overlap3D(int originalId_, int overlapId_, BlockCoordinates3D const& intersection_)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(intersection_),
      overlapRegion(intersection_)
  { }
  Overlap3D(int originalId_, int overlapId_,
            BlockCoordinates3D const& originalRegion_,
            int shiftX, int shiftY, int shiftZ)
    : originalId(originalId_), overlapId(overlapId_),
      originalRegion(originalRegion_),
      overlapRegion(originalRegion.shift(-shiftX, -shiftY, -shiftZ))
  { }
  int getOriginalId() const { return originalId; }
  int getOverlapId()  const { return overlapId; }
  BlockCoordinates3D const& getOriginalCoordinates() const { return originalRegion; }
  BlockCoordinates3D const& getOverlapCoordinates() const  { return overlapRegion; }
  int getShiftX() const { return originalRegion.x0 - overlapRegion.x0; }
  int getShiftY() const { return originalRegion.y0 - overlapRegion.y0; }
  int getShiftZ() const { return originalRegion.z0 - overlapRegion.z0; }
private:
  int originalId, overlapId;
  BlockCoordinates3D originalRegion, overlapRegion;
};

class MultiDataDistribution3D {
public:
  MultiDataDistribution3D(int nx_, int ny_, int nz_);
  MultiDataDistribution3D& operator=(MultiDataDistribution3D const& rhs);
  int getNx() const { return nx; }
  int getNy() const { return ny; }
  int getNz() const { return nz; }
  int getNumBlocks()           const { return blocks.size(); }
  int getNumNormalOverlaps()   const { return normalOverlaps.size(); }
  int getNumPeriodicOverlaps() const { return periodicOverlaps.size(); }
  void addBlock(int x0, int x1, int y0, int y1, int z0, int z1, int envelopeWidth, int procId=0);
  BlockParameters3D const& getBlockParameters(int whichBlock) const;
  Overlap3D   const& getNormalOverlap(int whichOverlap) const;
  Overlap3D const& getPeriodicOverlap(int whichOverlap) const;
  int locate(int iX, int iY, int iZ, int guess=0) const;
  int locateInEnvelopes(int iX, int iY, int iZ, std::vector<int>& foundId, int guess=0) const;
  size_t getNumAllocatedBulkCells() const;
  bool getNextChunkX(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkY(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
  bool getNextChunkZ(int iX, int iY, int iZ, int& nextLattice, int& nextChunkSize) const;
private:
  void computeNormalOverlaps(BlockParameters3D const& newBlock);
  void computePeriodicOverlaps();
private:
  int nx, ny, nz;
  std::vector<BlockParameters3D> blocks;
  std::vector<Overlap3D> normalOverlaps;
  std::vector<Overlap3D> periodicOverlaps;
  std::vector<std::vector<int> > neighbors;
};

/// Indexes of Blocks and Overlaps which are relevant in the parallel case
class RelevantIndexes3D {
public:
  /// Constructor for the serial case: list all blocks and overlaps
  RelevantIndexes3D(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny, int nz);
  /// Constructor for the parallel case
  RelevantIndexes3D(MultiDataDistribution3D const& dataDistribution, int whichRank);
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
  BlockCoordinates3D const& getBoundingBox()         const { return boundingBox; }
private:
  void listAllIndexes(int numBlocks, int numNormalOverlaps, int numPeriodicOverlaps, int nx, int ny, int nz);
  void computeRelevantIndexesInParallel(MultiDataDistribution3D const& dataDistribution, int whichRank);
private:
  std::vector<int> myBlocks;
  std::vector<int> nearbyBlocks;
  std::vector<int> normalOverlaps;
  std::vector<int> periodicOverlaps;
  std::vector<int> periodicOverlapWithMe;
  BlockCoordinates3D boundingBox;
};

}  // namespace olb

#endif
