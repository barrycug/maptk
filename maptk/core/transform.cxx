/*ckwg +29
 * Copyright 2014 by Kitware, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  * Neither name of Kitware, Inc. nor the names of any contributors may be used
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 * \brief Implementation of maptk::transform functions to apply
 * similarity transformations
 */

#include "transform.h"
#include <boost/foreach.hpp>


namespace maptk
{

/// Transform a 3D covariance matrix with a similarity transformation
template <typename T>
covariance_<3,T> transform(const covariance_<3,T>& covar,
                           const similarity_<T>& xform)
{
  // TODO trasform covariance parameters directly
  // instead of converting to matrix form and back
  matrix_<3,3,T> C(covar);
  matrix_<3,3,T> sR(xform.rotation());
  sR /= xform.scale();
  C = sR * C * sR.transpose();
  return covariance_<3,T>(C);
}


/// construct a transformed camera by applying a similarity transformation
camera_sptr transform(camera_sptr cam,
                      const similarity_d& xform)
{
  cam = cam->clone();
  cam->transform(xform);
  return cam;
}


/// construct a transformed map of cameras by applying a similarity transformation
camera_map_sptr transform(camera_map_sptr cameras,
                          const similarity_d& xform)
{
  camera_map::map_camera_t cam_map = cameras->cameras();
  BOOST_FOREACH(camera_map::map_camera_t::value_type& p, cam_map)
  {
    p.second = transform(p.second, xform);
  }
  return camera_map_sptr(new simple_camera_map(cam_map));
}


/// construct a transformed landmark by applying a similarity transformation
MAPTK_CORE_EXPORT
landmark_sptr transform(landmark_sptr lm,
                        const similarity_d& xform)
{
  lm = lm->clone();
  lm->transform(xform);
  return lm;
}


/// construct a transformed map of landmarks by applying a similarity transformation
landmark_map_sptr transform(landmark_map_sptr landmarks,
                            const similarity_d& xform)
{
  landmark_map::map_landmark_t lm_map = landmarks->landmarks();
  BOOST_FOREACH(landmark_map::map_landmark_t::value_type& p, lm_map)
  {
    p.second = transform(p.second, xform);
  }
  return landmark_map_sptr(new simple_landmark_map(lm_map));
}


/// \cond DoxygenSuppress
#define INSTANTIATE_TRANSFORM(T) \
template MAPTK_CORE_EXPORT covariance_<3,T> transform(const covariance_<3,T>& covar, \
                                                      const similarity_<T>& xform);

INSTANTIATE_TRANSFORM(double);
INSTANTIATE_TRANSFORM(float);

#undef INSTANTIATE_TRANSFORM
/// \endcond


} // end namespace maptk
