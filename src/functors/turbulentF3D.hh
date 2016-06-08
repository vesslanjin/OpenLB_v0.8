/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Patrick Nathen, Mathias J. Krause
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

#ifndef TURBULENT_F_3D_HH
#define TURBULENT_F_3D_HH

#include<vector>
#include<cmath>
#include<string>

#include "turbulentF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/superLatticeBaseF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity
#include "io/stlReader.h"

/** To enable simulations in a rotating frame, the axis is set in the
  * constructor with axisPoint and axisDirection. The axisPoint can be the
  * coordinate of any point where the axis pass. The axisDirection has to,
  * be a normal. The pulse w is in rad/s. It determines the pulse speed by
  * its norm while the trigonometric or clockwise direction is determined by
  * its sign: when the axisDirection is pointing "toward you", a
  * positive pulse make it turn in the trigonometric way. It has to be noted
  * that putting both axisDirection into -axisDirection and w into -w yields
  * an exactly identical situation.
  */

namespace olb {


///////////////////////////// SuperLatticeYplus3D //////////////////////////////


  template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeYplus3D<T,DESCRIPTOR>::SuperLatticeYplus3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter,
    SuperGeometry3D& _superGeometry, STLreader<T>& _stlReader, int _material )
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,1),
  superGeometry(_superGeometry), stlReader(_stlReader),
  material(_material) { }


  template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeYplus3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];

  std::vector<T> output(1,T());

  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) { //if 1
    // local coords are given, fetch local cell and compute value(s)
    int globX = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix;
    int globY = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy;
    int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz;

    T normal[3] = {0,0,0};
    T counter = T();
    T dist;
    if(superGeometry.getMaterial(globX, globY, globZ) == 1) { //if 2
      for(int iPop=0; iPop<DESCRIPTOR<T>::q; iPop++) {
        if(superGeometry.getMaterial(globX+DESCRIPTOR<T>::c[iPop][0], globY+DESCRIPTOR<T>::c[iPop][1], globZ+DESCRIPTOR<T>::c[iPop][2]) ==material){
          counter++;
          normal[0]+=DESCRIPTOR<T>::c[iPop][0];
          normal[1]+=DESCRIPTOR<T>::c[iPop][1];
          normal[2]+=DESCRIPTOR<T>::c[iPop][2];
        }
      }
      if(counter!=0) { //if 3
        // get physical Coordinates at intersection
        T globPhysX=superGeometry.physCoordX(globX);
        T globPhysY=superGeometry.physCoordY(globY);
        T globPhysZ=superGeometry.physCoordZ(globZ);
        T voxelSize=superGeometry.getSpacing();
        // calculate distance to STL file
        if(stlReader.readDistanceCuboid(globPhysX, globPhysY, globPhysZ,
              voxelSize*normal[0]*1.5, voxelSize*normal[1]*1.5, voxelSize*normal[2]*1.5,
              this->sLattice.get_load().loc(globIC), dist)) {

          T norm = sqrt(normal[0]*normal[0]+normal[1]*normal[1]+normal[2]*normal[2]);
          if (norm!=0) {
            normal[0] /=norm;
            normal[1] /=norm;
            normal[2] /=norm;
          }

          // call stress at this point
          T rho;
          T u[3];
          T pi[6];
          this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho, u);
          this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeStress(pi);

          //  Totel Stress projected from cell in normal direction on obstacle
          T Rx= pi[0]*normal[0]+pi[1]*normal[1]+pi[2]*normal[2];
          T Ry= pi[1]*normal[0]+pi[3]*normal[1]+pi[4]*normal[2];
          T Rz= pi[2]*normal[0]+pi[4]*normal[1]+pi[5]*normal[2];

          // Stress appearing as pressure in corresponding direction is calculated and substracted
          T R_res_pressure =  normal[0]*pi[0]*normal[0]+ normal[0]*pi[1]*normal[1] + normal[0]*pi[2]*normal[2] +
                              normal[1]*pi[1]*normal[0]+ normal[1]*pi[3]*normal[1] + normal[1]*pi[4]*normal[2] +
                              normal[2]*pi[2]*normal[0]+ normal[2]*pi[4]*normal[1] + normal[2]*pi[5]*normal[2];

          Rx -= R_res_pressure *normal[0];
          Ry -= R_res_pressure *normal[1];
          Rz -= R_res_pressure *normal[2];

          T tau_wall = sqrt(Rx*Rx+Ry*Ry+Rz*Rz)*this->converter.getLatticeNu();
          T u_tau=sqrt(tau_wall/rho);
          //y_plus
          output[0] = dist*u_tau/this->converter.getCharNu();
        } // if 4
      }
    }
  }
  return output; // empty vector
} // operator()


///////////////////////////// SuperLatticeQCrit3D //////////////////////////////


 template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeQCrit3D<T,DESCRIPTOR>::SuperLatticeQCrit3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, LBconverter<T>& _converter, SuperGeometry3D& sg)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,1), superGeometry(sg){ }


 template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeQCrit3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int foundIC = (int)input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  //int globIC = input[0];
  //int count;
  if ( this->sLattice.get_load().rank(foundIC) == singleton::mpi().getRank() ) {

   int globX = (int)this->sLattice.get_cGeometry().get_cuboid(foundIC).get_globPosX() + locix;
   int globY = (int)this->sLattice.get_cGeometry().get_cuboid(foundIC).get_globPosY() + lociy;
   int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(foundIC).get_globPosZ() + lociz;
    /// material fluid???
   if(superGeometry.getMaterial(globX+1, globY+1, globZ+1) == 1) {



   /////CORE LOOOOOOOP
   //T rho; 
   T u_x_plus[3], u_x_minus[3], u_y_plus[3], u_y_minus[3],u_z_plus[3], u_z_minus[3];
   std::vector<T> pos(3, 0.);

   //T loc_pos[3];



 // pos[0] = this->converter->latticeLength(input[1] - superGeometry.getPositionX());
 // pos[1] = this->converter->latticeLength(input[2] - superGeometry.getPositionY());
 // pos[2] = this->converter->latticeLength(input[3] - superGeometry.getPositionZ());

  Cell<T, DESCRIPTOR> cell;
 // T x0 = floor(pos[0]);
 // T y0 = floor(pos[1]);
 // T z0 = floor(pos[2]);

  //BlockLattice
  // loc_pos[0] = x0 -globX + this->sLattice.get_overlap()*
  //     this->sLattice.get_cGeometry().get_cuboid(foundIC).get_delta();
  // loc_pos[1] = y0 - globY + this->sLattice.get_overlap()*
  //     this->sLattice.get_cGeometry().get_cuboid(foundIC).get_delta();
  // loc_pos[2] = z0 - globZ + this->sLattice.get_overlap()*
  //     this->sLattice.get_cGeometry().get_cuboid(foundIC).get_delta();

foundIC = this->sLattice.get_load().loc(foundIC);
//std::cout << "[SuperLatticePhysVelocityInterp3D] "<< " " <<"locx: "<<globX<<" locy: "<<globY<<" locz: "<<globZ << std::endl;

  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0]+1, loc_pos[1], loc_pos[2]).computeRhoU(rho,u_x_plus);
  // //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  , loc_pos[1], loc_pos[2]).computeU(u_x);
  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0]+1, loc_pos[1], loc_pos[2]).computeRhoU(rho,u_x_minus);

  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0], loc_pos[1]+1, loc_pos[2]).computeRhoU(rho,u_y_plus);
  // //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  , loc_pos[1]  , loc_pos[2]).computeU(loc_vel[1]);
  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0], loc_pos[1]-1, loc_pos[2]).computeRhoU(rho,u_y_minus);

  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0], loc_pos[1], loc_pos[2]+1).computeRhoU(rho,u_z_plus);
  // //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  , loc_pos[1]  , loc_pos[2]  ).computeU(u_y_plus);
  // this->sLattice.get_lattice(this->sLattice.get_load().loc(foundIC)).get(loc_pos[0], loc_pos[1], loc_pos[2]-1).computeRhoU(rho,u_z_minus);

std::cout <<"dafuq x ?????: " <<locix<<std::endl;
  this->sLattice.get_blockLattice(foundIC).get(locix+this->sLattice.get_overlap()+1,   lociy  ,  lociz  ).computeU(u_x_plus);
  //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  ,   loc_pos[1]  ,  loc_pos[2]  ).computeU(u_x_plus[0]);
  this->sLattice.get_blockLattice(foundIC).get(locix+this->sLattice.get_overlap()-1,   lociy  ,  lociz  ).computeU(u_x_minus);

  this->sLattice.get_blockLattice(foundIC).get(locix  ,   lociy+this->sLattice.get_overlap()+1,  lociz  ).computeU(u_y_plus);
  //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  ,   loc_pos[1]  ,  loc_pos[2]  ).computeU(loc_vel[4]);
  this->sLattice.get_blockLattice(foundIC).get(locix  ,   lociy+this->sLattice.get_overlap()-1,  lociz  ).computeU(u_y_minus);

  this->sLattice.get_blockLattice(foundIC).get(locix  ,   lociy  ,  lociz+this->sLattice.get_overlap()+1).computeU(u_z_plus);
  //this->sLattice.get_blockLattice(foundIC).get(loc_pos[0]  ,   loc_pos[1],  loc_pos[2]  ).computeU(u_y_plus);
  this->sLattice.get_blockLattice(foundIC).get(locix  ,   lociy  ,  lociz+this->sLattice.get_overlap()-1).computeU(u_z_minus);
std::cout <<"dafuq x ?????: " <<lociy<<std::endl;

    //           int globX_pos = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosX()  + 1;
    //           int globX     = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosX()     ;
    //           int globX_neg = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosX()  - 1;

    //           int globY_pos = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosY()   + 1;
    //           int globY     = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosY()      ;
    //           int globY_neg = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosY()   - 1;

    //           int globZ_pos = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosZ()   + 1;
    //           int globZ     = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosZ()      ;
    //           int globZ_neg = (int)cGeometry.get_cuboid(load.glob(globIC)).get_globPosZ()   - 1;

    // int globX_pos = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix + 1;
    // int globX     = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix    ;
    // int globX_neg = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix - 1;

    // int globY_pos = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy + 1;
    // int globY     = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy    ;
    // int globY_neg = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy - 1;

    // int globZ_pos = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz + 1;
    // int globZ     = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz    ;
    // int globZ_neg = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz - 1;


    //    //
    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX_pos, globY, globZ).computeRhoU(rho,u_x_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX_neg, globY, globZ).computeRhoU(rho,u_x_minus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX, globY_pos, globZ).computeRhoU(rho,u_y_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX, globY_neg, globZ).computeRhoU(rho,u_y_minus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX, globY, globZ_pos).computeRhoU(rho,u_z_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(globX, globY, globZ_neg).computeRhoU(rho,u_z_minus);




    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_x_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_x_minus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_y_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_y_minus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_z_plus);

    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeRhoU(rho,u_z_minus);

    T dUdX = (this->converter.physVelocity(u_x_plus[0]-u_x_minus[0]))/(2*this->converter.getDeltaX());
    T dUdY = (this->converter.physVelocity(u_y_plus[0]-u_y_minus[0]))/(2*this->converter.getDeltaX());
    T dUdZ = (this->converter.physVelocity(u_z_plus[0]-u_z_minus[0]))/(2*this->converter.getDeltaX());

    T dVdX = (this->converter.physVelocity(u_x_plus[1]-u_x_minus[1]))/(2*this->converter.getDeltaX());
    T dVdY = (this->converter.physVelocity(u_y_plus[1]-u_y_minus[1]))/(2*this->converter.getDeltaX());
    T dVdZ = (this->converter.physVelocity(u_z_plus[1]-u_z_minus[1]))/(2*this->converter.getDeltaX());

    T dWdX = (this->converter.physVelocity(u_x_plus[2]-u_x_minus[2]))/(2*this->converter.getDeltaX());
    T dWdY = (this->converter.physVelocity(u_y_plus[2]-u_y_minus[2]))/(2*this->converter.getDeltaX());
    T dWdZ = (this->converter.physVelocity(u_z_plus[2]-u_z_minus[2]))/(2*this->converter.getDeltaX());

    T qCrit= dUdX*dUdX - (dUdY*dVdX + dUdZ*dWdX) +
             dVdY*dVdY - (dVdX*dUdY + dVdZ*dWdY) +
             dWdZ*dWdZ - (dWdX*dUdZ + dWdY*dVdZ);


    // local coords are given, fetch local cell and compute value(s)
    // T rho, uTemp[DESCRIPTOR<T>::d], pi[util::TensorVal<DESCRIPTOR<T> >::n];
    // this->sLattice.get_lattice(this->sLattice.get_load().loc(globIC)).get(locix, lociy, lociz).computeAllMomenta(rho, uTemp, pi);

    // T PiNeqNormSqr = pi[0]*pi[0] + 2.*pi[1]*pi[1] + pi[2]*pi[2];
    // if (util::TensorVal<DESCRIPTOR<T> >::n == 6)
    //   PiNeqNormSqr += pi[2]*pi[2] + pi[3]*pi[3] + 2.*pi[4]*pi[4] +pi[5]*pi[5];

    // T nuLattice = converter->getLatticeNu();
    // T omega = converter->getOmega();
    // T finalResult = PiNeqNormSqr*nuLattice*pow(omega*DESCRIPTOR<T>::invCs2,2)/rho/2.;

    return std::vector<T>(1,-0.5*qCrit);
  }
    else { // if 3
    std::vector<T> output; output.push_back(T());
    return output;
    }
 }

  else {
    return std::vector<T>(); // empty vector
  }
} // end SuperLatticeQCrit3D::operator()


} // end namespace olb
#endif


