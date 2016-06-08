/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Orestis Malaspinas
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
 * Groups all the 2D include files in the complexDynamics directory.
*/


#include "mrtLatticeDescriptors.h"
#include "advectionDiffusionLatticeDescriptors.h"
#include "forcedShanChenLatticeDescriptors.h"
#include "entropicDynamics.h"
#include "entropicLbHelpers.h"
#include "mrtDynamics.h"
#include "chopardDynamics.h"
#include "navierStokesAdvectionDiffusionCouplingPostProcessor2D.h"
#include "advectionDiffusionDynamics.h"
#include "advectionDiffusionBoundaries.h"
#include "advectionDiffusionBoundaryCondition2D.h"
#include "advectionDiffusionMomenta.h"
#include "advectionDiffusionUnits.h"
#include "forcedShanChenCouplingPostProcessor2D.h"
#include "smagorinskyBGKdynamics.h"
#include "smagorinskyMRTdynamics.h"
#include "powerLawBGKdynamics.h"
#include "porousBGKdynamics.h"
#include "porousBGKdynamicsDescriptors.h"
