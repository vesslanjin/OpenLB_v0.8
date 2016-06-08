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
 * Groups all the include files for basic 2D dynamics.
 */
#include "olbInit.h"
#include "multiPhysics.h"
#include "singleton.h"
#include "units.h"
#include "latticeDescriptors.h"
#include "latticeStatistics.h"
#include "dynamics.h"
#include "cell.h"
#include "momentaOnBoundaries.h"
#include "momentaOnBoundaries2D.h"
#include "postProcessing.h"
#include "dataFieldBase2D.h"
#include "dataFields2D.h"
#include "serializer.h"
#include "blockStructure2D.h"
#include "boundaryPostProcessors2D.h"
#include "offBoundaryPostProcessors2D.h"
#include "blockLattice2D.h"
#include "blockLatticeView2D.h"
#include "boundaryCondition2D.h"
#include "offBoundaryCondition2D.h"
#include "simulationSetup2D.h"
#include "ompManager.h"
#include "loadBalancer.h"
#include "analysisFlags.h"
#include "dataAnalysisBase2D.h"
#include "dataAnalysis2D.h"
#include "dataReductions.h"
#include "blockGeometry2D.h"
#include "blockGeometryStatistics2D.h"
#include "heuristicLoadBalancer.h"
