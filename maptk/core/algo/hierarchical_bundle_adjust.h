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
 * \brief Header defining \link maptk::algo::hierarchical_bundle_adjust
 *        hierarchical bundle adjustment \endlink algorithm
 */

#ifndef MAPTK_ALGO_HIERARCHICAL_BUNDLE_ADJUST_H_
#define MAPTK_ALGO_HIERARCHICAL_BUNDLE_ADJUST_H_

#include <maptk/core/algo/algorithm.h>
#include <maptk/core/algo/bundle_adjust.h>
#include <maptk/core/config_block.h>
#include <maptk/core/core_config.h>

#include <boost/scoped_ptr.hpp>


namespace maptk
{

namespace algo
{


class MAPTK_CORE_EXPORT hierarchical_bundle_adjust
  : public algorithm_impl<hierarchical_bundle_adjust, bundle_adjust>
{
public:

  /// Constructor
  hierarchical_bundle_adjust();
  /// Copy constructor
  hierarchical_bundle_adjust(hierarchical_bundle_adjust const& other);
  /// Destructor
  virtual ~hierarchical_bundle_adjust() MAPTK_NOTHROW;

  /// Return the name of this implementation
  std::string impl_name() const { return "hierarchical"; }

  /// Get this algorithm's \link maptk::config_block configuration block \endlink
  virtual config_block_sptr get_configuration() const;
  /// Set this algorithm's properties via a config block
  virtual void set_configuration(config_block_sptr config);
  /// Check that the algorithm's configuration config_block is valid
  virtual bool check_configuration(config_block_sptr config) const;

  /// Optimize the camera and landmark parameters given a set of tracks
  virtual void optimize(camera_map_sptr & cameras,
                        landmark_map_sptr & landmarks,
                        track_set_sptr tracks) const;

private:
  // private implementation class
  class priv;
  boost::scoped_ptr<priv> d_;
};


/// Type definition for shared pointer for hierarchical_bundle_adjust algorithm
typedef boost::shared_ptr<hierarchical_bundle_adjust> hierarchical_bundle_adjust_sptr;


}

}


#endif // MAPTK_ALGO_HIERARCHICAL_BUNDLE_ADJUST_H_
