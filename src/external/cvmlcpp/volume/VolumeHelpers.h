/***************************************************************************
 *   Copyright (C) 2007 by BEEKHOF, Fokko                                  *
 *   fpbeekhof@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*
 * This header should not be included directly!
 */

#ifndef CVMLCPP_VOLUMEHELPERS
#define CVMLCPP_VOLUMEHELPERS 1

#include <vector>

#include <omptl/omptl_algorithm>

#include <cvmlcpp/volume/Geometry>

namespace cvmlcpp
{

namespace detail
{

template <typename T>
struct IndexPoint
{
	typedef typename Geometry<T>::point_type point_type;

	IndexPoint() {}
	IndexPoint(const std::size_t i_, const point_type &p_) : i(i_), p(p_) {}

	bool operator<(const IndexPoint &that) const
	{
		return this->p < that.p;
	}

	std::size_t i;
	point_type p;
};

// Pre: each consequetive 3 idxPoints form a facet, and the normals are in the
// same order; i.e. for normal[i], the corresponding points are idxPoints[3*i],
// idxPoints[3*i+1] and idxPoints[3*i+2]
template <typename T>
bool constructGeometry(Geometry<T> &geometry, std::vector<Point3D<T> > &points)
{
	typedef typename Geometry<T>::point_type	point_type;
	typedef typename Geometry<T>::vector_type	vector_type;
	typedef typename Geometry<T>::facet_type	facet_type;

	assert(points.size() % 3 == 0);
	if (points.size() % 3 != 0)
		return false;

	geometry.clear();

	for (std::size_t i = 0; i < points.size(); i+=3)
	{
		const std::size_t a = geometry.addPoint( points[i  ] );
		const std::size_t b = geometry.addPoint( points[i+1] );
		const std::size_t c = geometry.addPoint( points[i+2] );
		geometry.addFacet(a, b, c);
	}

	return true;
}

// Pre: each consequetive 3 idxPoints form a facet, and the normals are in the
// same order; i.e. for normal[i], the corresponding points are idxPoints[3*i],
// idxPoints[3*i+1] and idxPoints[3*i+2]
template <typename T>
bool constructGeometry(Geometry<T> &geometry,
			std::vector<IndexPoint<T> > &idxPoints,
			std::vector<typename Geometry<T>::vector_type> &normals)
{
	typedef typename Geometry<T>::point_type	point_type;
	typedef typename Geometry<T>::vector_type	vector_type;
	typedef typename Geometry<T>::facet_type	facet_type;

	geometry.clear();

	if (idxPoints.size() == 0)
		return false;

	const std::size_t nPoints = idxPoints.size();
	omptl::sort(idxPoints.begin(), idxPoints.end());

	assert(nPoints > 0u);

	std::vector<std::size_t> pointIndexMap(nPoints);
	std::vector<point_type> points(nPoints);
	std::size_t index = 0u;
	pointIndexMap[0] = 0u;
	points[0] = idxPoints[0].p;
	for (std::size_t i = 1u; i < nPoints; ++i)
	{
		if (idxPoints[i-1].p < idxPoints[i].p)
			++index;
		pointIndexMap[idxPoints[i].i] = index;
		points[i] = idxPoints[i].p;
	}

	const typename std::vector<point_type>::iterator
		lastPoint = std::unique(points.begin(), points.end());

	std::vector<std::size_t> pointIndices(nPoints);
	geometry.loadPoints(points.begin(), lastPoint, pointIndices.begin());

	const std::size_t nFacets = nPoints / 3u;
	std::vector<facet_type> facets(nFacets);
	for (std::size_t i = 0; i < nFacets; ++i)
	{
		std::size_t p [] = {pointIndices[pointIndexMap[3*i    ]],
				 pointIndices[pointIndexMap[3*i + 1]],
				 pointIndices[pointIndexMap[3*i + 2]] };
		facets[i].set(p, p+3, normals[i]);
	}

	omptl::sort(facets.begin(), facets.end());
	const typename std::vector<facet_type>::iterator
		lastFacet = std::unique(facets.begin(), facets.end());

	std::vector<std::size_t> facetIndices(nFacets);
	geometry.loadFacets(facets.begin(), lastFacet, facetIndices.begin());

	return true;
}

} // namespace

} // namespace

#endif
